#include "printf.h";
int serialPort = 115200;

void setup(){
  setupSdkaart();
  setupTempSensor();
}

void loop(){
  // Serial.begin(serialPort);
  // printf_begin();
  loopTempSensor();
}
