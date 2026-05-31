# 🐶 Alimentador Automático DOGUINHO com ESP32

Projeto desenvolvido por **Lucas Carvalho**, utilizando **ESP32**, **Servo Motor**, **WiFiManager** e comunicação HTTPS para consultar um servidor remoto e acionar automaticamente um mecanismo de alimentação.

## 📋 Funcionamento

O ESP32 conecta-se à internet e realiza uma consulta a cada **5 segundos** no endpoint:

```text
https://backend-dog-9e62.onrender.com/consulta?machine=dog1
```

Se o servidor retornar:

```text
true
```

o servo motor é acionado para liberar a ração.

Se retornar:

```text
false
```

o servo permanece na posição de repouso.

O projeto também possui:

* Configuração Wi-Fi via WiFiManager
* Portal de configuração chamado **DOGUINHO**
* LED de status para indicar conexão
* Reconexão automática ao Wi-Fi
* Comunicação HTTPS
* Controle de Servo Motor

---

## 🔧 Hardware Utilizado

* ESP32
* Servo Motor SG90 ou MG90S
* LED de status
* Fonte de alimentação adequada
* Estrutura impressa em 3D

---

## 📦 Dependências

Instale as seguintes bibliotecas pela Arduino IDE:

### ESP32

Instale o pacote ESP32 da Espressif:

Arquivo → Preferências → URLs adicionais:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Depois:

```text
Ferramentas → Placa → Gerenciador de Placas
```

Procure por:

```text
esp32 by Espressif Systems
```

e instale.

---

### Bibliotecas

No Gerenciador de Bibliotecas da Arduino IDE instale:

#### WiFiManager

```text
WiFiManager
```

Autor:

```text
tzapu
```

#### ESP32Servo

```text
ESP32Servo
```

Autor:

```text
Kevin Harrington / John K. Bennett
```

As bibliotecas abaixo já fazem parte do framework ESP32:

```cpp
WiFi.h
HTTPClient.h
Arduino.h
```

---

## 🚀 Gravação

1. Conecte o ESP32 ao computador.
2. Abra o projeto na Arduino IDE.
3. Selecione a placa ESP32 correspondente.
4. Compile e envie o código.

Na primeira inicialização será criada uma rede Wi-Fi chamada:

```text
DOGUINHO
```

Conecte-se a ela para configurar a rede local.

---

## 📐 Arquivos 3D

Este repositório também contém os arquivos STL utilizados para impressão 3D da estrutura do projeto.

Os modelos podem ser impressos em:

* PLA
* PETG
* ABS

Os arquivos STL permitem montar o alimentador físico que abriga:

* ESP32
* Servo Motor
* Compartimento de ração
* Estrutura de fixação

<img width="719" height="514" alt="image" src="https://github.com/user-attachments/assets/1b9d03ed-4c0a-466a-8295-cb54a06e400c" />

<img width="713" height="526" alt="image" src="https://github.com/user-attachments/assets/f9e5133c-6f75-46bf-9cf0-12fcbcc6e463" />

<img width="724" height="491" alt="image" src="https://github.com/user-attachments/assets/b0102dfe-0147-47aa-8f2e-d10630d0680e" />




---

## 👨‍💻 Autor

Lucas Carvalho

Projeto educacional e open source para automação e alimentação de animais utilizando ESP32.
