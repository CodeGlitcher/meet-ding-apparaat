#include "RTClib.h";
#include "Wire.h";
#include "SPI.h"
#include "SD.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
//#include "Adafruit_ST7735.h"
#include "Adafruit_ILI9341.h"
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

#define SCHERM_DC 9
#define SCHERM_CS 10
#define SCHERM_RST 7

#define WARNLED_PIN 8

#define LOG_PIN 41
#define CELCIUS_CORRECTION 0
const long baud = 115200;

void setup(){  
  pinMode(SD_KAART_PIN, OUTPUT);
  pinMode(SCHERM_CS, OUTPUT);
  pinMode(WARNLED_PIN, OUTPUT);
  pinMode(LOG_PIN, INPUT);
  
  digitalWrite(SD_KAART_PIN, HIGH);
  digitalWrite(SCHERM_CS, HIGH);
  digitalWrite(WARNLED_PIN, LOW);
  
  log_init();
  log_println(F("Setup"));
  
  knoppen_init();
  
  scherm_init();
  
  opslag_init();
  
  klok_init();
  
  sensor_temp_init();
  
  sensor_init();

  knoppen_set_pot_callback(&interface_potmeter_changed);
  knoppen_set_selecteer_callback(&interface_selecteer_pressed);

  log_println("Setup klaar");
}

void loop(){
  knoppen_loop();
  interface_loop();
  sensor_loop();

  //scherm_debug();
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
          sendSerialEnd(inChar);
          break;
        case '1' : 
          opslag_sendData();
           sendSerialEnd(inChar);
          break;
        case '2' :
          opslag_sendConfig();
          sendSerialEnd(inChar);
          break;
        case '3' :
          opslag_recConfig();
          break;
        case '4' :
          readTime();
          //tijd
          break;
        case '5' :
          setDebug();
          sendSerialEnd(inChar);
          break;
        case '6' :
          opslag_verwijderData();
          sendSerialEnd(inChar);
          break;
      }
  
    }
    while(Serial.available()) {
      Serial.read();
    }
  }
}

void setDebug(){
   char en = (char)Serial.read();
    if(en == 't') {
      log_enable();
    } else if(en == 'f') {
      log_disable();
    }
}

void sendSerialEnd(char in){
      delay(2000);// give buffer some time co clear
      Serial.print('$');
      Serial.print(in);
}

