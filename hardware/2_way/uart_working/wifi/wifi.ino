#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(3, 2); //(rxPin, txPin);
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval = 2000; //interval for sending data to the websocket server in ms

void setup(){

	pinMode(3,INPUT);
	pinMode(2,OUTPUT);
  Serial.begin(9600); //debug
  NodeMCU.begin(9600);
  
}
String receivedString;
String receivedFromUno;
String serialMessage = "";
bool stringComplete = false;
void loop(){
	//String i = "Hello";
 // int i = 10;
  currentMillis = millis();
  if (abs(currentMillis - previousMillis) >= interval) // to wasd=dasjbiafsdbiasdfbiujsad
            {
                previousMillis = currentMillis;
                //data = (String)analogRead(A0); //read adc values, this will give random value, since no sensor is connected.
                 Serial.print("Sending data to arduino: " );
                  //Serial.println(i);
                  Serial.println("<Hello>");
                  
                  //NodeMCU.print(i);
                  NodeMCU.println("<Hello>");
                 
                
//                   if (NodeMCU.available() > 0)
//                   {
//                    receivedFromUno = NodeMCU.readStringUntil('\n');
//                    
//                    Serial.print("Received from arduino: ");
//                    Serial.println(receivedFromUno);
//                    
//                    receivedFromUno = "";
//                   }

                    while (NodeMCU.available()) {
                        char serialChar = NodeMCU.read();  //gets one byte from serial buffer
                              if (serialChar == '<') // jesli jest poczatkiem to zresetuj stringa
                              {
                                  serialMessage = "";
                              }
                              else if (serialChar == '>')
                              {
                                  stringComplete = true;
                              }
                              else
                              {
                                  if ((serialChar >= 48 && serialChar <= 122) || serialChar == ',') // zbiera literki dopoki nie sklei calego stringa
                                      serialMessage += serialChar;
                              }
            
                        delay(2);  //slow looping to allow buffer to fill with next character
                      }
                     if( stringComplete == true)
                        {
                          
                          Serial.println("Received: " );  
                          //jakims chujem arduino dostaje czasem HelloReceived:HelloFromUNO wiec trzeba by wyjebac

                          delay(2); 
                          //Serial.println(serialMessage);
                          stringComplete = false;
                          Serial.println(serialMessage);
                           delay(1000);
                        }
                      
                    
//                      if (receivedString.length() >0) {
//                        Serial.println("Received: ");
//                        Serial.println(receivedString);  //so you can see the captured String
//                        //int n = readString.toInt();  //convert readString into a number
//                        //myservo.write(n);
//                        receivedString="";
//                      }

            }
 
	delay(1000); //do skorygowania
}
