
/**
* main file
*/
#include "printf.h";
#include <DS3231.h>
long serialPort = 115200;
DS3231 rtc(A4, A5);

void setup(){
  Serial.begin(serialPort);
  printf_begin();
  setupSdkaart();
  klok_init();
}

void loop(){

  klok_loop();
}
