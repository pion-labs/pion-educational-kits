# Programando seu Kit

O seu `Kit Educacional PION` possui em sua Placa Controladora de Bordo um microcontrolador **Espressif ESP32**.

As placas de desenvolvimento que possuem o módulo **ESP32** utilizam microcontroladores que estão sendo cada vez mais utilizados para fins acadêmicos e industriais, especialmente na Internet das Coisas. Sua grande quantidade de saídas e entradas, aliado as conexões Bluetooth e WiFi, permitem aplicações mais diversas e complexas.

O código dos Kits Educacionais PION utiiliza do poder de processamento e da maior quantidade de núcleos do microcontrolador **ESP32** para executar todas as funções de Housekeeping e controle do seu Kit nas chamadas Threads do sistema operacional de tempo real FreeRTOS, tudo isso pode ser facilmente acessado e foi facilitado para o usuário por meio da biblioteca `PION_System.h` que é instalada junto com o suporte recomendado para o Ambiente de Desenvolvimento(IDE) do Arduino. Para ler a documentação de como utilizar as funções da biblioteca, [clique aqui](https://github.com/pion-labs/pion-educational-kits/wiki/Documentação-do-Software). Para saber como realizar a instação do suporte siga as intruções abaixo.

Há diversas formas de se programar um ESP32 e portanto, seu Kit Educacional PION, dentre elas podemos citar:
- IDE do Arduino com Instalação do Suporte para os Kits Educacionais PION **(Recomendado para todos os Usuários)**
- IDE do Arduino com Instalação do Suporte ao ESP32 + Bibliotecas dos sensores
- Platform.Io para ESP32 + Bibliotecas dos Sensores
- ESP-IDF **(Recomendado para usuários avançados em ESP32)**

# Instalação do Ambiente de Desenvolvimento(IDE) do Arduino

Antes de instalar a "Board" ou "Placa" `Pion Educational Kits` no seu Arduino 1.8.x ou superior, certifique-se de que você tem o Ambiente de Desenvolvimento(IDE) do Arduino instalado em seu computador, se não:

### [Faça aqui o Download da IDE do Arduino](https://www.arduino.cc/en/software)

# Instalando o suporte para o seu Kit Educacional PION

![Suporte para Kit Educacional PION](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCapa.png?alt=media&token=1cc89473-7967-4976-bda8-813fadd1ef8b)

Para obter a "Board" ou "Placa" Pion Educational Kits no seu Arduino 1.8 ou superior siga os seguintes passos:

## Primeiro Passo

Para começar, no canto superior esquerdo clique em **Arquivo** e depois em **Preferências** para abrir a janela a seguir:

![Preferências do Arduino](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FPreferencias-Blank.png?alt=media&token=a63cb16f-3ad3-4b60-b7b8-e2e7c35bd98f)

## Segundo Passo

Na janela de preferências clique no botão a direita de URLs Adicionais para Gerenciadores de Placas, mostrado com uma seta vermelha na imagem a seguir para adicionar o suporte dos Kits PION ao arduino.

![Botão URLs Adicionais](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FPreferencias-Blank-Seta.png?alt=media&token=d0833cfd-8b91-485b-b2f7-43fbe858834b)

## Terceiro Passo

A seguinte janela deverá aparecer:

![URLs Adicionais](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FPreferencias-URL-Box.png?alt=media&token=1f121833-61be-477c-afa2-e5fab6cc5f6f)

Na janela de URLs Adicionais para Gerenciadores de Placas cole o Link a seguir:

`https://raw.githubusercontent.com/pion-labs/pion-educational-kits/main/package_pion_kit_index.json`

Se você já tiver algum outro suporte a placas adicionado, apenas coloque o link acima em uma nova linha pressionando enter.

Esse deve ser o resultado final:

![URLs Adicionais Link](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FPreferencias-URL-Box-Link.png?alt=media&token=dc9421e4-373c-42bd-b5a9-0c0af6d0fd84)

Apenas clique Ok nas duas janelas abertas para finalizar esse passo.

## Quarto Passo

Utilizando o botão Ferramentas na aba superior, coloque o mouse sobre a opção Placa: xxxxxx (Nome da ultima placa que você utilizou), para clicar na opção que aparecerá ao seu lado: `Gerenciador de Placas...`

![Gerenciador de Placas](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FBoads-Manager.png?alt=media&token=5982552a-8d18-40f4-b518-6b36ee95dde3)

Após aguardar o carregamento do Gerenciador de Placas a seguinte janela deve se abrir:

![Gerenciador de Placas](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FBoads-Manager-List.png?alt=media&token=47e3da57-7e4e-4013-96fd-fa2343850743)

Utilize a barra superior para Pesquisar por **PION** e posicione o mouse sobre o resultado **PION Educational Kits** para liberar o botão Instalar e clique nele para realizar a instalação da versão mais recente. A janela estará como na imagem a seguir:

![Gerenciador de Placas Instalação](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FBoards-Manager-PION-Installing.png?alt=media&token=da8d89dc-d4b3-4e33-96b5-202055888576)

Após a instalação, o gerenciador mostrará INSTALLED ou INSTALADO na tela como a seguir:

![Gerenciador de Placas Instalado](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FBoards-Manager-Installed.png?alt=media&token=3acc95da-4b59-4727-85a6-4d128a827680)

A partir desse momento você pode fechar as janelas abertas e verificar se as Placas PION CanSat e PION CubeSat estão disponíveis para escolha no menu como na imagem:

![Suporte para Kit Educacional PION](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FCapa.png?alt=media&token=1cc89473-7967-4976-bda8-813fadd1ef8b)

## Quinto passo 

A partir desse momento você já pode começar com o seu desenvolvimento seguindo nossos Exemplos e a Documentação:

### Exemplos

![Exemplos](https://firebasestorage.googleapis.com/v0/b/classroom-e67ad.appspot.com/o/Images%2FExamples.png?alt=media&token=e0c5694a-0228-4466-a0e6-f8ca6e3f3f77)

### Documentação

[Clique aqui para começar a ler a documentação](https://github.com/pion-labs/pion-educational-kits/wiki/Documentação-do-Software)