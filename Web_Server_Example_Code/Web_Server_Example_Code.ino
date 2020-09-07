//Leonardo
//Serial_ & dbgTerminal = Serial;
//HardwareSerial & espSerial = Serial1;

////UNO & M328P
//#include <SoftwareSerial.h>
//SoftwareSerial dbgTerminal(10, 11); // RX, TX
//HardwareSerial & espSerial = Serial;


//MEGA2560 
HardwareSerial & monitor = Serial;
HardwareSerial & esp_serial = Serial1;

// set pin numbers:
const int ledPin =  13;      // the number of the LED pin

const int relay1 =  22;
const int relay2 =  23;
const int relay3 =  24;
const int relay4 =  25;

const int ESP8266_CHPD = 8;

// Variables will change:
int ledState = HIGH;             // ledState used to set the LED

#define BUFFER_SIZE 128
char buffer[BUFFER_SIZE];


int result = 0;
int OK = 1;
int TIMEOUT = 2 ;
int CANCEL = 3;
int NOT_FOUND = 4;

int i;
int m=0;
int lp = 0;

char inputChar[500];
int len = 0;

String ssid = "LudwigEFigueiredo";
String pwd = "41992549713";
String serverip="192.168.1.10";
String port="80";
String cmd;
String myIP;

int currentID;

int ch_id, packet_len;
char *pb;


void(* resetFunc) (void) = 0;                          //declare reset function at address 0

void setup() { 
  pinMode(ledPin, OUTPUT); 
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  pinMode(ESP8266_CHPD, OUTPUT);
  digitalWrite(ESP8266_CHPD,HIGH);
  
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW);
  digitalWrite(relay4,LOW);
      
  monitor.begin(115200);           // Serial monitor
  esp_serial.begin(115200);             // ESP8266
    
  //while (!dbgTerminal) {
   // ; // wait for serial port to connect. Needed for Leonardo only
  //}

  monitor.println(F("\nESP8266 WebServer Test 0.22"));
  //hardReset();
  delay(1000);
  
  
  /* RESET Module */
  
   
  esp_serial.println("AT+RST\r\n");                     // Software Reset 
  monitor.print("\nAT+RST");
  
  result = CheckResponse();                         // Check "OK" 
  if(result == OK){
    Serial.print(" OK");
    delay(300);
  }
  else{
    Serial.print(" ERROR");
    delay(2000);       
    resetFunc();   
  }
  
  
  
        
  SET_MODE:
      esp_serial.println("AT+CWMODE=1\r\n");                // Set Mode  
      monitor.print("\nAT+CWMODE=1");
  
      result = CheckResponse();                         // Check "OK" 
      if(result == OK){
        Serial.print(" OK");
        delay(200);
      }
      else{
        Serial.print(" ERROR");
        delay(1000);
        goto SET_MODE;
      }
      
      
  DISCONNECT_AP:
     esp_serial.println("AT+CWQAP\r\n");                    // Disconnect AP 
      monitor.print("\nAT+CWQAP");
  
      result = CheckResponse();                         // Check "OK" 
      if(result == OK){
        Serial.print(" OK");
        delay(300);
      }
      else{
        Serial.print(" ERROR");
        delay(1000);       
        goto DISCONNECT_AP;  
      }
  
  
  
  CONNECT_WIFI:
  
      cmd = "AT+CWJAP=" + String("\"") + ssid + String("\"") + String(",")+String("\"") + pwd + String("\"");
      esp_serial.println(cmd);                    // Connect AP 
      monitor.print("\n"+cmd);
  
      result = CheckResponse();                         // Check "OK" 
      if(result == OK){
        Serial.print(" OK");
        delay(300);      
      }
      else{
        Serial.print(" ERROR");
        delay(1000);  
        goto CONNECT_WIFI;  
          
      }
      
      
 SET_MULTIPLE:
     esp_serial.println("AT+CIPMUX=1");                 // Multiple Connnect 
      monitor.print("\nAT+CIPMUX=1");
  
      result = CheckResponse();                         // Check "OK" 
      if(result == OK){
        Serial.print(" OK");
        delay(300);
      }
      else{
        Serial.print(" ERROR");
        delay(1000);       
        goto SET_MULTIPLE;  
      }      
      
    
  START_SERVER:
      cmd = "AT+CIPSERVER=" + String("1") + String(",") + port;
      
      esp_serial.println(cmd);                          // Start Server 
      monitor.print("\n"+cmd);
  
      result = CheckResponse();                         // Check "OK" 
      if(result == OK){
        Serial.print(" OK");
        delay(200);
      }
      else{
        Serial.print(" ERROR");        
        delay(1000); 
      }      
      
     
  CHECK_IP:
      esp_serial.println("AT+CIFSR");                 // Multiple Connnect 
      monitor.print("\nAT+CIFSR");
      
      readSerial();  
      //monitor.print(inputChar);   
      readSerial();  
      //monitor.print(inputChar);
      readSerial();  
      monitor.print(inputChar);
      
      for(unsigned char i=0;i<2;i++){     
        esp_serial.println("AT+CIPCLOSE");                // Close All Socket 
        monitor.print("\nAT+CIPCLOSE");
        result = CheckResponse();                         // Check "OK" 
        if(result == OK){
          Serial.print(" OK");
          delay(200);
        }
        else{
          Serial.print(" ERROR");
          delay(200);       
          //goto START_SERVER;  
        }          
     }
      
    
  digitalWrite(ledPin,ledState);  
  delay(3000);
           
}// Setup





void loop() {
   
  esp_serial.readBytesUntil('\n', buffer, BUFFER_SIZE);
  
  if(strncmp(buffer, "+IPD,", 5)==0) {
    
     //monitor.print("\nBuffer");
    // request: +IPD,ch,len:data
    sscanf(buffer+5, "%d,%d", &ch_id, &packet_len);
    if (packet_len > 0) {
      //monitor.print("\nlen > 0");
      // read serial until packet_len character received
      // start from :
      pb = buffer+5;
      while(*pb!=':') pb++;
      pb++;
      
      if (strncmp(pb, "GET /led", 8) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
 
        delay(100);
        clearSerialBuffer();
             
       if (ledState == LOW)
          ledState = HIGH;
       else
          ledState = LOW;
        digitalWrite(ledPin, ledState);
        
        delay(3000);
        homepage(ch_id);        
        
      } 
      
      
      
      if (strncmp(pb, "GET /?relay1on", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay1, HIGH);
        homepage(ch_id);              
      } 
           
      if (strncmp(pb, "GET /?relay1off", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay1, LOW);
        homepage(ch_id);              
      } 
      
      if (strncmp(pb, "GET /?relay2on", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay2, HIGH);
        homepage(ch_id);              
      } 
            
      if (strncmp(pb, "GET /?relay2off", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay2, LOW);
        homepage(ch_id);              
      } 
      
      
      if (strncmp(pb, "GET /?relay3on", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay3, HIGH);
        homepage(ch_id);              
      } 
            
      if (strncmp(pb, "GET /?relay3off", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay3, LOW);
        homepage(ch_id);              
      } 
      
      if (strncmp(pb, "GET /?relay4on", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay4, HIGH);
        homepage(ch_id);              
      } 
            
      if (strncmp(pb, "GET /?relay4off", 14) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get led from ch :" );
        monitor.println(ch_id);
        delay(100);
        clearSerialBuffer();            
        digitalWrite(relay4, LOW);
        homepage(ch_id);              
      } 
      
       //else if (strncmp(pb, "GET / ", 6) == 0) {
      if (strncmp(pb, "GET / ", 6) == 0) {
        monitor.print(millis());
        monitor.print(" : ");
        monitor.println(buffer);
        monitor.print( "get Status from ch:" );
        monitor.println(ch_id);
        
        delay(100);
        clearSerialBuffer();
        homepage(ch_id);             
      }
       
    }
    
  }
  //monitor.print(buffer);
  clearBuffer();
  
  //lp++;
  monitor.print( "\nLoop "); 
  //monitor.print(lp);
    
}





void homepage(int ch_id) {
  String Header;

  Header =  "HTTP/1.1 200 OK\r\n";
  Header += "Content-Type: text/html\r\n";
  Header += "Connection: close\r\n";  
  //Header += "Refresh: 5\r\n";
  
  String Content;
  Content = "<html><header><title>ESP8266 Webserver</title></header>";
  Content += "<center> <p> <h1 style=\"color: #FF0; background: #000\">ESP8266 WiFi Web Server 0.22  </h1></p>";
  
  Content += "<a href=\"/?relay1on\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 1 ON </font> </button> </a>";
  Content += "<a href=\"/?relay1off\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 1 OFF </font> </button> </a> <br/><br/>";
  
  Content += "<a href=\"/?relay2on\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 2 ON </font> </button> </a>";
  Content += "<a href=\"/?relay2off\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 2 OFF </font> </button> </a> <br/><br/>";
  
  Content += "<a href=\"/?relay3on\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 3 ON </font> </button> </a>";
  Content += "<a href=\"/?relay3off\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 3 OFF </font> </button> </a> <br/><br/>";
  
  Content += "<a href=\"/?relay4on\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 4 ON </font> </button> </a>";
  Content += "<a href=\"/?relay4off\"> <button style=\"width:360px;height:120px\"> <font size=\"7\">Device 4 OFF </font> </button> </a> <br/><br/>";
  
  
  Content += "<hr> <p> By <a href=\"http://androidcontrol.blogspot.com\"></p><p style=\"font-family:arial;color:blue;font-size:28px;\">Android Control Blogspot</p></a>";
  
  Content += "</body></html>";
  
  //Content += "D";
  //Content += String(ledState);
  
  Header += "Content-Length: ";
  Header += (int)(Content.length());
  Header += "\r\n\r\n";
  
 START_SENT: 
  esp_serial.print("AT+CIPSEND=");
  esp_serial.print(ch_id);
  esp_serial.print(",");
  esp_serial.println(Header.length()+Content.length());
  
  monitor.print("AT+CIPSEND=");
  monitor.print(ch_id);
  monitor.print(",");
  monitor.println(Header.length()+Content.length());
  delay(10);                                        //*** effect Web page
 
  
  
  // for debug buffer serial error
  //while (espSerial.available() >0 )  {
  //  char c = espSerial.read();
  //  dbgTerminal.write(c);
  //  if (c == '>') {
  //      espSerial.print(Header);
  //      espSerial.print(Content);
  //  }
  //}
  
  if (esp_serial.find(">")) {
      esp_serial.print(Header);
      esp_serial.print(Content);
      delay(10);     
   } 

}



void clearSerialBuffer(void) {
       while ( esp_serial.available() > 0 ) {
         esp_serial.read();
       }
}


void clearBuffer(void) {
       for (int i = 0;i<BUFFER_SIZE;i++ ) {
         buffer[i]=0;
       }
}


int readSerial(){
  
  int i = 0;
  while(1){ 
    while (esp_serial.available() > 0){    
      char inChar = esp_serial.read();
      
      if(i > 0){
        if (inChar == '\n'){
          inputChar[i] = '\0';
          esp_serial.flush();
          return 0;
          //break;
        }
      }
      
      if(inChar!='\r'){
        inputChar[i] = inChar;
        i++;
      }
      
    }
  } 
  
}


int CheckResponse(){
  
  for(m=0;m<500;m++){
      if(esp_serial.read()=='K'){         // Check "OK"      
      return OK;
      }
      delay(10);
  }
  return TIMEOUT;  
}


