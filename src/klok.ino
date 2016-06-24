// Deze module regelt de communicatie met de klok.
// Door de klok (RTC) blijft de tijde gelijk lopen met
// de werkelijke tijd. Ook als de klimaatscanner uit is geweest
// klk -> klok

RTC_DS3231 rtc;

// Initialisatie van de klok
void klk_init()
{
  log_print(F("Klok"));
  if (! rtc.begin()) {
    log_println(F(" .. niet gevonden"));
    return;
  }
  log_println(F(" ... klaar"));
}

//Vult de buffer met de tijd als string.
inline void klk_getDateTime(char *buffer){
  DateTime now = rtc.now();
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute());
}

//Geeft unix time stemp
inline long klk_getUnixTime(){
  DateTime now = rtc.now();
  return now.unixtime();
}

// Geeft het huidige uur
int klk_getHour() {
  return rtc.now().hour();
}

// Geeft de huidige dag
int klk_getDayOfWeek() {
  return (rtc.now().dayOfTheWeek() - 1) % 7;
}

void readTime(){
  String time ="";
  char in;
  while(true) {
    if(Serial.available()){
      in = (char)Serial.read();
      if( in == '$' ) {
        break;
      }
      time += in;
    }
  }
  DateTime x = DateTime(time.toInt());
  rtc.adjust(x);
}
 

