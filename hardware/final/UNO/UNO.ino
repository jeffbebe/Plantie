#include<dht.h> //library for temp/humidity sensor
dht DHT;

#define DHT11_PIN 2 //pin for temperature and hum sensor

String serialMessage = "";
bool stringComplete = false;

void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}


void loop()
{

int chk = DHT.read11(DHT11_PIN); //reading from temp/humidity sensor

//When there is something in serial buffer
while (Serial.available()) 
    {
        char serialChar = Serial.read(); //gets one byte from serial buffer
        if (serialChar == '<')  //if < is the beginning of the received char reset the buffer
        {
            serialMessage = "";
        }
        else if (serialChar == '>')
        {
            stringComplete = true;
        }
        else
        {
            //Append the message within specified ascii section 
            if ((serialChar >= 48 && serialChar <= 122) || serialChar == ',') 
                serialMessage += serialChar;
        }
    }

    //Things to do when we received a command
    if( stringComplete == true)
    {
      if( serialMessage == "Water")
      {
         digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
      if(serialMessage == "Fertilise")
      {
         digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      }
      if(serialMessage == "Fertilise")
      {
        //temperature and humidity
        Serial.print("<t"+ String(int(DHT.temperature))+ ";h"+ String(int(DHT.humidity))+ ">");
        
      }
      //Serial.println("<HelloFromUNO>");

      stringComplete = false;
      delay(100);

    }
  
  
//     int val = 0; //= ArduinoUno.parseFloat();
//     val = ArduinoUno.read();
//     if(val != "-1")
//       {
//       Serial.print("Incomming data: ");
//       Serial.println(val);
//       if( val == '\n')
//        {
//         Serial.println("slash n detected");
//         val = "";
//        }

   }
  
//void writeString(String stringData) { // Used to serially push out a String with Serial.write()
//
//  for (int i = 0; i < stringData.length(); i++)
//  {
//    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
//  }
//
//}// end writeString
