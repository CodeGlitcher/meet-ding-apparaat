


int opslag_pin;
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
  
  if(SD.exists(opslag_getDataFileLocation())){
    log_println(F("Bestand bestaat"));
    return;// bestand bestaat al.
  }
  
  // maak folder
  SD.mkdir(dataFolder);
  
  // open data file
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);

  // check if file exist
  if (file) {
    // Headerrow
    file.println(F("Tijd (ms),Tijd (String),Cijfer,Temperatuur,Gevoelstemperatuur,Luchtvochtigheid,lichtkleur,lichtsterkte,co2, geluid"));
    file.close();
  } else {
    log_println(F("Data bestand aanmaken mislukt"));
  }

}

/**
* Voeg data toe aan het data bestand.
*/
bool opslag_SaveData(long tijd, char* tijdString, float temp, float gevoelsTemp, float luchtvochtigheid){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    int cijfer = knoppen_potmeter_waarde();
    int lichtsterkte = analogRead(A1);

    char tempS[8];
    char gevoelsTempS[8];
    char luchtvochtigheidS[8];
    
    dtostrf(temp,-4,2,tempS);
    dtostrf(gevoelsTemp,-4,2,gevoelsTempS);
    dtostrf(luchtvochtigheid,-4,2,luchtvochtigheidS);
    
    char buffer[100];
    sprintf(buffer, "%ld,%s,%d,%s,%s,%s,%d,%d,%d,%d", tijd, tijdString, cijfer, tempS, gevoelsTempS, luchtvochtigheidS, 0, lichtsterkte, 0, 0);
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
