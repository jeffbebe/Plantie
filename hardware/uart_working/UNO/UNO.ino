
void setup(){

	Serial.begin(115200);
	

}
int incomingByte = 0; // for inco0ming serial data

void loop(){

String serialMessage = "";
bool stringComplete = false;
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
      //Serial.print("Received text: " );
      //Serial.println(serialMessage);
      stringComplete = false;
      
      //String outMessage = "HelloFromUno "; 
     // writeString(outMessage);
      int outInt = 88;
      //Serial.write(outInt);
      
      Serial.println("HelloFromUNO\n");
    }
  
  
//     int val = 0; //= ArduinoUno.parseFloat();
//     val = ArduinoUno.read();
//     if(val != "-1")
//       {
//       Serial.print("Incomming data: ");
//       Serial.println(val);
//       if( val == '\n')
//      	{
//         Serial.println("slash n detected");
//         val = "";
//        }
  delay(500);
   }
  
void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}// end writeString
