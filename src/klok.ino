
void klok_init()
{
  rtc.begin();
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
  String out = rtc.getDateStr();
  out += " -- ";
  out += rtc.getTimeStr();
  // Send date
  return out;

}
/**
* Get unix time stemp
*/
long klok_getUnitxTime(){
  return rtc.getUnixTime(rtc.getTime());
}
