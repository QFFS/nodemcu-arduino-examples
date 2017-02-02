/*
 * Title : blink the led
 * Date : 2017-02-03
 * Modified : YuHaiBo 
 * Found at : from the ESP8266 module example
*/
void setup() 
{
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
}

 
void loop() 
{
    digitalWrite(BUILTIN_LED, LOW);    
    Serial.println("ON");
    delay(1000);                      
    digitalWrite(BUILTIN_LED, HIGH);   
    Serial.println("OFF");
    delay(1000);                       
}
