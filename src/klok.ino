RTC_DS3231 rtc;

void klok_init()
{

  if (! rtc.begin()) {
    log_println("Klok niet gevonden");
    return;
  }
  log_println("Klok gevonden");
  // use the following commands to set date and time
  // rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
  // rtc.setTime(10, 52, 0);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(26, 4, 2016);   // Set the date to January 1st, 2014
}

void klok_loop()
{

}
/**
* Get date time sting.
* 26-4-2016 -- 12:00
*/
String klok_getDateTime(){
  DateTime now = rtc.now();
  String out = "";
  out +=now.day() ;
  out+= "-";
  out+= now.month();
  out+= "-";
  out+= now.year();
  out+= " -- " ;
  out+= now.hour();
  out+= ":";
  out+= now.minute();
  // Send date
  return out;
}
/**
* Get unix time stemp
*/
long klok_getUnitxTime(){
  DateTime now = rtc.now();
  return now.unixtime();
}
