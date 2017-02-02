/*
 * Title : subscribe info and publish it to cloudmqtt.com
 * Date : 2017-01-31
 * Modified : YuHaiBo
 * Found at : the PubSubClient module example
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_PORT 12324

const char *ssid = "xxxxxxx";
const char *password = "xxxxxx";
const char *mqtt_server = "xxxxxxxxxxxx";
const char *mqtt_user = "xxxxxx";
const char *mqtt_password = "xxxxxx";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
    delay(10);
    Serial.print("\nConnecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nWiFi connected\nIP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    byte *p = (byte*)malloc(length);
    memcpy(p, payload, length);
    client.publish("outTopic", p, length);
    free(p);
}
void reconnect()
{
    Serial.println("Attenpting cloudmqtt connection..");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password))
    {
        Serial.println("connected");
        client.subscribe("inTopic");
    }
    else
    {
        Serial.print(String("failed, rc=") + String(client.state()) + String(" try again in 5 seconds\n"));
        delay(5000); 
    }
    
}
void setup() 
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, MQTT_PORT);
    client.setCallback(callback);
}

void loop() 
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}
