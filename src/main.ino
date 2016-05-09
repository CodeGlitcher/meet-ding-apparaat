
#include "printf.h";
#include "RTClib.h";
#include "Wire.h";
// ANALOG 0-5
#define POTMETER_PIN 0

// INTERRTUPT 0-1
#define SELECTEER_PIN 0

// DIGITAL 3-13
#define BUZZER_PIN 3
#define LICHT_PIN 4

/**
* main file
*/

const long baud = 115200;

void setup(){
  log_init(baud);
  opslag_init();
  knoppen_init(SELECTEER_PIN, POTMETER_PIN);
  buzzer_init(BUZZER_PIN);
  licht_init(LICHT_PIN);
  klok_init();
  knoppen_init(0,4);
  log_print("Alle componenten zijn geïnitialiseerd ");

}

void loop(){
  opslag_loop();
  knoppen_loop();
<<<<<<< HEAD
  buzzer_loop();
=======
  klok_loop();
>>>>>>> d4e6da576f9ead1d29bb2e95d61c8c95c7c260e1
}
