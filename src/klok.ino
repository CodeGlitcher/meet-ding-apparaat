RTC_DS3231 rtc;

void klok_init()
{
  log_print(F("Klok"));
  if (! rtc.begin()) {
    log_println(F(" .. niet gevonden"));
    return;
  }
  log_println(F(" ... klaar"));
  // use the following commands to set date and time
  // rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
  // rtc.setTime(10, 52, 0);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(26, 4, 2016);   // Set the date to January 1st, 2014
}

/**
* Get date time sting.
* 26-4-2016 -- 12:00
*/
inline void klok_getDateTime(char *buffer){
  DateTime now = rtc.now();
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute());
}
/**
* Get unix time stemp
*/
inline long klok_getUnixTime(){
  DateTime now = rtc.now();
  return now.unixtime();
}

int klok_getHour() {
  return rtc.now().hour();
}

int klok_getDayOfWeek() {
  return (rtc.now().dayOfTheWeek() - 1) % 7;
}


