#include "printf.h"
const long baud = 115200;

void setup()  {
  log_init(baud);

  opslag_init();
  knoppen_init(0,4);

  sensor_temp_init();

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop() {
  sensor_temp_loop();
  opslag_loop();
  knoppen_loop();
}
