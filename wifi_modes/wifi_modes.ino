#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t pin_led = 16;
char* ssid = "NETWORK_SSID";      //Your WiFi hotspot name
char* password = "13meetup37";.   //Your Wifi Hotspot asswordpno special characters or spaces 
char* mySsid = "ESP8266_SSID";.   // Guest Hotspot name 
//The following 3 lines are your nodemcu custom IP, subnet, gateway addresses
IPAddress ip(192,168,11,4);.      
IPAddress gateway(192,168,11,1);. 
IPAddress subnet(255,255,255,0);

void setup()
{
  pinMode(pin_led, OUTPUT);.      //Customizable output pin... Try using an external LED riggrd to the nodemcu. Note that other pins might have to be configured as well...
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});. //Message to be didplayed in the IP address browser tab
  server.on("/toggle",toggleLED);.    
  server.begin();

  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(mySsid, password);
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}
