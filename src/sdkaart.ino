


int opslag_pin;
// alles komt om een of andere rede in hoofdletters te staan. Hier ook maar.
String dataFolder = "ARDUINO/DATA";
String dataFile = "DATA.csv";
/**
* This file contains logic for data storage
*/
void opslag_init(int sdpin){
  opslag_pin = sdpin;
  SdFile::dateTimeCallback(dateTime);
  if (!SD.begin(opslag_pin)) {
    log_println("SD-kaart niet gevonden");
    return;
  }
  if(SD.exists(opslag_getDataFileLocation())){
    log_println("Bestand bestaat");
    return;// bestand bestaat al.
  }
  // maake folder
  SD.mkdir(dataFolder);
  // open data file
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);

// check if file exist
 if (file) {
   // add header to file (TODO add more)
   file.println("Tijd (ms),Tijd (String),Temperatuur,Gevoelstemperatuur,Luchtvochtigheid");
   // close the file:
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
bool opslag_SaveData(long tijd,String tijdString, float temp, float gevoelsTemp, float luchtvochtigheid){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    opslag_addData(file, String(tijd));
    opslag_addData(file,tijdString);
    opslag_addData(file, String(temp));
    opslag_addData(file, String(gevoelsTemp));
    opslag_addData(file, String(luchtvochtigheid));
    file.println("");
    file.close();
    return true;
  } else {
    log_println("Data bestand openen mislukt");
    return false;
  }
}

/**
* File f, a open file, String data data to print
*/
void opslag_addData(File f, String data){
  f.print(data);
  f.print(",");
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
