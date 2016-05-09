#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 scherm = Adafruit_ILI9341(TFT_CS, TFT_DC);

void scherm_init() {
  scherm.begin();
  scherm.setRotation(3);

  scherm.setTextSize(3);
  scherm.println("Jochem is gay");
}

void scherm_loop() {
  
}

