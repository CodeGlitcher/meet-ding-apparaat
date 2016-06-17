
#include "printf.h";
#include "RTClib.h";
#include "Wire.h";
#include <SPI.h>
#include <SD.h>
// ANALOG 0-5
#define POTMETER_PIN A0
// INTERRTUPT 0-1
#define SELECTEER_PIN 0
#define GELUID_PIN A1
// DIGITAL 3-13
#define DHTPIN 6
#define BUZZER_PIN 3
#define LICHT_PIN 4
#define SD_KAART_PIN 5
const long baud = 115200;

#include "DHT.h"
#define DHTTYPE DHT22
void setup(){

  log_init(baud);
  knoppen_init(SELECTEER_PIN, POTMETER_PIN);
  buzzer_init(BUZZER_PIN);
  licht_init(LICHT_PIN);
  opslag_init(SD_KAART_PIN);
  klok_init();
  sensor_temp_init();
  log_println("Alle componenten zijn geïnitialiseerd ");
}

void loop() {
  sensor_temp_loop();
  opslag_loop();
//  knoppen_loop();
//  buzzer_loop();
  klok_loop();

  if(readSensors()){
    sensor_temp_read_values();
    float humidity = sensor_temp_humidity();
    float temp = sensor_temp_celcius();
    float heatIndex = sensor_temp_heatindex_c();
    long  time = klok_getUnitxTime();
    String timeString = klok_getDateTime();
    opslag_SaveData(time, timeString,temp,heatIndex,humidity);
    delay(1000);
  }
}
bool readSensors(){
  return true;
}
