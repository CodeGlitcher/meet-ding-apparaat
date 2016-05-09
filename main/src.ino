#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

const long baud = 57600;

// Initieer alle componenten
void setup(){
  log_init(baud);
  opslag_init();
  knoppen_init(2,4);
  scherm_init();

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop(){
  opslag_loop();
  knoppen_loop();
}
