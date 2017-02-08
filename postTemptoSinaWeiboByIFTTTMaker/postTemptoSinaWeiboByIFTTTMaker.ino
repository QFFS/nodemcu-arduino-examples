/*
 * Title : post the temperature in house to sina Weibo by IFTTT maker every half hour
 * Date : 2017-02-4
 * Write : YuHaiBo 
*/

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS_1 2
#define PORT 80

OneWire oneWire_in(ONE_WIRE_BUS_1);
DallasTemperature sensor_inhouse(&oneWire_in);

const char* ssid     = "xxxxx";
const char* password = "xxxxxxxxxxxx";

String event = "xxxxx";
String key = "xxxxxxxxxxx";

void setup() 
{
    Serial.begin(115200);
    delay(10);
    
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
    sensor_inhouse.begin();
}
String postUrl(String event, String key)
{  
    return String("/trigger/") + event + String("/with/key/") + key + String("?value1=") + String(sensor_inhouse.getTempCByIndex(0));
}
void loop() 
{
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect("maker.ifttt.com", httpPort)) {
    Serial.println("connection failed");
    return;
    }
    sensor_inhouse.requestTemperatures();
    client.print(String("POST ")  + postUrl(event, key) + 
                String(" HTTP/1.1\r\n") +
               String("Host: maker.ifttt.com\r\n") + 
               String("Accept: */*\r\n") + 
               String("User-Agent: Mozilla/4.0 (compatible; esp8266 ardunio; Windows NT 5.)\r\n\r\n"));   
               
    delay(60*1000*30); //delay 30 minutes
}

