/*
 * Title : blink the led connect at D1 once and deepsleep 5s
 * Date : 2017-02-8
 * Writed : YuHaiBo
*/
void setup() 
{
    Serial.begin(115200);
    pinMode(D1, OUTPUT);
}

void loop() 
{
    digitalWrite(D1, HIGH);
    delay(1000);
    digitalWrite(D2, LOW);
    ESP.deepSleep(5000000, RF_DEFAULT);
}
