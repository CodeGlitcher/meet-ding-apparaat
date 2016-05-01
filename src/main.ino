
/**
* main file
*/
#include "printf.h";
#include "RTClib.h";
#include "Wire.h";
const long baud = 115200;



void setup(){
  log_init(baud);
  opslag_init();
  klok_init();
  knoppen_init(0,4);
  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop(){
  opslag_loop();
  knoppen_loop();
  klok_loop();
}
