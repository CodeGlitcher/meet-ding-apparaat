//Adafruit_ILI9341 scherm = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ST7735 scherm = Adafruit_ST7735(SCHERM_CS, SCHERM_DC);

int scherm_prev_voorkomma = -1, scherm_prev_nakomma = -1;

inline void scherm_init() {
  pinMode(SCHERM_BL, OUTPUT);
  scherm_uit();
  scherm.initR(INITR_BLACKTAB);
  scherm.setRotation(1);
  scherm.fillScreen(ST7735_BLACK);
//  scherm.setFont(&FreeSans18pt7b);

}

inline void scherm_uit() {
    digitalWrite(SCHERM_BL, LOW);
}

inline void scherm_aan() {
    digitalWrite
    (SCHERM_BL, HIGH);  
}

void scherm_draw_bedankt(int x, int y){
  scherm.fillRect(x, y, 100, 40, ST7735_BLACK);
  
  scherm.setTextSize(3);  
  scherm.setCursor(x,y);
  scherm.print(F("Bedankt!"));
  scherm.setTextSize(1); 
}

void scherm_draw_cijfer(int x, int y, int val){
  //scherm.fillRect(x, y, 100, 40, ST7735_BLACK);

//  scherm.drawRect(x, y, 18, 24, ST7735_RED);
//  scherm.drawRect(x+18, y, 18, 24, ST7735_RED);
//  scherm.drawRect(x+36, y, 18, 24, ST7735_RED);
//  scherm.drawRect(x+54, y, 18, 24, ST7735_RED);
//  scherm.drawRect(x+72, y, 18, 24, ST7735_RED);
  if (val==-1){
    scherm.setTextSize(2);
    scherm.setTextColor(0x666666);
    scherm.setCursor(10,y);
    scherm.print(F("Draai aan de knop"));
    scherm.setTextColor(ST7735_WHITE);

    return;
  } 

  if (scherm_prev_voorkomma == -1){
    scherm.fillRect(0, y, scherm.width(), 100, ST7735_BLACK);
  }

  scherm.setTextSize(3);  

  // Bereken het cijfer
  int voorKomma = val/10;
  int naKomma = val%10;
  
  char buffer[3];
  if ( voorKomma != scherm_prev_voorkomma ) {
    scherm_prev_voorkomma = voorKomma;
    scherm.fillRect(x, y, 36, 24, ST7735_BLACK);
    sprintf(buffer, "%2d", voorKomma); 

    scherm.setCursor(x,y);
    scherm.print(buffer);
  }
  scherm.setCursor(x+36,y);
  scherm.print(',');
  if ( naKomma != scherm_prev_nakomma ) {
    scherm_prev_nakomma = naKomma;
    scherm.fillRect(x+54, y, 18, 24, ST7735_BLACK);
    sprintf(buffer, "%d", naKomma); 
    scherm.print(buffer);
  }
}

void scherm_stel_vraag(){
  scherm.setTextSize(2);
  scherm.setCursor(5,5);
  scherm.print(F("Welk cijfer"));
  scherm.setCursor(5,25);
  scherm.print(F("geeft u deze"));
  scherm.setCursor(5,45);
  scherm.print(F("werkruimte?"));  
}

void scherm_reset(){
  scherm.fillScreen(ST7735_BLACK);
  scherm_prev_voorkomma = -1;
  scherm_prev_nakomma= -1;
}

long scherm_last_debug = 0;
void scherm_debug(){

  if (millis() - scherm_last_debug > 1000){
    scherm_last_debug = millis();

    sensor_temp_read_values();
    scherm.setTextSize(1);  

    scherm.fillRect(0, 0, 32, 50, ST7735_BLACK);
    scherm.drawRect(-1, -1, 33, 51, ST7735_RED);

    scherm.setCursor(1, 1);
    scherm.println(analogRead(A1));
    scherm.setCursor(1, 11);
    scherm.println(sensor_temp_humidity());
    scherm.setCursor(1, 21);
    scherm.println(sensor_temp_celcius());
  }
}
