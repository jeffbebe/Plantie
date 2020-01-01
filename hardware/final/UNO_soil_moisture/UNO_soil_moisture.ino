int soilSensor = A2;
int soilSensorValue = 0; // variable to store the value coming from the sensor
void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
 
Serial.begin(9600); //sets serial port for communication

}


void loop()
{
soilSensorValue = analogRead(soilSensor); // read the value from the sensor
Serial.println(soilSensorValue); //prints the values coming from the sensor on the screen
delay(100);
}
