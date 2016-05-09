
#include "printf.h";
#include "RTClib.h";
#include "Wire.h";
#include <SPI.h>
#include <SD.h>
// ANALOG 0-5
#define POTMETER_PIN A0
// INTERRTUPT 0-1
#define SELECTEER_PIN 0
// DIGITAL 3-13
#define BUZZER_PIN 3
#define LICHT_PIN 4
#define SD_KAART_PIN 5
const long baud = 115200;

void setup(){

  log_init(baud);
  knoppen_init(SELECTEER_PIN, POTMETER_PIN);
  buzzer_init(BUZZER_PIN);
  licht_init(LICHT_PIN);
  opslag_init(SD_KAART_PIN);
  klok_init();
  knoppen_init(0,4);
  log_print("Alle componenten zijn geïnitialiseerd");

}

void loop(){
  opslag_loop();
  knoppen_loop();
  buzzer_loop();
  klok_loop();
}
