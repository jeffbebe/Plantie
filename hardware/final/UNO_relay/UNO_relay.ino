int relayPin = 3;
void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(relayPin, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.


}


void loop()
{   digitalWrite(relayPin,HIGH);
  delay(100);
  digitalWrite(relayPin,HIGH);
 
  delay(500);
 
}
