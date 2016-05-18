#include "RTClib.h";
#include "Wire.h";
#include "SPI.h"
#include "SD.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
//#include "Fonts/FreeSans18pt7b.h"

#define DHTTYPE DHT22

// ANALOG 0-5
#define POTMETER_PIN A0
// INTERRTUPT 0-1
#define SELECTEER_PIN 0
// DIGITAL 3-13
#define SD_KAART_PIN 5
#define DHTPIN 6
#define SCHERM_BL 8
#define SCHERM_DC 9
#define SCHERM_CS 10

#define CELCIUS_CORRECTION -2

const long baud = 57600;

void setup(){
  log_init();
  knoppen_init();

  opslag_init();
  klok_init();
  scherm_init();
  //sensor_temp_init();

  knoppen_set_pot_callback(&interface_potmeter_changed);
  knoppen_set_selecteer_callback(&interface_selecteer_pressed);

  log_println(F("Alle componenten zijn geïnitialiseerd "));
}

void loop(){
  knoppen_loop();
  interface_loop();

  //scherm_debug();
}
