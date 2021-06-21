# Conceitos Avançados para a Utilização

As funções a seguir são as funções padrão de criação de cabeçalho de arquivo e de criação de linhas no arquivo do cartão SD. Essas funções podem ser sobrescritas pelo usuário para adicionar ou remover valores de acordo com o que é necessário.

```C++
void createFileFirstLine(fs::FS &fs, const char * path){
    Serial.printf("Escrevendo em: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Falha ao abrir para escrita");
        return;
    }
    const char * message = "tempo(ms),temperatura(C),umidade(%),pressao(Pa),co2(ppm),luminosidade(%),acelX(m/s2),accelY,acelZ,giroX(graus/s),giroY,giroZ,magX(uT),magY,magZ,bateria(%)";
    if(file.println(message)){
        Serial.println("Escrita Começou");
    } else {
        Serial.println("Falha na escrita");
    }
    file.close();
}
```

```C++
void appendFile(fs::FS &fs, const char * path, TickType_t time){
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Falha ao abrir para gravacao");
        return;
    }
    file.print(time);
    file.write(',');
    file.print(Sensors::temperature);
    file.write(',');
    file.print(Sensors::humidity);
    file.write(',');
    file.print(Sensors::pressure);
    file.write(',');
    file.print(Sensors::CO2Level);
    file.write(',');
    file.print(Sensors::luminosity);
    file.write(',');
    file.print(Sensors::accel[0]);
    file.write(',');
    file.print(Sensors::accel[1]);
    file.write(',');
    file.print(Sensors::accel[2]);
    file.write(',');
    file.print(Sensors::gyro[0]);
    file.write(',');
    file.print(Sensors::gyro[1]);
    file.write(',');
    file.print(Sensors::gyro[2]);
    file.write(',');
    file.print(Sensors::mag[0]);
    file.write(',');
    file.print(Sensors::mag[1]);
    file.write(',');
    file.print(Sensors::mag[2]);
    file.write(',');
    file.println(System::battery);
    file.close();
}
```