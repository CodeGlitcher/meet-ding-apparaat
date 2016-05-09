#include "SPI.h"
#include "Adafruit_GFX.h"
#include <Adafruit_ST7735.h>

//Adafruit_ILI9341 scherm = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ST7735 scherm = Adafruit_ST7735(SCHERM_CS, SCHERM_DC);;

void scherm_init() {
  
  scherm.initR(INITR_BLACKTAB);
  scherm.print("Jochem is gay");
}

void scherm_loop() {
  
}

