/*
 * Title : get some ESP8266 info
 * Date : 2017-02-6
 * Modified : YuHaiBo
*/
#include <Esp.h>
#include <Fs.h>

ADC_MODE(ADC_VCC)

void setup() 
{
    Serial.begin(115200);

   
    Serial.printf("ChipID: %08X", ESP.getChipId());
    
    Serial.printf("Flash Chip id:   %08X\n", ESP.getFlashChipId());
    Serial.printf("Flash Speed: %dMHz\n",ESP.getFlashChipSpeed()/1000000);
    Serial.printf("Flash Chip Size: %d\n",ESP.getFlashChipSize());
    Serial.printf("Remaining heap size is: %d\n",ESP.getFreeHeap());

    //get the supply voltage  
    Serial.printf("The supply voltage: %dv\n",ESP.getVcc()/1000);

    //SPIFFS
    Serial.println("Mounting FS...");

    if (!SPIFFS.begin()) 
    {
        Serial.println("Failed to mount file system");
        return;
    }
    FSInfo fsinfo;
    SPIFFS.info(fsinfo);
    Serial.printf("Total: %u, Used: %u, remain: %u\n", fsinfo.totalBytes, fsinfo.usedBytes, fsinfo.totalBytes - fsinfo.usedBytes);
}

void loop() {
  // put your main code here, to run repeatedly:

}
