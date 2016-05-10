#include "RTClib.h";
#include "Wire.h";
#include "SPI.h"
#include "SD.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"

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

const long baud = 57600;
const bool debug = true;

void setup(){
  log_init();
  knoppen_init();

  opslag_init();
  klok_init();
  scherm_init();
  sensor_temp_init();

  knoppen_set_pot_callback(&scherm_potmeter_changed);
  knoppen_set_selecteer_callback(&scherm_selecteer_pressed);

  log_println("Alle componenten zijn geïnitialiseerd ");
}

long lastloop = 0;
int screen = 1;
void loop(){
  opslag_loop();
  knoppen_loop();
  scherm_loop();
  sensor_temp_loop();
  klok_loop();

  if(debug && millis() - lastloop > 1000){
    lastloop = millis();
    
    //sensor_temp_read_values();
    float humidity = 0.0;//sensor_temp_humidity();
    float temp = 0.0;//sensor_temp_celcius();
    float heatIndex = 0.0;//sensor_temp_heatindex_c();
    long  time = klok_getUnitxTime();
    String timeString = klok_getDateTime();
    opslag_SaveData(time, timeString,temp,heatIndex,humidity);
  }
}
