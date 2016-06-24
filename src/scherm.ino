// Deze module tekent op het scherm.
// sch -> scherm

Adafruit_ILI9341 scherm = Adafruit_ILI9341(SCHERM_CS, SCHERM_DC, SCHERM_RST);

bool sch_changed = false;
int sch_curvraagnr = 0;

// Zet het scherm klaar om te gaan beginnen
inline void sch_init() {
  log_print(F("Scherm "));
  scherm.begin();
  scherm.setRotation(1);
  scherm.fillScreen(ILI9341_BLACK);
  log_println(F("... klaar"));
}


// Teken een cijfer
void sch_drawCijfer(int antwoordnr){
  if (antwoordnr==-1){
    scherm.fillRect(0, 120, scherm.width(), 24*3, ILI9341_BLACK);
    scherm.setTextSize(3);
    scherm.setTextColor(ILI9341_WHITE);
    scherm.setCursor(0,120);
    scherm.println(F("Draai aan de knop"));
    delay(1);

    return;
  } 

  if (!sch_changed){
    scherm.fillRect(0, 100, scherm.width(), 100, ILI9341_BLACK);
  }
  sch_changed = true;
  char antwoord[80];
  scherm.setTextSize(3);
  scherm.setCursor(0, 120);
  for(int i = 0; i < 3; i++) {
    scherm.fillRect(0, 120+(24*i), scherm.width(), 24, ILI9341_BLACK);
    if(ops_getAntwoord(ops_getVraagNr(), antwoordnr, i, antwoord)) {
      scherm.println(antwoord);
    }
  }
}

// Lees de vraag van de sd en geef hem weer op het scherm
void sch_stelVraag(){
  scherm.setTextSize(3);
  scherm.setCursor(0,0);

  scherm.fillRect(0,0, scherm.width(), 4*24, ILI9341_BLACK);

  char vraagBuf[80];
  for(int i = 0; i < 4; i++) {
    if(ops_getVraag(sch_curvraagnr, i, vraagBuf)) {
      scherm.println(vraagBuf);
    }
  }
  sch_curvraagnr = (sch_curvraagnr + 1) % ops_getVraagAantal(); 
}

void sch_drawBedankt(int x, int y){
  scherm.fillRect(0, 0, 320, 240, ILI9341_BLACK);
  
  scherm.setTextSize(4);  
  scherm.setCursor(x,y);
  scherm.print(F("Bedankt!"));
  scherm.setTextSize(1); 
}

int sch_getCurVraagNr(){
  return sch_curvraagnr;
}

void sch_reset(){
  scherm.fillScreen(ILI9341_BLACK);
  sch_changed = false;
}

long sch_last_debug = 0;
void sch_debug(){

  if (millis() - sch_last_debug > 1000){
    sch_last_debug = millis();

    tem_readValues();
    scherm.setTextSize(1);  

    scherm.fillRect(0, 0, 32, 50, ILI9341_BLACK);
    scherm.drawRect(-1, -1, 33, 51, ILI9341_RED);

    scherm.setCursor(1, 1);
    scherm.println(analogRead(1));
    scherm.setCursor(1, 11);
    scherm.println(tem_humidity());
    scherm.setCursor(1, 21);
    scherm.println(tem_celcius());
  }
}
