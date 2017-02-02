/*
 * Title : get the Chinese Standard Time
 * Date : 2017-01-28
 * Modified : YuHaiBo 
 * Found at : https://github.com/ckuehnel/NodeMCU-applications   getDateTime.lua
*/
#include <ESP8266WiFi.h>

const char* ssid     = "xxxxxxx";
const char* password = "xxxxxxxxxx";

const char* host = "www.baidu.com";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  delay(2000);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  client.print(String("HEAD / HTTP/1.1\r\n") +
               String("Host: www.baidu.com\r\n\r\n"));         
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\n');
    line.toUpperCase();
    if (line.startsWith("DATE: "))
    {
      int hours = (line.substring(23,25).toInt()+8)%24;
      int minutes = line.substring(26,28).toInt();
      int seconds = line.substring(29,31).toInt();
      Serial.println("Chinese Standard Time : " + String(hours) + ":" + String(minutes) + ":" + String(seconds));
    }
  }
}

