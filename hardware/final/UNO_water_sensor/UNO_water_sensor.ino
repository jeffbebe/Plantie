int waterLevelSensor = A1;
int waterLevelSensorValue = 0; // variable to store the value coming from the sensor
void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
 
Serial.begin(9600); //sets serial port for communication

}


void loop()
{
waterLevelSensorValue = analogRead(waterLevelSensor); // read the value from the sensor
Serial.println(waterLevelSensorValue); //prints the values coming from the sensor on the screen
delay(1000);
}
