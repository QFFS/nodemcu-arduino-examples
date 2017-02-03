/*
 * Title : subscribe instruction from cloudmqtt.com to control led blink
 * Date : 2017-01-31
 * Modified : YuHaiBo
 * Found at : the PubSubClient example
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>


#define MQTT_PORT 19953

const char *ssid = "xxxxx";
const char *password = "xxxxxx";
const char *mqtt_server = "xxxxxxxxx";
const char *mqtt_user = "xxxxxx";
const char *mqtt_password = "xxxxxxxxx";

int state = 0;
Ticker flipper;
WiFiClient espClient;
PubSubClient client(espClient);

//Ticker callback function
void flip()
{
  if ((state++)%2 == 0)
     digitalWrite(BUILTIN_LED, LOW);
   else
     digitalWrite(BUILTIN_LED, HIGH);
}

void setup_wifi()
{
  delay(10);
  Serial.print("\nConnecting to " + String(ssid)+ String(" "));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}

//mqtt callback function
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print(String("Message arrive [") + topic + "] payload: ");
  
  for (int i = 0; i < length; ++i)
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
  
  if ((char)payload[0] == 'y')
  {
    Serial.println("LED start blinking.");
    flipper.attach(1, flip);
  }
  else
  {
    Serial.println("LED stop blinking.");
    flipper.detach();
  }
  
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Attenpting cloudmqtt connection..");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.subscribe("ESP8266Client/inTopic");
    }
    else
    {
      Serial.print(String("failed, rc=") + String(client.state()) + String(" try again in 5 seconds\n"));
      delay(5000);
    }
  }
}
void setup() 
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  digitalWrite(BUILTIN_LED, HIGH);
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
