 #include <SoftwareSerial.h> 
 #define DEBUG true
  
 SoftwareSerial esp8266(2,3); // connect the TX line from the esp to the Arduino's pin 2 // and the RX line from the esp to the Arduino's pin 3 
 int counter; 
 int connectionId; 
 void setup() { 
  
  Serial.begin(74880); 
  esp8266.begin(115200); // check the baud rate it may be different 
  pinMode(13,OUTPUT); // connect Anode LED pin 12 and Cathode to Ground pin 
  digitalWrite(13,LOW); 
  delay(1000); 
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module 
  sendData("AT+CWMODE=2\r\n",2000,DEBUG); // configure as access point 
  sendData("AT+CIFSR\r\n",2000,DEBUG); // get ip address 
  sendData("AT+CIPMUX=1\r\n",2000,DEBUG); // configure for multiple connections 
  sendData("AT+CIPSERVER=1,80\r\n",2000,DEBUG); // turn on server on port 80 
  
  } 
  
  void loop() { 
    
    if(esp8266.available()) // check if the esp is sending a message 
    
    { 
      if(esp8266.find("+IPD,")) 
      { 
        delay(1000); // wait for the serial buffer to fill up (read all the serial data) // get the connection id so that we can then disconnect 
        
        int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns // the ASCII decimal value and 0 (the first decimal number) starts at 48 
        
        String t; 
        t = esp8266.readStringUntil('\r'); 
        t.replace("GET /?", ""); 
        t.replace(" HTTP/1.1", ""); 
        
        Serial.print(t); 
        
        if (t.indexOf("p") > 0) { 
          manageLED(); } 
          else if (t.indexOf("s") > 0) { 
            chkStates(); 
            } 
            else { 
              tryAgain(); 
              } 
              } 
              } 
              } 
              void tryAgain() { 
                String webpage = String("Something went wrong please try again"); 
                sendHTTPResponse(connectionId, webpage); 
                } 
                void manageLED() { 
                                  String webpage = String("Something went wrong please try again"); 
                sendHTTPResponse(connectionId, webpage); 
                  Serial.print("manage led called"); 
                  esp8266.find("p"); // advance cursor to "pin=" String webpage = ""; 
                  
                  if ( counter % 2 == 0) { //even 
                    digitalWrite(13, HIGH); 
                    webpage = String("Led Turned ON"); 
                    } 
                    else { //odd 
                      digitalWrite(13, LOW); 
                      webpage = String("Led Turned OFF"); 
                      } 
                      counter++; 
                      // generate web page 
                      sendHTTPResponse(connectionId, webpage); 
                      } 
                      void chkStates() { 
                        Serial.print("check status called"); 
                        String states = ""; 
                        if ( counter % 2 == 0) { //even it means led is off 
                          states = "{ state: OFF }"; 
                          } 
                          else { //odd it means led if on 
                            states = "{ state : ON }"; 
                            } 
                            
                            sendHTTPResponse(connectionId, states); 
                            } 
                            
                            void sendHTTPResponse(int connectionId, String content) {
                              String httpResponse; 
                              String httpHeader; // HTTP Header 
                              httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"; 
                              httpHeader += "Content-Length: "; 
                              httpHeader += content.length(); 
                              httpHeader += "\r\n"; httpHeader += "Connection: close\r\n\r\n"; 
                              httpResponse = httpHeader + content + " "; 
                              sendCIPData(connectionId, httpResponse); 
                              } 
                              
                              void sendCIPData(int connectionId, String data) { 
                                String cipSend = "AT+CIPSEND="; 
                                cipSend += connectionId; 
                                cipSend += ","; 
                                cipSend += data.length() ; 
                                cipSend += "\r\n"; 
                                sendData(cipSend, 1000, true); 
                                sendData(data, 1000, true); 
                                String closeCommand = "AT+CIPCLOSE="; 
                                closeCommand += connectionId; // append connection id 
                                closeCommand += "\r\n"; 
                                sendData(closeCommand, 1000, DEBUG); // close connection 
                                } 
                                String sendData(String command, const int timeout, boolean debug) 
                                { 
                                  String response = ""; 
                                esp8266.print(command); // send the read character to the esp8266 
                                long int time = millis(); 
                                while ( (time + timeout) > millis()) 
                                { 
                                  while (esp8266.available()) { // The esp has data so display its output to the serial window 
                                    char c = esp8266.read(); // read the next character. 
                                    response += c; 
                                    } 
                                    } if (debug) {
Serial.print(response); 
} 
return response; 
} 


