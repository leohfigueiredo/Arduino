#include <SPI.h>
#include <Ethernet.h>
 
//Define os parametros para o sensor ultrasonico HC-SR04
#define PINO_TRIGGER  6 //Porta ligada ao pino Trigger do sensor
#define PINO_ECHO     7 //Porta ligada ao pino Echo do sensor
//Inicializa o sensor ultrasonico

 
//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,88);          //Define o endereco IP
IPAddress gateway(192,168,1,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);
 
void setup()
{
  //Inicializa a interface de rede
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}
 
void loop() {
}
