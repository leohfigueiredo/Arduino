#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 #include <Wire.h>          
 #include <PortExpander_I2C.h>
 PortExpander_I2C placa(0x3F);
 

const char *ssid = ""; //  SSID da sua rede
const char *password = ""; // senha da sua rede

//IPAddress ip(192,168,9,28);
IPAddress ip(192,168,1,10); // ip atribuido ao módulo
IPAddress gateway(192,168,1,1); // base ip da sua rede
IPAddress subnet(255,255,255,0);

     int pin_SDA = 0;
     int pin_SCL = 2;

WiFiServer server(80); // porta para entrada externa
const int rele1 = 16;
const int rele2 = 14;
String header;

const char* APssid = "CARLOSKWIEK.COM.BR"; // para mudar o nome da placa na rede
const char* APpassword = "12345678"; // senha para conexão à placa

void setup ( void ) {
              
  

   Wire.begin(pin_SDA, pin_SCL);
   placa.init();

  pinMode ( rele1, OUTPUT );
  digitalWrite ( rele1, 1 );
  
  pinMode ( rele2, OUTPUT );
  digitalWrite ( rele2, 1 );

// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("creating ");
  Serial.println(APssid);
  
  //WiFi.softAP(APssid);
  int channel = 2;
  WiFi.softAP(APssid, APpassword, channel);
  WiFi.begin(ssid, password);
  WiFi.config( ip,  gateway,  subnet);
  

  Serial.begin ( 115200 );
  delay(10000);

  Serial.println();
  Serial.println();
  Serial.print("Conectando a...");
  Serial.println();
  Serial.println(ssid);
  
  
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 15000 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected a " );
  Serial.println();
  Serial.println ( ssid );

  server.begin();
  Serial.print ( "Server Inicializado" );
  Serial.println();
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  

}

void loop ( void ) {
 //String buf = "";
    int estado_rele1 = digitalRead(rele1);
   // Serial.println(estado_rele1);
 
 // Listenning for new clients
  WiFiClient client = server.available();


  if (client) {
    Serial.println("Novo Cliente");
       
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
      // String req = client.readStringUntil('\r');
      // Serial.print(req);
  
        if (c == '\n' && blank_line) {
              // Serial.print(header);
          
             client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            //client.println("Refresh: 10");  // refresh the page automatically every 10 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");

            client.println("");
            
            if(estado_rele1 == 0)
            client.println("Rele 1 esta ligado");
            else if(estado_rele1 == 1)
            client.println("Rele 1 esta Desligado");
            
                
                
                 String buf = "";
                
                  
                  //buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
                
                    buf += "<head>\r\n";
                    buf += "   <title>esp8266 webserver</title>\r\n";
                    buf += "</head>\r\n";
                    buf += "<body>\r\n";
                    buf += "<h1><a href=\"http://www.carloskwiek.com.br/wireless-ct-8f6da\"><span style=\"color:#000000;\">ESP8266</span></a></h1>\r\n";
                
                  
                  buf += "<h3> ESP8266 CARLOSKWIEK.COM.BR</h3>";
                  buf += "<p>RELE1 <a href=\"?function=Rele1_on\"><button>ON</button></a> <a href=\"?function=Rele1_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE2 <a href=\"?function=Rele2_on\"><button>ON</button></a> <a href=\"?function=Rele2_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE3 <a href=\"?function=Rele3_on\"><button>ON</button></a> <a href=\"?function=Rele3_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE4 <a href=\"?function=Rele4_on\"><button>ON</button></a> <a href=\"?function=Rele4_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE5 <a href=\"?function=Rele5_on\"><button>ON</button></a> <a href=\"?function=Rele5_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE6 <a href=\"?function=Rele6_on\"><button>ON</button></a> <a href=\"?function=Rele6_off\"><button>OFF</button></a></p>";
                  buf += "<p>RELE7 <a href=\"?function=Rele7_on\"><button>ON</button></a> <a href=\"?function=Rele7_off\"><button>OFF</button></a></p>";
                  buf += "<p>OnAll <a href=\"?function=OnAll_on\"><button>ON</button></a> <a href=\"?function=OnAll_off\"><button>OFF</button></a></p>";
                  buf += "<h4>Carloskwiek</h4>";
                  buf += "</html>\n";
                  
                 //  client.println ("<button style=\"width:300px;height:40px;color:green;background-color:#87CEFB\"");
                 client.print(buf);
                
               // buf +=("<button style=\"width:300px;height:40px;color:green;background-color:#87CEFB\"");
                // client.println("<button style=\"width:120px;height:40px;color:green;background-color:#87CEFB\"");
           
                  //client.flush();

                  if (header.indexOf("Rele1_on") != -1){
                        placa.digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
                    }
                  else if (header.indexOf("Rele1_off") != -1){
                        placa.digitalWrite(3,LOW );   // turn the LED on (HIGH is the voltage level)
                  }
                  
                 else if (header.indexOf("Rele2_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele2_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)


                 else if (header.indexOf("Rele3_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele3_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele4_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele4_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
                  
                  else if (header.indexOf("Rele5_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele5_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele6_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele6_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele7_on") != -1)
                        {
                          //digitalWrite(rele2, 0);
                           placa.digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
                           int valor_pino = placa.digitalRead(7);
                           Serial.println(valor_pino);
                             if(valor_pino==1)
                             {
                                client.print("Rele 7 esta ligado");
                             }
                        }
                        
                  else if (header.indexOf("Rele7_off") != -1)
                        {
                          //digitalWrite(rele2, 1);
                          placa.digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
                          int valor_pino = placa.digitalRead(7);
                          Serial.println(valor_pino);
                              if(valor_pino==0)
                              {
                                 Serial.print("Rele 7 esta desligado");
                                 client.print("Rele 7 OFF");
                                
                              }
                       
                        }
                        

                  else if (header.indexOf("OnAll_on") != -1)
                    {//digitalWrite(rele2, 0);
                        placa.digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level
                        placa.digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
                    }
    
                  else if (header.indexOf("OnAll_off") != -1)
                   {
                        //digitalWrite(rele2, 1);
                        placa.digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level
                        placa.digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
                   }
                    
   
                    
                  else {
                    Serial.println("invalid request");
                  //  client.stop();
                  }
                 // Serial.println("Client disonnected");
            
        header = "";
        break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");

  }
                   
                 
  }
