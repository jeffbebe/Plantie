/*******************Esp8266_Websocket.ino****************************************/

#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <SoftwareSerial.h>



const int esp_led = 2;
//Wifi config
boolean handshakeFailed = 0;
String dataRecivedFromWeb = "";
String dataToSend = "";

char path[] = "/"; //identifier of this device


const char *ssid = "Internet";
const char *password = "dlink123";
char *host = "192.168.1.4"; 
 /*
const char *ssid = "Skynet";
const char *password = "Ziemniak";
char *host = "192.168.43.198"; //replace this ip address with the ip address of your Node.Js server

 
  const char *ssid = "RedmiX";
const char *password = "kamilkamil12";
char *host = "192.168.43.198"; //replace this ip address with the ip address of your Node.Js server
*/

const int espport = 3000;

WebSocketClient webSocketClient;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval = 2000; //interval for sending data to the websocket server in ms

// Use WiFiClient class to create TCP connections
WiFiClient client;

//Esp-arduino config
//Declaring the rx and tx Pin of ESP
const int rxPin = 3;
const int txPin = 2;
SoftwareSerial NodeMCU(rxPin, txPin); //(rxPin, txPin);
String dataReceivedFromUno;

String receivedString;
String receivedFromUno;
String serialMessage = "";
bool stringComplete = false;


//Method to connect to the websocket server
void wsconnect()
{
    if (client.connect(host, espport))
    {
        Serial.println("Connected");
    }
    else
    {
        Serial.println("Connection failed.");
        delay(1000);

        if (handshakeFailed)
        {
            handshakeFailed = 0;
            ESP.restart();
        }
        handshakeFailed = 1;
    }

    // Handshake with the server
    webSocketClient.path = path;
    webSocketClient.host = host;
    if (webSocketClient.handshake(client))
    {
        Serial.println("Handshake successful");
    }
    else
    {

        Serial.println("Handshake failed.");
        delay(4000);

        if (handshakeFailed)
        {
            handshakeFailed = 0;
            ESP.restart();
        }
        handshakeFailed = 1;
    }
}


void setup()
{
    //wifi config
    Serial.begin(9600); //for debuging
    pinMode(esp_led, INPUT); // Initialize the esp builtin led pin as an output

    delay(10);

    //Connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(1000);

    wsconnect();
    //  wifi_set_sleep_type(LIGHT_SLEEP_T);

    
    //esp-arduino config
     pinMode(rxPin,INPUT);
     pinMode(txPin,OUTPUT);
     NodeMCU.begin(9600);
}


void loop()
{

  //  if (client.connected())
 //   {
       
       // currentMillis = millis();
        webSocketClient.getData(dataRecivedFromWeb);
        
        if (dataRecivedFromWeb.length() > 0)
        {
            Serial.print("Data to send to arduino: ");
            Serial.println(dataRecivedFromWeb);
            //Serial.print("Sending data to arduino...\n" );
            dataRecivedFromWeb = dataToSend;
            dataRecivedFromWeb = "";
            NodeMCU.println(dataToSend);
            dataToSend = "";
            //webSocketClient.sendData("data was send to arduino");
        }

            //*************send log data to server in certain interval************************************
            //currentMillis=millis();
          //  if (abs(currentMillis - previousMillis) >= interval) 
           // {
                //previousMillis = currentMillis;
                //data = (String)analogRead(A0); //read adc values, this will give random value, since no sensor is connected.

         //When there is something in serial buffer
         while (NodeMCU.available()) 
                {
                  //Serial.println("NodeMCU available !@");
                    char serialChar = NodeMCU.read();  //gets one byte from serial buffer
                        if (serialChar == '<') //if < is the beginning of the received char reset the buffer
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
                // webSocketClient.sendData("random test");
                 if(stringComplete == true)
                        {
                          Serial.println("Received from arduino: " );  
                          delay(2); 
                          stringComplete = false;
                          Serial.println(serialMessage);
                          
                          webSocketClient.sendData(serialMessage); //send received data to websocket server
                          serialMessage = "";
                        }
       
        delay(1000);
    
}
