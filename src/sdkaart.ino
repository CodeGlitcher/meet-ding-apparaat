
IniFile ini = IniFile("config.ini");

int opslag_pin;
int opslag_aantal_antwoorden;
int opslag_aantal_vragen;
int opslag_vraag_nr;
int opslag_antwoord_nr;

int opslag_begintijd;
int opslag_eindtijd;



// alles komt om een of andere rede in hoofdletters te staan. Hier ook maar.
String dataFolder = "ARDUINO";
String dataFile = "DATA.csv";
/**
* This file contains logic for data storage
*/
inline void opslag_init(){
  SdFile::dateTimeCallback(dateTime);
 
  if (!SD.begin(SD_KAART_PIN)) {
    log_println(F("SD-kaart niet gevonden"));
    return;
  }
  
  if(!SD.exists(opslag_getDataFileLocation())){
    log_println(F("Bestand bestaat niet"));
    
    // maak folder
    SD.mkdir(dataFolder);
    
    // open data file
    File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  
    // check if file exist
    if (file) {
      // Headerrow
      file.println(F("Tijd(ms),Datum,Temperatuur,Gevoelstemperatuur,Luchtvochtigheid,Lichtkleur,Lichtsterkte,CO2,Geluid,Vraagnummer,Vraag,Antwoordnummer,Antwoord"));
      file.close();
    } else {
      log_println(F("Data bestand aanmaken mislukt"));
    }
  }
  
  if(ini.open()) {
    char retBuf[80];
    
    //aantal vragen ophalen
    opslag_aantal_vragen = 0;
    char buf[8];
    sprintf(buf, "vraag%d", 0);
    while (ini.getValue(buf, "vraag", retBuf, 80)) {
      opslag_aantal_vragen++;
      sprintf(buf, "vraag%d", opslag_aantal_vragen);
    }
    
    //begin en eind tijden ophalen
    if(!ini.getValue("tijden", "begintijd", retBuf, 80, opslag_begintijd) || !ini.getValue("tijden", "eindtijd", retBuf, 80, opslag_eindtijd)) {
      log_println(F("Kan tijden niet inlezen"));
    }
    
    ini.close();
  } else {
    log_println(F("Config file niet aanwezig"));
  }
}

/**
* Voeg data toe aan het data bestand.
*/
bool opslag_SaveData(long tijd, char* datum, float temp, float gevoelsTemp, float luchtvochtigheid, int lichtKleur, int lichtSterkte, int CO2, int geluid, int antwoordNr){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    
    char tempS[8];
    char gevoelsTempS[8];
    char luchtvochtigheidS[8];
    
    dtostrf(temp,-4,2,tempS);
    dtostrf(gevoelsTemp,-4,2,gevoelsTempS);
    dtostrf(luchtvochtigheid,-4,2,luchtvochtigheidS);

    char vraag[80];
    char antwoord[80];
    opslag_getVraag(opslag_vraag_nr, vraag);
    opslag_getAntwoord(opslag_vraag_nr, antwoordNr, antwoord);
    
    char buffer[100];
    sprintf(buffer, "%ld,%s,%s,%s,%s,%d,%d,%d,%d,%d,%s,%d,%s", tijd, datum, tempS, gevoelsTempS, luchtvochtigheidS, lichtKleur, lichtSterkte, CO2, geluid, opslag_vraag_nr, vraag, antwoordNr, antwoord);
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

// call back for file timestamps
void dateTime(uint16_t* date, uint16_t* time) {
 DateTime now = rtc.now();

 // return date using FAT_DATE macro to format fields
 *date = FAT_DATE(now.year(), now.month(), now.day());

 // return time using FAT_TIME macro to format fields
 *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

bool opslag_getVraag(int vraagnr, char* retBuf) {
  if(!ini.open() || vraagnr < 0 || vraagnr >= opslag_aantal_vragen) {
    return false;
  }

  //aantal antwoorden ophalen
  opslag_aantal_antwoorden = 0;
  char antBuf[11];
  char vrgBuf[8];
  sprintf(antBuf, "antwoord%d", 0);
  sprintf(vrgBuf, "vraag%d", vraagnr);
  
  while (ini.getValue(vrgBuf, antBuf, retBuf, 80)) {
    opslag_aantal_antwoorden++;
    sprintf(antBuf, "antwoord%d", opslag_aantal_antwoorden);
  }

  //vraag ophalen
  if(ini.getValue(vrgBuf, "vraag", retBuf, 80)){
    ini.close();
    opslag_vraag_nr = vraagnr;
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

bool opslag_getAntwoord(int vraagnr, int antwoordnr, char* antwoordbuf) {
  if(!ini.open() || antwoordnr < 0 || antwoordnr >= opslag_aantal_antwoorden) {
    return false;
  }
  
  char antBuf[11];
  char vrgBuf[8];
  sprintf(vrgBuf, "vraag%d", vraagnr);
  sprintf(antBuf, "antwoord%d", antwoordnr);
  if(ini.getValue(vrgBuf, antBuf, antwoordbuf, 80)) {
    ini.close();
    return true;
  }
  ini.close();
  return false;
}

