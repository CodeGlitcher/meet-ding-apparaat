
/**
* main file
*/
#include "printf.h";
#include <DS3231.h>
#include <SPI.h>
#include <SD.h>

#include <SPI.h>
#include <SD.h>
long serialPort = 115200;
DS3231 rtc(A4, A5);

int SD_KAART_PIN = 4;
void setup(){
  Serial.begin(serialPort);
  printf_begin();
  opslag_init(SD_KAART_PIN);
  klok_init();
}

void loop(){
opslag_loop();
  klok_loop();
}
