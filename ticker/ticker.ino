/*
 * Title : use the ticker to bkink the led
 * Date : 2017-01-30
 * Modified : YuHaiBo 
 * Found at : the esp8266 example
*/

#include <Ticker.h>
Ticker fliper;
int state = 0;
void flip()
{
  if ((state++)%2 == 0)
     digitalWrite(BUILTIN_LED, LOW);
   else
     digitalWrite(BUILTIN_LED, HIGH);
}
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.begin(115200);
  fliper.attach(1, flip);
  Serial.print("\nThe LED on the board will be toggled every second\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}
