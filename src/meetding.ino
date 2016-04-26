
/**
* main file
*/
#include "printf.h";
long serialPort = 115200;

void setup(){
  Serial.begin(serialPort);
  printf_begin();
  setupSdkaart();
  klok_init();
}

void loop(){

  klok_loop();
}
