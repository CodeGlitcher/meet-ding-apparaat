//Adafruit_ILI9341 scherm = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ST7735 scherm = Adafruit_ST7735(SCHERM_CS, SCHERM_DC);

bool scherm_changed = false;

int scherm_curvraagnr = 0;

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
  if (val==-1){
    scherm.setTextSize(2);
    scherm.setTextColor(0x666666);
    scherm.setCursor(10,y);
    scherm.print(F("Draai aan de knop"));
    scherm.setTextColor(ST7735_WHITE);

    return;
  } 

  if (!scherm_changed){
    scherm.fillRect(0, y, scherm.width(), 100, ST7735_BLACK);
  }
  scherm_changed = true;
  char antwoord[80];
  if(opslag_getAntwoord(opslag_getVraagNr(), val, antwoord)) {
    scherm.fillRect(0,y+16, scherm.width(), 18, ST7735_BLACK);
    int length = strlen(antwoord);
    scherm.fillRect(12*length, y, scherm.width(), 18, ST7735_BLACK);
    scherm.setTextSize(2);    
    scherm.setTextColor(ST7735_WHITE, ST7735_BLACK);
    scherm.setCursor(12,y);
    scherm.println(antwoord);
  } else {
    log_println("Antwoord niet gevonden!");
  }

//  char a[7][12];
//  strcpy(a[0], "Zeer slecht");
//  strcpy(a[1], "  Slecht   ");
//  strcpy(a[2], "   Matig   ");
//  strcpy(a[3], " Voldoende ");
//  strcpy(a[4], "  Redelijk ");
//  strcpy(a[5], "   Goed    ");
//  strcpy(a[6], " Zeer goed ");
//
//  int len = strlen(a[val]); 
//  scherm.setTextSize(2);
//  scherm.fillRect(12 + len * 12 , y, (11 - len) * 12, 24, ST7735_BLACK);
//  scherm.setTextColor(ST7735_WHITE, ST7735_BLACK);
//  scherm.setCursor(12,y);
//  scherm.print(a[val]);
}

void scherm_stel_vraag(){

  char vraagBuf[80];
  if(opslag_getVraag(scherm_curvraagnr, vraagBuf)) {
    scherm.setTextSize(2);
    scherm.setCursor(0,0);
    scherm.println(vraagBuf);
  }
  scherm_curvraagnr = (scherm_curvraagnr + 1) % opslag_getVraagAantal(); 

  
  /*
  scherm.setTextSize(2);
  scherm.setCursor(5,5);
  scherm.print(F("Welk cijfer"));
  scherm.setCursor(5,25);
  scherm.print(F("geeft u deze"));
  scherm.setCursor(5,45);
  scherm.print(F("werkruimte?")); 
  */ 
}

int scherm_get_curvraagnr(){
  return scherm_curvraagnr;
}

void scherm_reset(){
  scherm.fillScreen(ST7735_BLACK);
  scherm_changed = false;
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
    scherm.println(analogRead(1));
    scherm.setCursor(1, 11);
    scherm.println(sensor_temp_humidity());
    scherm.setCursor(1, 21);
    scherm.println(sensor_temp_celcius());
  }
}
