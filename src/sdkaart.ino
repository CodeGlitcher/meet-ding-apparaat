


int opslag_pin;
// alles komt om een of andere rede in hoofdletters te staan. Hier ook maar.
String dataFolder = "ARDUINO/DATA";
String dataFile = "DATA.csv";
/**
* This file contains logic for data storage
*/
void opslag_init(){
  SdFile::dateTimeCallback(dateTime);
  
  if (!SD.begin(SD_KAART_PIN)) {
    log_println("SD-kaart niet gevonden");
    return;
  }
  
  if(SD.exists(opslag_getDataFileLocation())){
    log_println("Bestand bestaat");
    return;// bestand bestaat al.
  }
  
  // maak folder
  SD.mkdir(dataFolder);
  
  // open data file
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);

  // check if file exist
  if (file) {
    // Headerrow
    file.println("Tijd (ms)|Tijd (String)|Temperatuur|Gevoelstemperatuur|Luchtvochtigheid");
    file.close();
  } else {
    log_println("Data bestand aanmaken mislukt");
  }

}

void opslag_loop(){

}

/**
* Voeg data toe aan het data bestand.
*/
bool opslag_SaveData(long tijd, String tijdString, float temp, float gevoelsTemp, float luchtvochtigheid){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    
    char buffer[100];
    sprintf(buffer, "%d|%f|%f|%f", tijd, temp, gevoelsTemp, luchtvochtigheid);
    log_println(buffer);
    file.println(buffer);
    
    return true;
  } else {
    log_println("Data bestand openen mislukt");
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
