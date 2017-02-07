#include "FS.h"
void setup() 
{
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Mounting SPIFFS...");
    if (!SPIFFS.begin())
    {
        Serial.println("Fail to mount file system");
        return ;
    }
    File f = SPIFFS.open("test.txt", "w");
    if (!f)
    {
        Serial.println("Fail to open file to writing");
        return;
    }
    char *info = "device=nodemcuv1.0";
    f.write((uint8_t*)info,18);
    f.close();
    f = SPIFFS.open("test.txt", "r");
    char a[18];
    f.readBytes(a, 18);
    Serial.println("read from File system: ");
    Serial.println(a);
    f.close();
}

void loop() {
  // put your main code here, to run repeatedly:

}
