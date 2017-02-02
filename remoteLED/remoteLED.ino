/*
 * Title : use a web server to control the led
 * Date : 2017-01-31
 * Modified : YuHaiBo 
 * Found at : from the internet
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "xxxxxxxx";
const char* password = "xxxxxxxxxxxxx";

ESP8266WebServer server(80);

void handleRoot() 
{
    String buf = String("<html><h1> ESP8266 Web Server</h1>");
    buf = buf + String("<p>LED: <a href=\"?LED=1\"><button>ON</button></a> <a href=\"?LED=0\"><button>OFF</button></a></p></html>");
    if (server.arg(0) == "1")
    {
        digitalWrite(BUILTIN_LED, LOW);
    }
    else if (server.arg(0) == "0")
    {
        digitalWrite(BUILTIN_LED, HIGH);
    }
    server.send(200, "text/html", buf);

}

void setup(void){
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
   digitalWrite(BUILTIN_LED, HIGH);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
