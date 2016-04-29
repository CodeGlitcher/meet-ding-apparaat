#include "printf.h"
const long baud = 115200;

void setup()  {
  log_init(baud);

  opslag_init();
  knoppen_init(0,4);

  setupTempSensor();

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop() {
  loopTempSensor();
  opslag_loop();
  knoppen_loop();
}
