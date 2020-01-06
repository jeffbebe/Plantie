




#include<dht.h> //library for temp/humidity sensor
dht DHT;

#define DHT11_PIN 2 //pin for temperature and hum sensor



//stuff for display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int waterLevelSensor = A1;
int waterLevelSensorValue = 0; // variable to store the value coming from the sensor
int percentageWaterLevelSensorValue = 0;

int lightSensor = A3;
int lightSensorValue = 0;
int percentageLightSensorValue = 0;
// variable to store the value coming from the sensor

int soilSensor = A2;
int soilSensorValue = 0; // variable to store the value coming from the sensor
int percentageSoilSensorValue = 0;


const int relayPin =12; //pin for pump relay

//stuff for incomming messages
String serialMessage = "";
bool stringComplete = false;

void drawText(int temp, int humidity);

void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
   pinMode(relayPin, OUTPUT);   // initialize digital pin relayPin as an output.
 digitalWrite(relayPin,HIGH);
  Serial.begin(9600);

  //###########display setup
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

}


void loop()
{

int chk = DHT.read11(DHT11_PIN); //reading from temp/humidity sensor
 //digitalWrite(relayPin,HIGH);
 drawText(DHT.temperature,DHT.humidity);

         lightSensorValue = analogRead(lightSensor); // read the value from the sensor
         percentageLightSensorValue = (lightSensorValue-65)*100L/(800-65); //(value-initialValue)*100/(maxValue-initialValue)
         if(percentageLightSensorValue<0)
         percentageLightSensorValue = 0;
     //    Serial.print("Light sensor in %:   " );
    //Serial.println(100-percentageLightSensorValue);


    soilSensorValue = analogRead(soilSensor); // read the value from the sensor
    percentageSoilSensorValue = (soilSensorValue-300)*100L/(1020-300); //(value-initialValue)*100/(maxValue-initialValue)
    if(percentageSoilSensorValue<0)
    percentageSoilSensorValue = 0;

    //Serial.print("Soil sensor in %:   " );
   // Serial.println(100-percentageSoilSensorValue);

   waterLevelSensorValue = analogRead(waterLevelSensor); // read the value from the sensor
    percentageWaterLevelSensorValue = (waterLevelSensorValue-300)*100L/(1020-300); //(value-initialValue)*100/(maxValue-initialValue)
    if(percentageWaterLevelSensorValue<0)
    percentageWaterLevelSensorValue = 0;
    //Serial.print("WaterLevel sensor in %:   " );
    //Serial.println(100-percentageWaterLevelSensorValue);

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
      if(serialMessage == "Water")
      {
         digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
         
         digitalWrite(relayPin,LOW);
         delay(100);
         digitalWrite(relayPin,HIGH);
      }

      if(serialMessage == "Update")
      {



         
        //<airt:;airh:;soil:;brig:;wat:>
        
        //temperature and humidity
        //Serial.print("<t"+ String(int(DHT.temperature))+ ";h"+ String(int(DHT.humidity))+ ">");
        Serial.print("<airt:"+ String(int(DHT.temperature))+ ";airh:"+ String(int(DHT.humidity))+";soil:"+(100-percentageSoilSensorValue)+";brig:"+(100-percentageLightSensorValue)+";wat:"+(100-percentageWaterLevelSensorValue)+";>");

       //  Serial.println(soilSensorValue); //prints the values coming from the sensor on the screen
       // Serial.println(lightSensorValue); //prints the values coming from the sensor on the screen
      //  Serial.println(waterLevelSensorValue); //prints the values coming from the sensor on the screen
      }
      //Serial.println("<HelloFromUNO>");

      stringComplete = false;
      delay(100);

    }
}
void drawText(int temp, int humidity) {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Plantie stats:");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
 display.setCursor(0,20);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("Temp: ");
  display.print(temp);
  display.print((char)167); //degree symbol is 248 but this one is better
  display.println("C");
  
  display.print("Humid: ");
  display.print(humidity);
  display.println("%");
  
  display.setTextSize(1);
  display.print("LastUpdate: ");
  display.println(temp*humidity);
  display.display();
  //delay(2000);
  display.clearDisplay();

  

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


  
//void writeString(String stringData) { // Used to serially push out a String with Serial.write()
//
//  for (int i = 0; i < stringData.length(); i++)
//  {
//    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
//  }
//
//}// end writeString
