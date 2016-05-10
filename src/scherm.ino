//Adafruit_ILI9341 scherm = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ST7735 scherm = Adafruit_ST7735(SCHERM_CS, SCHERM_DC);

byte scherm_modus = 1; // 0 = inactief, 1 = vraag stellen, 2 = bedanken
long scherm_modus_last_change = 0;

void scherm_init() {
  scherm.initR(INITR_BLACKTAB);
  scherm.setRotation(1);
  scherm.fillScreen(ST7735_BLACK);

  pinMode(SCHERM_BL, OUTPUT);
  scherm_aan();
  
  if (debug){
    scherm.drawRect(0,0, scherm.width(), scherm.height(), ST7735_RED);
  }

  scherm.setTextSize(2);
  scherm.setCursor(5,5);
  scherm.print("Welk cijfer");
  scherm.setCursor(5,25);
  scherm.print("geeft u deze");
  scherm.setCursor(5,45);
  scherm.print("werkruimte?");
}

void scherm_loop() {
  if (scherm_modus==2 && millis() - scherm_modus_last_change > 5000){
    scherm_modus=0;
    scherm_modus_last_change = millis();
    scherm.fillScreen(ST7735_BLACK);
    scherm_uit();
  }
}

inline void scherm_uit() {
    digitalWrite(SCHERM_BL, LOW);
}

inline void scherm_aan() {
    digitalWrite
    (SCHERM_BL, HIGH);  
}

void scherm_selecteer_pressed(){
  if (scherm_modus!=1){
    return;
  }

  scherm_modus = 2;
  scherm_modus_last_change = millis();
  scherm.fillScreen(ST7735_BLACK);
  scherm_draw_bedankt(10,50);
}

void scherm_potmeter_changed(int val) {
  if (scherm_modus!=1){
    return;
  }
  
  scherm_draw_cijfer(35, 80, val);
}

void scherm_draw_bedankt(int x, int y){
  scherm.fillRect(x, y, 100, 40, ST7735_BLACK);
  
  scherm.setTextSize(3);  
  scherm.setCursor(x,y);
  scherm.print("Bedankt!");
  scherm.setTextSize(1); 
}

void scherm_draw_cijfer(int x, int y, int val){
  scherm.fillRect(x, y, 100, 40, ST7735_BLACK);
  
  scherm.setTextSize(3);  
  scherm.setCursor(x,y);

  // Bereken het cijfer
  int voorKomma = val/10;
  int naKomma = val%10;
  char buffer[5];
  sprintf(buffer, "%2d,%d", voorKomma, naKomma);

  scherm.print(buffer);
  scherm.setTextSize(1); 
}

