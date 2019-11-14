#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(3, 2); //(rxPin, txPin);


void setup(){

	pinMode(3,INPUT);
	pinMode(2,OUTPUT);
  Serial.begin(115200); //debug
  NodeMCU.begin(115200);
  
}

String receivedFromUno;
void loop(){
	//String i = "Hello";
 // int i = 10;
  Serial.print("Sending data to arduino: " );
  //Serial.println(i);
  Serial.println("<Hello>");
  
	//NodeMCU.print(i);
  NodeMCU.println("<Hello>");
 

   if (NodeMCU.available() > 0)
   {
    receivedFromUno = NodeMCU.readStringUntil('\n');
    Serial.print("Received from arduino: ");
    Serial.println(receivedFromUno);
    
   }
	delay(1000); //do skorygowania
}
