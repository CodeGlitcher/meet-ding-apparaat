Adafruit_ILI9341 scherm = Adafruit_ILI9341(SCHERM_CS, SCHERM_DC, SCHERM_RST);
//Adafruit_ST7735 scherm = Adafruit_ST7735(SCHERM_CS, SCHERM_DC);

bool scherm_changed = false;
int scherm_curvraagnr = 0;

inline void scherm_init() {
  log_print(F("Scherm "));
  scherm.begin();
  scherm.setRotation(1);
  scherm.fillScreen(ILI9341_BLACK);
  log_println(F("... klaar"));

}

//inline void scherm_uit() {
//    digitalWrite(SCHERM_BL, LOW);
//}
//
//inline void scherm_aan() {
//    digitalWrite(SCHERM_BL, HIGH);  
//}



void scherm_draw_cijfer(int antwoordnr){
  if (antwoordnr==-1){
    scherm.fillRect(0, 120, scherm.width(), 24*3, ILI9341_BLACK);
    scherm.setTextSize(3);
    scherm.setTextColor(ILI9341_WHITE);
    scherm.setCursor(0,120);
    scherm.println(F("Draai aan de knop"));
    delay(1);

    return;
  } 

  if (!scherm_changed){
    scherm.fillRect(0, 100, scherm.width(), 100, ILI9341_BLACK);
  }
  scherm_changed = true;
  char antwoord[80];
  scherm.setTextSize(3);
  scherm.setCursor(0, 120);
  for(int i = 0; i < 3; i++) {
    scherm.fillRect(0, 120+(24*i), scherm.width(), 24, ILI9341_BLACK);
    if(opslag_getAntwoord(opslag_getVraagNr(), antwoordnr, i, antwoord)) {
      scherm.println(antwoord);
    }
  }
}

void scherm_stel_vraag(){

  scherm.setTextSize(3);
  scherm.setCursor(0,0);

  scherm.fillRect(0,0, scherm.width(), 4*24, ILI9341_BLACK);

  char vraagBuf[80];
  for(int i = 0; i < 4; i++) {
    if(opslag_getVraag(scherm_curvraagnr, i, vraagBuf)) {
      scherm.println(vraagBuf);
    }
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

void scherm_draw_bedankt(int x, int y){
  scherm.fillRect(0, 0, 320, 240, ILI9341_BLACK);
  
  scherm.setTextSize(4);  
  scherm.setCursor(x,y);
  scherm.print(F("Bedankt!"));
  scherm.setTextSize(1); 
}

int scherm_get_curvraagnr(){
  return scherm_curvraagnr;
}

void scherm_reset(){
  scherm.fillScreen(ILI9341_BLACK);
  scherm_changed = false;
}

long scherm_last_debug = 0;
void scherm_debug(){

  if (millis() - scherm_last_debug > 1000){
    scherm_last_debug = millis();

    sensor_temp_read_values();
    scherm.setTextSize(1);  

    scherm.fillRect(0, 0, 32, 50, ILI9341_BLACK);
    scherm.drawRect(-1, -1, 33, 51, ILI9341_RED);

    scherm.setCursor(1, 1);
    scherm.println(analogRead(1));
    scherm.setCursor(1, 11);
    scherm.println(sensor_temp_humidity());
    scherm.setCursor(1, 21);
    scherm.println(sensor_temp_celcius());
  }
}
