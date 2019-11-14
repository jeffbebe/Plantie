
#include <dht.h>
dht DHT;
int temp,humi;
#define DHT11_PIN A0
String str;
void setup(){
 Serial.begin(115200);
 //Serial1.begin(115200);
 delay(2000);
}
void loop()
{
  Serial.println("Uno data to send: ");
  DHT.read11(DHT11_PIN);
  humi=DHT.humidity;
  temp=DHT.temperature;
  Serial.print("H: ");
  Serial.print(humi); 
  Serial.print("% ");
  Serial.print(" T: ");
  Serial.print(temp); 
  Serial.print(char(176));
  Serial.println("C");
  str =String('H')+String(humi)+String('T')+String(temp);
  Serial.println(str);
 // Serial1.println(str);
  delay(5000);
}
