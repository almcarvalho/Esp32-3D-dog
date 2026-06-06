// POR LUCAS CARVALHO — versão com RELÉ e consulta dog1

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h>

// -------------------- CONFIG --------------------
const String consultaUrl = "https://backend-dog-9e62.onrender.com/consulta?machine=dog1";

// Tempo de acionamento do relé em segundos
const unsigned long TEMPO_RELE_SEGUNDOS = 180;

// LED único de status
const int LED_STATUS = 2;

// Relé
const int RELE_PIN = 14;

// Ajuste conforme seu módulo relé
const int RELE_LIGADO = LOW;
const int RELE_DESLIGADO = HIGH;

// Intervalo de consulta
const unsigned long POLL_INTERVAL_MS = 5000;

// -------------------- VARIÁVEIS --------------------
unsigned long lastPoll = 0;
unsigned long lastBlink = 0;
unsigned long lastReco = 0;

bool ledState = false;
bool portalAtivo = false;

WiFiManager wifiManager;

// -------------------- FUNÇÕES --------------------
void blinkWhileConnecting(unsigned long now) {
  if (now - lastBlink >= 500) {
    ledState = !ledState;
    digitalWrite(LED_STATUS, ledState ? HIGH : LOW);
    lastBlink = now;
  }

  if (now - lastReco >= 5000) {
    WiFi.reconnect();
    lastReco = now;
  }
}

void acionarRele() {
  Serial.println("Ligando relé");

  digitalWrite(RELE_PIN, RELE_LIGADO);

  delay(TEMPO_RELE_SEGUNDOS * 1000UL);

  Serial.println("Desligando relé");

  digitalWrite(RELE_PIN, RELE_DESLIGADO);
}

void consultarMaquina() {
  HTTPClient https;

  Serial.println("[HTTPS] begin...");

  if (https.begin(consultaUrl)) {

    Serial.println("[HTTPS] GET...");

    int httpCode = https.GET();

    if (httpCode > 0) {

      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK ||
          httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

        String payload = https.getString();
        payload.trim();

        Serial.println("payload:");
        Serial.println(payload);

        if (payload == "true") {
          acionarRele();
        } else {
          Serial.println("Retorno false");
          digitalWrite(RELE_PIN, RELE_DESLIGADO);
        }

      } else {
        Serial.println("HTTP não OK");
      }

    } else {
      Serial.printf("[HTTPS] GET failed: %s\n",
                    https.errorToString(httpCode).c_str());
    }

    https.end();

  } else {
    Serial.println("[HTTPS] Unable to connect");
  }
}

// -------------------- SETUP --------------------
void setup() {

  Serial.begin(115200);

  pinMode(LED_STATUS, OUTPUT);
  digitalWrite(LED_STATUS, LOW);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, RELE_DESLIGADO);

  wifiManager.setConfigPortalTimeout(180);
  wifiManager.setConfigPortalBlocking(false);

  bool conectado = wifiManager.autoConnect("DOGUINHO");

  if (conectado) {

    Serial.println("Conectado ao Wi-Fi.");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    digitalWrite(LED_STATUS, HIGH);
    ledState = true;

  } else {

    Serial.println("*wm:Starting Web Portal");
    portalAtivo = true;
  }
}

// -------------------- LOOP --------------------
void loop() {

  unsigned long now = millis();

  if (WiFi.status() != WL_CONNECTED) {

    if (!portalAtivo) {

      wifiManager.startConfigPortal("DOGUINHO");

      portalAtivo = true;
      Serial.println("*wm:Starting Web Portal");
    }

    blinkWhileConnecting(now);

    wifiManager.process();

    digitalWrite(RELE_PIN, RELE_DESLIGADO);

    return;
  }

  if (portalAtivo) {
    portalAtivo = false;
    Serial.println("Conectado ao Wi-Fi.");
  }

  if (!ledState || digitalRead(LED_STATUS) == LOW) {
    ledState = true;
    digitalWrite(LED_STATUS, HIGH);
  }

  digitalWrite(RELE_PIN, RELE_DESLIGADO);

  if (now - lastPoll >= POLL_INTERVAL_MS) {

    lastPoll = now;

    consultarMaquina();

    Serial.println("TEMPO DE CONSULTA 5 SEGUNDOS");
  }
}
