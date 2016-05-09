


int opslag_pin;
// alles komt om een of andere rede in hoofdletters te staan. Hier ook maar.
String dataFolder = "ARDUINO/DATA";
String dataFile = "DATA.csv";
/**
* This file contains logic for data storage
*/
void opslag_init(int sdpin){
  opslag_pin = sdpin;
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
   file.println("Tijd,Temperatuur,Luchtvochtigheid,kleur");
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
bool opslag_SaveData(long tijd, int temp, float luchtvochtigheid){
  File file = SD.open(opslag_getDataFileLocation(), FILE_WRITE);
  if (file) {
    opslag_addData(file, String(tijd));
    opslag_addData(file, String(temp));
    opslag_addData(file, String(luchtvochtigheid,2)); // float afronden 2 decimalen
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
