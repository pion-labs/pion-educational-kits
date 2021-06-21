# Especificações Técnicas

O `PION CubeSat Educacional` é composto por um conjunto de placas empilháveis e integradas a uma estrutura impressa em 3D, respeitando os limites geométricos de um CubeSat.

Nas próximas tabelas, serão apresentados características gerais e detalhes técnicos relacionados ao Hardware do Cubesat Educacional.

| Especificação| Descrição |
| --- |   :---:  |
| Microcontrolador | ESP32 (32-Bit / Dual Core / 240 MHz) |
| Tensão de Operação | 3.3 V |
| Bateria | Li-Po 3.7V / 400mah |
| Memória Flash | 4 Mb |
| Armazenamento Externo | Cartão microSD até 16 Gb |
| Wi-Fi| 802.11 b/g/n 2.4 GHz ~ 2.5 GHz  |
| Interface de Programação| Micro USB  |

## Limites de Operação

| Parâmetro| Limites|
| --- |   :---:  |
| Tensão GPIO  | 3.3 V |
| Corrente (3V3)| 600 mA |
| Corrente (GPIO)| 30 mA |

Para maiores informações, acesse o datasheet [ESP32](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf).

## Sensores

| Sensores| Faixa de Operação| Endereço I2C|
| --- |   :---:  |    :---:  |
| Temperatura|  -40 a 125°C  |  0x40  | 
| Umidade|  0 - 100 %  |  0x40  |
| Pressão|  300 - 1100 hPa | 0x76  |
| Luminosidade|  0 - 100 % | GPI34 |
| Gás Carbônico|  400 - 29206 ppm |  0x5A  |
| Giroscópio |  ±250, ±500, ±1000, e ±2000°/seg| 0x68  |
| Acelerômetro | ±2g, ±4g, ±8g e ±16g | 0x68   |
| Magnetômetro | ±4800 µT| 0x68   |
| Nível de Bateria|  0 - 100 % | GPI35 |


# Diagrama de Pinos
Cada placa do CubeSat possui um barramento de conectores empilháveis com 40 pinos. Os conectores tem por objetivo conectar, de maneira dinâmica, os diferentes subsistemas do CubeSat, e permitir futuras customizações e/ou expansões.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCube_Pinout.png?alt=media&token=c97748f9-1377-4f86-bc6a-69e2087c1fb3)

| Terminal | Descrição | Terminal | Descrição | Terminal | Descrição | Terminal | Descrição |
|  :---: |   :---:   | :---: |   :---:   |   :---:   |   :---:   |   :---:   |   :---:   |
| 1 | 3V3| 11 | N/C - Não Conectado| 21| N/C - Não Conectado| 31 | GPI34 - Sensor de Luminosidade|
| 2 | 3V3| 12 | GPIO4 - ADC2_0| 22| N/C - Não Conectado| 32 | GPIO22 - I2C SCL|
| 3 | GPIO19 - VSPI MISO| 13 | GPI35 - Sensor de Bateria| 23| GND| 33 | GND|
| 4 | GPIO23 - VSPI MOSI| 14 | GPIO25 - Buzzer (Sirene)| 24| GND| 34 | GND|
| 5 | GPIO18 - VSPI SCK| 15 | GPIO27 - ADC2_7| 25| N/C - Não Conectado| 35 | GPIO26 - ADC2_9 - DAC2|
| 6 | N/C - Não Conectado| 16 | GPIO14 - ADC2_6| 26 | N/C - Não Conectado| 36 | N/C - Não Conectado|
| 7 | GND| 17 | GPI36 - ADC1_0| 27 | VBUS - 5V USB| 37 | N/C - Não Conectado|
| 8 | GND| 18 | GPIO13 - ADC2_4| 28 | VBUS - 5V USB| 38 | GPIO5 - VSPI CS|
| 9 | N/C - Não Conectado| 19 | GPIO16 - UART2 RX| 29 | N/C - Não Conectado| 39 | VBAT - Tensão da Bateria|
| 10 | GPIO2 - ADC2_2| 20 | GPIO17 - UART2 TX| 30 | GPIO21 - I2C SDA| 40 | VBAT - Tensão da Bateria|

## Expansão

Além do barramento, o CubeSat possui uma área de expansão localizada placa de Computador de Bordo, permitindo maiores customizações.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCube_Expansion.png?alt=media&token=a8ba8295-fc1c-47ee-a833-a7a74f71068e)

# Dimensões

## Dimensões - Estrutura 3D

A estrutura do PION CubeSat Educacional foi projetada para acomodar, integrar e proteger a eletrônica embarcada do Kit. Impressa em 3D com material PLA, a estrutura segue o formato padrão de um CubeSat 1U com dimensões de 10 x 10 x 10 cm.

|   Dimensões Gerais |
|:---    |
| **Comprimento:** 100 mm | 
| **Largura:** 100 mm    | 
| **Altura:** 100 mm    | 

A vista superior da estrutura central esta representada a seguir.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCube_Structure.png?alt=media&token=1f0fb345-db9a-46ce-a21b-466399a87ed5)

## Dimensões - Placas

As quatro placas que compõem o Kit educacional possuem as mesmas dimensões, permitindo o adequadro empilhamento e integração com a estrutura.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCube_Dimensions.png?alt=media&token=ab082b84-c6dc-4123-afe4-a0aca58e96c4)

