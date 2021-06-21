# Especificações Técnicas

O `PION CanSat Educacional` é composto por um conjunto de placas empilháveis e integradas a uma estrutura impressa em 3D, respeitando os limites geométricos de um CanSat.

Nas próximas tabelas, serão apresentados características gerais e detalhes técnicos relacionados ao Hardware do CanSat Educacional.

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

Cada placa do CanSat possui três conectores empilháveis de 20 pinos. Os conectores tem por objetivo conectar, de maneira dinâmica, os diferentes subsistemas do CanSat, e permitir futuras customizações e/ou expansões. 

Os conectores são dividos em 3 grupos, A, B e C, sendo que cada um possui uma pinagem única.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCan_Pinout.png?alt=media&token=af59c395-4117-4231-a449-79afba5b9bc0)


<table>
<tr><th>Conector A </th><th>Conector B</th><th>Conector C</th></tr>
<tr><td>

| Terminal | Descrição | Terminal | Descrição |
|  :---: |   :---:   | :---: |   :---:   |
| 1 | VBAT - Tensão da Bateria| 11 | GPIO23 - VSPI MOSI|
| 2 | VBAT - Tensão da Bateria| 12 | GPIO23 - VSPI MOSI| 
| 3 | GPIO22 - I2C SCL | 13 | GND|
| 4 | GPIO22 - I2C SCL| 14 | GND|
| 5 | GPIO21 - I2C SDA| 15 | GND| 
| 6 | GPIO21 - I2C SDA| 16 | GND|
| 7 | GPIO19 - VSPI MISO| 17 | GND|
| 8 | GPIO19 - VSPI MISO| 18 | 3V3|
| 9 | GPIO18 - VSPI SCK| 19 | 3V3|
| 10 | GPIO18 - VSPI SCK| 20 | 3V3|

</td><td>

| Terminal | Descrição | Terminal | Descrição |
|  :---: |   :---:   | :---: |   :---:   |
| 1 | VBUS - 5V USB| 11 | GPI35 - Sensor de Bateria|
| 2 | VBUS - 5V USB| 12 | GPI35 - Sensor de Bateria| 
| 3 | VBUS - 5V USB| 13 | 3V3|
| 4 | VBUS - 5V USB| 14 | GND|
| 5 | GND| 15 | GND| 
| 6 | GND| 16 | GND|
| 7 | GND| 17 | GND|
| 8 | GND| 18 | 3V3|
| 9 | GND| 19 | 3V3|
| 10 | GND| 20 | 3V3|

</td>

<td>

| Terminal | Descrição | Terminal | Descrição |
|  :---: |   :---:   | :---: |   :---:   |
| 1 | GND| 11 | GPIO26 - ADC2_9 - DAC2 |
| 2 | GND| 12 | GPIO4 - ADC2_0 | 
| 3 | GND| 13 | GPIO34 - Sensor de Luminosidade |
| 4 | GND| 14 | GPIO5 - VSPI CS |
| 5 | GPIO14 - ADC2_6| 15 | GPIO16 - UART2 RX | 
| 6 | GPIO13 - ADC2_4 | 16 | GPI36 - ADC1_0  |
| 7 | GPIO17 - UART2 TX | 17 | GPIO27 - ADC2_7 |
| 8 | GND| 18 | GND|
| 9 | GPIO2 - ADC2_2| 19 | GND|
| 10 | GPIO25 - Buzzer (Sirene)  | 20 | GND|

</td></tr> </table>

# Dimensões

## Dimensões - Estrutura 3D

A estrutura do PION CanSat Educacional foi projetada para acomodar, integrar e proteger a eletrônica embarcada do Kit. Impressa em 3D com material PLA, a estrutura segue o formato de um CanSat.

|   Dimensões Gerais |
|:---    |
| **Comprimento:** 100 mm | 
| **Diâmetro:** 66 mm    | 

A vista superior da estrutura central esta representada a seguir.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCan_Structure.png?alt=media&token=07910d55-afaf-46d5-9d46-a0e681d86a1c) 

## Dimensões - Placas

As quatro placas que compõem o Kit educacional possuem as mesmas dimensões, permitindo o adequadro empilhamento e integração com a estrutura.

![](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCan_Dimensions.png?alt=media&token=6962ac7b-37d8-4034-b735-3717fbda45db)

