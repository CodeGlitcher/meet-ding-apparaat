#include "RTClib.h";
#include "Wire.h";
#include "SPI.h"
#include "SD.h"
#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "IniFile.h"

#define DHTTYPE DHT22
#define CELCIUS_CORRECTION 0
const long baud = 115200;

// Definieer waarvoor alle (configureerbare) binnen gebruikt worden.
// ANALOOG 0-5
#define POTMETER_PIN A0
#define LDR_PIN      A1
#define CO2_PIN      A2
#define GELUID_PIN   A3

// INTERRTUPT 0-1
#define SELECTEER_PIN 0

// DIGITAAL 3-13
#define SD_KAART_PIN 5
#define DHTPIN       6
#define SCHERM_RST   7
#define WARNLED_PIN  8
#define SCHERM_DC    9
#define SCHERM_CS    10
#define LOG_PIN      41

// De initiele set up
void setup()
{
  // Stel wat pinnen in
  pinMode(SD_KAART_PIN, OUTPUT);
  pinMode(SCHERM_CS, OUTPUT);
  pinMode(WARNLED_PIN, OUTPUT);
  pinMode(LOG_PIN, INPUT);

  digitalWrite(SD_KAART_PIN, HIGH);
  digitalWrite(SCHERM_CS, HIGH);
  digitalWrite(WARNLED_PIN, LOW);

  // Initialiseer alle componenten
  log_init(); // Log systeem
  knp_init(); // Knoppen besturing
  sch_init(); // Scherm
  ops_init(); // Opslag
  klk_init(); // Real-time klok
  tem_init(); // Temperatuur sensor
  sns_init(); // Sensor data opslaan interval

  //Stel een callback functie in, deze wordt aangeroepen wanneer de knoppen gebruikt worden
  knp_setPotCallback(&inf_potmeterChanged);
  knp_setSelecteerCallback(&inf_selecteerPressed);

  log_println("Setup klaar");
}

// Sommige componenten moeten informatie blijven verzamelen van de pins. Deze
// loop roept voor ieder component waarbij dit nodig is een functie aan.
// LET OP!: deze functies mogen geen delay() gebruiken omdat dit de werking
// van de andere componenten hindert.
void loop()
{
  knp_loop(); // Knop
  inf_loop(); // Interface
  sns_loop(); // Sensor opslaan
  gld_loop(); // Geluidssensor
}

// Handel berichten over serial af
void serialEvent()
{
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
          ops_sendData();
           sendSerialEnd(inChar);
          break;
        case '2' :
          ops_sendConfig();
          sendSerialEnd(inChar);
          break;
        case '3' :
          ops_recConfig();
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
          ops_verwijderData();
          sendSerialEnd(inChar);
          break;
      }

    }
    while(Serial.available()) {
      Serial.read();
    }
  }
}

// Zet log modus aan of uit.
void setDebug()
{
   char en = (char)Serial.read();
    if(en == 't') {
      log_enable();
    } else if(en == 'f') {
      log_disable();
    }
}

// Verstuur eind van serial bericht
void sendSerialEnd(char in)
{
      delay(2000);// give buffer some time co clear
      Serial.print('$');
      Serial.print(in);
}
