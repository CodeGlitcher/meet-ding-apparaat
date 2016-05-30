#include "RTClib.h";
#include "Wire.h";
#include "SPI.h"
#include "SD.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "IniFile.h"
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

const long baud = 38400;

void setup(){
  log_init();
  knoppen_init();
  randomSeed(analogRead(2));
  pinMode(SD_KAART_PIN, OUTPUT);
  pinMode(SCHERM_CS, OUTPUT);
  digitalWrite(SD_KAART_PIN, HIGH);
  digitalWrite(SCHERM_CS, HIGH);
  
  
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

//  scherm_debug();
}

void serialEvent() {
  if (Serial.available()) {
    // get the new byte:
    delay(5);
    char inChar = (char)Serial.read();
    if(inChar == '#' && Serial.available()) {
      inChar = (char)Serial.read();
      switch(inChar) {
        case '0' :
          break;
        case '1' : 
          opslag_sendData();
          break;
        case '2' :
          opslag_sendConfig();
          break;
        case '3' :
          opslag_recConfig();
          break;
        case '4' :
          char en = (char)Serial.read();
          if(en == 't') {
            log_enable();
          } else if(en == 'f') {
            log_disable();
          }
          break;
      }
      Serial.print('$');
      Serial.print(inChar);
    }
    while(Serial.available()) {
      Serial.read();
    }
  }
}
