#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <SoftwareSerial.h>

SoftwareSerial sw(2 ,3);

const char* ssid     = "";
const char* password = "";

WebSocketsServer webSocket = WebSocketsServer(81, "/", "chat");
 
void setup() {
 
 sw.begin(115200);
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 Serial.println("");
 
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // sprawdzanie co 500ms czy jestesmy polaczeni
 }
 // sprawdzenie czy sie poprawnie polaczyl
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 
  webSocket.begin();
  webSocket.onEvent(webSocketEvent); // wywola funkcje w nawiasie gdy cos sie stanie w websockecie, np pobierzemy dane 
}
 
void loop(void){ // void nie musi byc
  webSocket.loop(); // ?? sprawdzic co to dokladnie robi
  if (sw.available() > 0){ // jesli dane z arduino przychodza, to zrob to co nizej
    char c[] = {(char)sw.read()}; // zczytaj z seriala
    webSocket.broadcastTXT(c, sizeof(c)); // wyslij do strony
  }
}
// wysyla do arduino z socketa
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  Serial.println("WebSocket event");
  if (type == WStype_TEXT){
   for(int i = 0; i < length; i++) sw.print((char) payload[i]);
   sw.println();
  }
  if(type == WStype_CONNECTED){
    sw.println("Client connected");            
    webSocket.sendTXT(num, "Connected");
  }
  if(type == WStype_DISCONNECTED){
    sw.println("Client disconnected");
  }
}



// czesc do arduino
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


if (stringComplete){zrób coś}

// 