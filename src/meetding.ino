#include "printf.h";
int serialPort = 115200;

void setup(){
  setupSdkaart();
}

void loop(){
  Serial.begin(serialPort);
  printf_begin();

}
