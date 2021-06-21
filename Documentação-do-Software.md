# Introdução

Toda a bibliteca `PION_System.h` que deve ser utilizada para acesso as funções é programada em C++ e está incluída na instalação do suporte PION para o Ambiente de Desenvolvimento(IDE) do Arduino. O sistema utiliza de todo o poder de processamento do ESP32 e do seu nucleo para Arduino construído com FreeRTOS, para fornecer aos usuários uma melhor experiência ao utilizar os `Kits Educacionais PION`. 

Todo o processamento de leitura dos sensores e controle de eventos como atuação de LED's e do BUZZER são comandados em segundo plano em tarefas em paralelo ao `void loop()` do Arduino, sendo necessário ao usuário apenas acessar a algumas funções listadas a seguir:

- [void init()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-init)
- [void initNoNetwork()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-initnonetwork)
- [uint8_t getBattery](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#uint8_t-getbattery)
- [float getTemperature()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-gettemperature)
- [float getHumidity()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-gethumidity)
- [float getPressure()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getpressure)
- [float getCO2Level()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getco2level)
- [float getLuminosity()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getluminosity)
- [float getAccelerometer(uint8_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getaccelerometeruint8_t)
- [float getGyroscope(uint8_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getgyroscopeuint8_t)
- [float getMagnetometer(uint8_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#float-getmagnetometeruint8_t)
- [void setRGB(uint8_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-setrgbuint8_t)
- [void setLed(uint8_t, uint8_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-setleduint8_t-uint8_t)
- [void buzzer(uint16_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-buzzeruint16_t)
- [void doBeeps(uint8_t, uint16_t, uint16_t)](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-dobeepsuint8_t-uint16_t-uint16_t)
- [void toggleSiren()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-togglesiren)
- [SirenState_t getSirenState()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#sirenstate_t-getsirenstate)
- [uint32_t getSerialNumber()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#uint32_t-getserialnumber)
- [SDStatus_t getSDStatus()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#sdstatus_t-getsdstatus)
- [void createSDLogTask()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-createsdlogtask)
- [void toggleSD()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-togglesd)
- [void createLogOnSD()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-createlogonsd)
- [void logOnSDFile()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software#void-logonsdfile)

## Objeto `System`

Após ter incluído a biblioteca em seu código com a chamada `#include "PION_System.h"` você precisa inicializar um objeto para a classe `System`. Para isso, recomenda-se que inicialize-a com um objeto de nome canSat ou cubeSat de acordo com o modelo que estiver utilizando. No entanto, não há nenhum problema em utilizar outras palavras para essa definição.

```C++
#include "PION_System.h"

System canSat;
// ou
System cubeSat;

void setup(){
  // Inicializa seu CanSat, e seus periféricos    
  canSat.init();
}
```

## Funções

### `void init()`
A função init deve sempre ser adicionada ao `void Setup()` de sua aplicação para inicializar seu CanSat ou CubeSat. Essa função inicializará todos os subsistemas necessários para a utilização do seu CanSat ou CubeSat.

```C++
#include "PION_System.h"

System canSat;

void setup(){
  // Inicializa seu CanSat, e seus periféricos  
  canSat.init();
}
```

### `void initNoNetwork()`
De maneira análoga a função `init()`, `initNoNetwork()` deve sempre ser adicionada ao `void Setup()` de sua aplicação para inicializar seu CanSat ou CubeSat sem a utilização da WiFi.

```C++
#include "PION_System.h"

System canSat;

void setup(){
  // Inicializa seu CanSat, e seus periféricos 
  canSat.initNoNetwork();
}
```

### `uint8_t getBattery`

Essa função retorna o valor inteiro da bateria do seu cansat ou cubesat normalizado de 0% a 100%.

```C++

int bateria = canSat.getBattery();
// ou
uint8_t bateria = canSat.getBattery();

```
***`uint8_t` é utlizado para economia de espaço, no entanto, pode-se utilizar um `int` para recepção do valor** 

### `float getTemperature()`
A função getTemperature retorna um valor do tipo float correspondente a leitura do sensor de temperatura. A unidade de medida padrão é em graus Celsius (°C).

```C++
// Realiza a leitura de Temperatura, em °C, e armazena em uma variável do tipo float.
float temperatura = canSat.getTemperature();

```

### `float getHumidity()`
A função getHumidity retorna um valor do tipo float correspondente a leitura do sensor de humidade. A medida, em porcentagem (%), corresponde a umidade relativa do ar, calculada pela razão entre o percentual de água que existe no ar e o percentual de saturação. 

```C++
// Realiza a leitura de Umidade Relativa , em %, e armazena em uma variável do tipo float.
float umidade = cubeSat.getHumidity();

```

### `float getPressure()`
A função getPressure retorna um valor do tipo float correspondente a leitura do sensor de pressão atmosférica. A unidade de medida padrão é em Pascal (Pa).

```C++
// Realiza a leitura de Pressão, Pa, e armazena em uma variável do tipo float.
float pressãoAtm = canSat.getPressure();

```

### `float getCO2Level()`
A função getCO2Level retorna um valor do tipo float correspondente a leitura do sensor de concetração de CO2. A medida, em partes por milhão (ppm), representa a concentração equivalente de dióxido de carbono (CO2) no ambiente entorno.

```C++
// Realiza a leitura de concentração de CO2, em ppm, e armazena em uma variável do tipo float.
float nivelCO2 = cubeSat.getCO2Level();

```

### `float getLuminosity()`
A função getLuminosity retorna um valor do tipo float correspondente a leitura do sensor de luminosidade. A medida, em porcentagem (%), é proporcional a incidência luminosa no sensor.

```C++
// Realiza a leitura de incidência de luz, em %, e armazena em uma variável do tipo float.
float luminosidade = canSat.getLuminosity();

```

### `float getAccelerometer(uint8_t)`
A função getAccelerometer retorna um valor do tipo float correspondente a leitura do acelerômetro triaxial. A medida, em  metro por segundo ao quadrado (m/s²), pode ser adqurida nos 3 eixos do sensor (X , Y e Z) e representa a aceleração sobre o sensor.

```C++
// Realiza a leitura de aceleração no eixo X, em m/s², e armazena em uma variável do tipo float.
float aceleracaoX = cubeSat.getAccelerometer(0);

// Realiza a leitura de aceleração no eixo Y, em m/s², e armazena em uma variável do tipo float.
float aceleracaoY = cubeSat.getAccelerometer(1);

// Realiza a leitura de aceleração no eixo Z, em m/s², e armazena em uma variável do tipo float.
float aceleracaoZ = cubeSat.getAccelerometer(2);

```

### `float getGyroscope(uint8_t)`
A função getGyroscope retorna um valor do tipo float correspondente a leitura do giroscópio triaxial. A medida, em  graus por segundo (graus/s), pode ser adqurida nos 3 eixos do sensor (X , Y e Z) e representa a velocidade angular em cada eixo.

```C++
// Realiza a leitura de velocidade angular no eixo X, em graus/s, e armazena em uma variável do tipo float.
float velAngularX = canSat.getGyroscope(0);

// Realiza a leitura de velocidade angular no eixo Y, em graus/s, e armazena em uma variável do tipo float.
float velAngularY = canSat.getGyroscope(1);

// Realiza a leitura de velocidade angular no eixo Z, em graus/s, e armazena em uma variável do tipo float.
float velAngularZ = canSat.getGyroscope(2);

```

### `float getMagnetometer(uint8_t)`
A função getMagnetometer retorna um valor do tipo float correspondente a leitura do magnetômetro triaxial. A medida, em  micro Tesla (μT), pode ser adqurida nos 3 eixos do sensor (X , Y e Z) e representa a intensidade do campo magnético em cada eixo.

```C++
// Realiza a leitura de intensidade do campo magnético no eixo X, em μT, e armazena em uma variável do tipo float.
float campoMagX= cubeSat.getMagnetometer(0);

// Realiza a leitura de intensidade do campo magnético no eixo Y, em μT, e armazena em uma variável do tipo float.
float campoMagY= cubeSat.getMagnetometer(1);

// Realiza a leitura de intensidade do campo magnético no eixo Z, em μT, e armazena em uma variável do tipo float.
float campoMagZ= cubeSat.getMagnetometer(2);

```

### `void setRGB(uint8_t)`
A função setRGB configura os LEDs RGB presentes na placa de interface de acordo com a cor definida pelo usuário. Essa cor pode ser definida ao se utilizar seu nome em letras maiúsculas* ou o numero correspondente a cor como na Tabela a seguir.

| Nome| Valor|
| --- | :---: |
| OFF | 0 |
| RED | 1 |
| GREEN | 2 |
| BLUE | 3 |
| WHITE | 4 |
| PINK | 5 |

```C++

// Configura os RGB para a cor Azul
cubeSat.setRGB(BLUE);

// Configura os RGB para Desligado
cubeSat.setRGB(OFF);

```

*As cores em maiúsculo definidas na tabela se apresentam em cor diferente quando reconhecidas pela IDE do Arduino.

### `void setLed(uint8_t, uint8_t)`
Essa função deve ser utilizada para configurar os 4x LEDs brancos de visualização, localizados na placa de Interface. O estado do LED deve ser defino como `HIGH` ou `LOW`, e seu endereço pode ser defino usando seu nome ou valor correspondente, como descrito na tabela a seguir.

| Nome| Valor|
| --- |   :---:  |
| L1 | 1 |
| L2 | 2 |
| L3 | 3 |
| L4 | 4 |

```C++
// Confiura o LED 1 ligado por 1 segundo, e o desliga logo em seguida.
canSat.setLed(L1, HIGH);
delay(1000);
canSat.setLed(L1, LOW);

// Confiura o LED 3 como ligado 
canSat.setLed(3, HIGH);

// Aciona todos os LEDs Branco
canSat.setLed(ALL);

// Desliga todos os LEDs Brancos
canSat.setLed(ALL_OFF);

```
### `void buzzer(uint16_t)`
Essa função pode ser utilizada para acionar o buzzer por uma duração de tempo específica. A duração da sirene deve ser descrita em milisegundos.

```C++
// Configura a sirene ligada por 7 segundos.
canSat.buzzer(7000);

```

### `void doBeeps(uint8_t, uint16_t, uint16_t)`
A função doBeeps pode ser utilizada para acionar o sirene múltiplas vezes em uma sequência pré-definda. Nesse caso, devem ser descritas a quantidade de repetições `times`, a duração de acionamento `duration` e o intervalo entre cada acionamento `interval`.

```C++
// Por 5 vezes consecultivas, a sirene será acionada por 3 segundos, e ficará desligada durante 1 segundo. 
cubeSat.doBeeps(5,3000,1000);

```

### `void toggleSiren()`
A função toggleSiren pode ser utilizada para alterar o estado da sirene em ativado e desativado. Em ativado, a sirene fará dois acionamentos a cada 1. segundo. Quando desligada, nenhum sinal sonoro será emitido.

```C++
// Alterna o estado da sirene. 
canSat.toggleSiren();
```

### `SirenState_t getSirenState()`
A função getSirenState deve ser utilizada para retornar o estado atual da sirene. A tabela a seguir descreve todos as condições possíveis.

| Nome| Valor| Descrição|
| --- |   :---:  | :---:|
| ALARM_OFF | 0 | A sirene está desligada
| ALARM_SIREN | 1 | A sirene está ativada
| ALARM_ERROR | 2 | Erro de inicialização
| ALARM_LOW_BATTERY| 3 | Indicação de baixa bateria

```C++
// Retorna o estado atual da sirene e armazena em uma variável do tipo int.
int estadoSirene = cubeSat.getSirenState();
```

### `uint32_t getSerialNumber()`
A função getSerialNumber deve ser utilizada para retornar um valor do tipo float, correspondente ao número de série do Kit. 

```C++
// Retorna o número de série do kit e armazena em uma variável do tipo long.
long numSerie= canSat.getSerialNumber();
```
### `SDStatus_t getSDStatus()`
A função getSDStatus deve ser utilizada para retornar o estado atual da cartão SD. A tabela a seguir descreve todos as condições possíveis.

| Nome| Valor| Descrição|
| --- |   :---:  | :---:|
| NO_SD | 0 | Cartão μSD não conectado ou não reconhecido
| SD_CONNECTED | 1 | Cartão μSD Conectado
| SD_RECORDING | 2 | Cartão μSD em armazenamento
| SD_ERROR | 3 | Erro no cartão μSD

```C++
// Retorna o estado atual do cartão uSD e armazena em uma variável do tipo int.
int estadoSD = cubeSat.getSDStatus();
```

### `void createSDLogTask()`

Essa função somente deve ser utilizada quando você deseja utilizar o salvamento de dados em background que já foi desenvolvido para o seu Kit. Ela deve estar no seu `void setup()` para criar a **Thread**, ou a aplicação em paralelo ao seu código, que realizará o armazenamento dos dados. 

**Atenção:** Essa função apenas inicializa a tarefa de armazenamento, para começar a gravação utilize a função [void toggleSD()]()

Para utilizar as funções que permitem que você mesmo controle o tempo de armazenamento veja [void createLogOnSD()]()

```C++
void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  cubeSat.createSDLogTask();
}
```

### `void toggleSD()`

Essa função somente deve ser utilizada se você já utilizou `createSDLogTask()` no seu `void setup()` para criar a **Thread**, ou a aplicação em paralelo ao seu código, que realizará o armazenamento dos dados. 

**Atenção:** Essa função é um **toggle**, quando excecutada uma vez inicializa a gravação e quando executada novamente finaliza. 

```C++
void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  cubeSat.createSDLogTask();
}
void loop(){
  //Liga a gravação a cada meio segundo por 30 segundos e depois desliga
  cubeSat.toggleSD();
  delay(30000);
  cubeSat.toggleSD();
}
```
Verifique os [Conceitos Avaçados](https://) para modificar a função que define o que é armazenado pelo sistema.


### `void createLogOnSD()`

Essa função somente deve ser utilizada quando você deseja utilizar o armazenamento de dados. Ela deve estar no seu `void setup()` para criar o arquivo em seu cartão SD onde será realizado o armazenamento. 

**Atenção:** Essa função apenas inicializa o arquivo de armazenamento, para começar a gravação utilize a função [void logOnSDFile()](https://github.com/pion-labs/pion-educational-kits/wiki/Documenta%C3%A7%C3%A3o-do-Software/_edit#void-logonsdfile)

```C++
void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  cubeSat.createLogOnSD();
}
```
Verifique os [Conceitos Avaçados](https://github.com/pion-labs/pion-educational-kits/wiki/Conceitos-Avaçados) para modificar a função que define o que é armazenado pelo sistema e o cabeçalho do seu arquivo.

### `void logOnSDFile()`

Essa função somente deve ser utilizada se você já utilizou `createLogOnSD()` no seu `void setup()`. Ela adiciona uma nova linha ao arquivo que foi criado anteriormente com a chamada da função `createLogOnSD()`.

**Atenção:** Verifique os [Conceitos Avaçados](https://github.com/pion-labs/pion-educational-kits/wiki/Conceitos-Avaçados) para modificar a função que define o que é armazenado pelo sistema e adicionar seus dados.

```C++
void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  cubeSat.createLogOnSD();
}

void loop(){
  // Salva uma nova linha com dados no seu arquivo a cada 1000 millisegundos ou 1 segundo
  cubeSat.logOnSDFile();
  delay(1000);
}
```
