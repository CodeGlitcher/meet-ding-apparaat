int opslag_pin;
int opslag_aantal_antwoorden;
int opslag_aantal_vragen;
int opslag_vraag_nr;
int opslag_antwoord_nr;

int opslag_begintijd;
int opslag_eindtijd;
int opslag_vraaginterval = -1;
int opslag_sensorinterval = -1;

//                zo     ma     di     wo     do     vr     za
bool dagen[] = {false, false, false, false, false, false, false};

// alles komt om een of andere rede in hoofdletters te staan. Hier ook maar.
String dataFolder = "ARDUINO";
String dataFile = "DATA.csv";
String configFile = "config.ini";

IniFile ini = IniFile("ARDUINO/config.ini");

/**
* This file contains logic for data storage
*/
inline void opslag_init(){
  log_print(F("SD kaart "));
  SdFile::dateTimeCallback(dateTime);

  int counter = 0;
  while (!SD.begin(SD_KAART_PIN)) {
    log_print(F("."));
    delay(500);
  }
  
  if(!SD.exists(opslag_getDataFileLocation())){
    log_print(F(" ... csv aanmaken"));
    
    // maak folder
    SD.mkdir(dataFolder);
    
    // open data file
    File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  
    // check if file exist
    if (file) {
      // Headerrow
      file.println(F("Type meting|Tijd(ms)|Datum|Temperatuur|Gevoelstemperatuur|Luchtvochtigheid|Lichtkleur|CO2|Geluid|Vraagnummer|Vraag|Antwoordnummer|Antwoord"));
      file.close();
      log_print(F(" gelukt"));
    } else {
      log_print(F(" mislukt"));
    }
  } else {
    log_print(F(" ... csv aanwezig"));
  }

  // lees configuratiebestand uit
  log_print(F(" ... config openen"));
  if(ini.open()) {
    log_print(F(" gelukt"));
    char retBuf[80];
    
    //aantal vragen ophalen
    opslag_aantal_vragen = 0;
    char buf[8];
    sprintf(buf, "vraag%d", 0);
    while (ini.getValue(buf, "vraag_deel0", retBuf, 80)) {
      opslag_aantal_vragen++;
      sprintf(buf, "vraag%d", opslag_aantal_vragen);
    }
        
    //begin en eind tijden ophalen
    if( !ini.getValue("tijden", "begintijd", retBuf, 80, opslag_begintijd) || 
        !ini.getValue("tijden", "eindtijd", retBuf, 80, opslag_eindtijd) ||
        !ini.getValue("tijden", "vraaginterval", retBuf, 80, opslag_vraaginterval) ||
        !ini.getValue("tijden", "sensorinterval", retBuf, 80, opslag_sensorinterval)) {
          
      log_print(F(" ... tijden inlezen mislukt"));
    }

    //lees dagen in
    if( 
        !ini.getValue("dagen", "zo", retBuf, 80, dagen[0]) ||
        !ini.getValue("dagen", "ma", retBuf, 80, dagen[1]) ||
        !ini.getValue("dagen", "di", retBuf, 80, dagen[2]) ||
        !ini.getValue("dagen", "wo", retBuf, 80, dagen[3]) ||
        !ini.getValue("dagen", "do", retBuf, 80, dagen[4]) ||
        !ini.getValue("dagen", "vr", retBuf, 80, dagen[5]) ||
        !ini.getValue("dagen", "za", retBuf, 80, dagen[6])
        ) {
      log_print(F(" ... dagen inlezen mislukt"));
    }    
    
    ini.close();
  } else {
    log_print(F(" mislukt"));
  }
  log_println(F(" ... klaar"));
}

/**
* Voeg data toe aan het data bestand. Het type wordt G van gebruiker
*/
bool opslag_SaveUserData(long tijd, char* datum, float temp, float gevoelsTemp, float luchtvochtigheid, int lichtSterkte, int CO2, int geluid, int antwoordNr){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    
    char tempS[8];
    char gevoelsTempS[8];
    char luchtvochtigheidS[8];
    
    dtostrf(temp,-4,2,tempS);
    dtostrf(gevoelsTemp,-4,2,gevoelsTempS);
    dtostrf(luchtvochtigheid,-4,2,luchtvochtigheidS);

    char vraagBuf[18*4];
    char vraagRgl[80];
    for(int i = 0; i < 4; i++) {
      if(opslag_getVraag(opslag_vraag_nr, i, vraagRgl)) {
        sprintf(vraagBuf + strlen(vraagBuf), "%s ", vraagRgl);
      }
    }

    char antwoordBuf[18*3];
    char antwoordRgl[80];
    for(int i = 0; i < 3; i++) {
      if(opslag_getAntwoord(opslag_vraag_nr, antwoordNr, i, antwoordRgl)) {
        sprintf(antwoordBuf + strlen(antwoordBuf), "%s ", antwoordRgl);
      }
    }
    
    char buffer[200];
    sprintf(buffer, "G|%ld|%s|%s|%s|%s|%d|%d|%d|%d|%s|%d|%s", tijd, datum, tempS, gevoelsTempS, luchtvochtigheidS, lichtSterkte, CO2, geluid, opslag_vraag_nr, vraagBuf, antwoordNr, antwoordBuf);
    log_println(buffer);
    file.println(buffer);
    file.close();
    
    return true;
  } else {
    log_println(F("Data bestand openen mislukt"));
    return false;
  }
}

/*
 * Sla data op van de sensoren. Het type is I van interval
 */
bool opslag_SaveIntervalData(long tijd, char* datum, float temp, float gevoelsTemp, float luchtvochtigheid, int lichtSterkte, int CO2, int geluid) {
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    
    char tempS[8];
    char gevoelsTempS[8];
    char luchtvochtigheidS[8];
    
    dtostrf(temp,-4,2,tempS);
    dtostrf(gevoelsTemp,-4,2,gevoelsTempS);
    dtostrf(luchtvochtigheid,-4,2,luchtvochtigheidS);
    
    char buffer[200];
    sprintf(buffer, "I|%ld|%s|%s|%s|%s|%d|%d|%d||||", tijd, datum, tempS, gevoelsTempS, luchtvochtigheidS, lichtSterkte, CO2, geluid);
    log_println(buffer);
    file.println(buffer);
    file.close();
    
    return true;
  } else {
    log_println(F("Data bestand openen mislukt"));
    return false;
  }
}

String opslag_getDataFileLocation(){
  return dataFolder + '/' + dataFile;
}

String opslag_getConfigFileLocation(){
  return dataFolder + '/' + configFile;
}

// call back for file timestamps
void dateTime(uint16_t* date, uint16_t* time) {
 DateTime now = rtc.now();

 // return date using FAT_DATE macro to format fields
 *date = FAT_DATE(now.year(), now.month(), now.day());

 // return time using FAT_TIME macro to format fields
 *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

bool opslag_getVraag(int vraagnr, int regelnr, char* retBuf) {
  if(!ini.open() || vraagnr < 0 || vraagnr >= opslag_aantal_vragen || 
  regelnr < 0 || regelnr >= 4) {
    return false;
  }
  
  //aantal antwoorden ophalen
  opslag_aantal_antwoorden = 0;
  char keyBuf[18];
  char secBuf[18];
  sprintf(keyBuf, "antwoord%d_deel0", 0);
  sprintf(secBuf, "vraag%d", vraagnr);
  
  while (ini.getValue(secBuf, keyBuf, retBuf, 80)) {
    opslag_aantal_antwoorden++;
    sprintf(keyBuf, "antwoord%d_deel0", opslag_aantal_antwoorden);
  }

  //vraag ophalen
  sprintf(keyBuf, "vraag_deel%d", regelnr);
  if(ini.getValue(secBuf, keyBuf, retBuf, 80)){
    ini.close();
    opslag_vraag_nr = vraagnr;
    return true;
  }

  ini.close();
  return false;
}

bool opslag_getAntwoord(int vraagnr, int antwoordnr, int regelnr, char* antwoordbuf) {
  if(!ini.open() || vraagnr < 0 || vraagnr >= opslag_aantal_vragen || 
  antwoordnr < 0 || antwoordnr >= opslag_aantal_antwoorden ||
  regelnr < 0 || regelnr >= 3) {
    log_println("Er ging iets mis");
    return false;
  }
  
  char keyBuf[18];
  char secBuf[18];
  sprintf(secBuf, "vraag%d", vraagnr);
  sprintf(keyBuf, "antwoord%d_deel%d", antwoordnr, regelnr);
  if(ini.getValue(secBuf, keyBuf, antwoordbuf, 80)) {
    ini.close();
    return true;
  }
  ini.close();
  return false;
}

int opslag_getAntwoordAantal() {
  return opslag_aantal_antwoorden;
}

int opslag_getVraagAantal() {
  return opslag_aantal_vragen;
}

int opslag_getVraagNr() {
  return opslag_vraag_nr;
}

void opslag_sendData() {
  File file = SD.open(opslag_getDataFileLocation(), FILE_READ);

  
  if (file) {
    Serial.println(file.size());
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    log_println(F("Kan data file niet openen"));
  }
}

void opslag_sendConfig() {
  File file = SD.open(opslag_getConfigFileLocation(), FILE_READ);
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    log_println(F("Kan config file niet openen"));
  }
}

void opslag_recConfig() {
  if(SD.exists(opslag_getConfigFileLocation())) {
    if(!SD.remove(opslag_getConfigFileLocation())) {
      log_println(F("Kan config file niet verwijderen"));
    }
  }
  File file = SD.open(opslag_getConfigFileLocation(), FILE_WRITE);
  if(file) {
    char in;
    while(true) {
      if(Serial.available()){
        in = (char)Serial.read();
        if( in == '$' ) {
          break;
        }
        file.write(in);
      }
    }

    
//    char in;
//    do {
//      in = (char)Serial.read();
//    } while (
//    while(Serial.available()) {
//      char in = (char)Serial.read();
//      file.write(in);
//      Serial.write(in);
//      if(!Serial.available()) {
//        delay(5);
//      }
//    }
    file.close();
  } else {
    log_println(F("Kan config file niet aanmaken"));
  }
}

void opslag_verwijderData() {
  if(SD.exists(opslag_getDataFileLocation())) {
    if(!SD.remove(opslag_getDataFileLocation())) {
      log_println(F("Kan data file niet verwijderen"));
    }
  }
}

bool opslag_magOpDezeDag(int dag) {
  return dagen[dag];
}

int opslag_getBegintijd() {
  return opslag_begintijd;
}

int opslag_getEindtijd() {
  return opslag_eindtijd;
}

int opslag_getVraagInterval() {
  return opslag_vraaginterval;
}

int opslag_getSensorInterval() {
  return opslag_sensorinterval;
}



