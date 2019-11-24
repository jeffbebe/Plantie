/*******************Esp8266_Websocket.ino****************************************/

#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <SoftwareSerial.h>



//Wifi config
boolean handshakeFailed = 0;
String dataRecivedFromWeb = "";
String dataToSend = "";

uint8_t pin_led = 2;
char path[] = "/"; //identifier of this device

const char *ssid = "Internet";
const char *password = "dlink123";
char *host = "192.168.1.4"; //replace this ip address with the ip address of your Node.Js server
const int espport = 3000;

WebSocketClient webSocketClient;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval = 2000; //interval for sending data to the websocket server in ms

// Use WiFiClient class to create TCP connections
WiFiClient client;

//Esp-arduino config
const int rxPin = 3;
const int txPin = 2;
SoftwareSerial NodeMCU(rxPin, txPin); //(rxPin, txPin);
String dataReceivedFromUno;

String receivedString;
String receivedFromUno;
String serialMessage = "";
bool stringComplete = false;


void wsconnect()
{
    // Connect to the websocket server
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
    pinMode(pin_led, INPUT); // Initialize the LED_BUILTIN pin as an output

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
                
      // if (NodeMCU.isListening()) {
         // Serial.println("NodeMCU is listening !@");
        
         while (NodeMCU.available()) 
                {
                  //Serial.println("NodeMCU available !@");
                    char serialChar = NodeMCU.read();  //gets one byte from serial buffer
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
                // webSocketClient.sendData("random test");
                 if( stringComplete == true)
                        {
                          Serial.println("Received from arduino: " );  
                          delay(2); 
                          stringComplete = false;
                          Serial.println(serialMessage);
                          
                          webSocketClient.sendData(serialMessage); //send sensor data to websocket server
                          serialMessage = "";
                        }
       
        delay(1000);
    
}
