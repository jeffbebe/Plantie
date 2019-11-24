
void setup(){

  pinMode(LED_BUILTIN, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
}
String serialMessage = "";
bool stringComplete = false;
void loop(){


while (Serial.available()) // jesli cos ma w buforze
    {
        char serialChar = Serial.read(); // zczytaj znak
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
    }
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
      Serial.println("<HelloFromUNO>");
      delay(1);
      //Serial.println("<HelloFromUNO>");
      //Serial.print("Received text: " );
      //Serial.println(serialMessage);
      stringComplete = false;
      //Serial.println(serialMessage);

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
