int interval;
long lastRead = 0;

void sensor_init() {
  log_print(F("Sensoren"));
  interval = opslag_getSensorInterval() * 1000;
  log_println(F(" ... klaar"));
}

void sensor_loop() {
  //bekijk of interval voorbij is
//  Serial.println(millis() - lastRead);
//  Serial.print("Interval: ");
//  Serial.println(interval);
  if(interval <= 0 || (millis() - lastRead < interval) || (opslag_getBegintijd() > klok_getHour() && klok_getHour() > opslag_getEindtijd())) {
    return;
  }
  lastRead = millis();

  int co2 = 0;                                  // CO2
  int sound = 0;                                // geluid
  sensor_temp_read_values();                    // vertel dht22 om sensor uit te lezen
  double temp = sensor_temp_celcius();          // temperatuur
  double humidity = sensor_temp_humidity();     // luchtvochtigheid
  double heatIndex = sensor_temp_heatindex_c(); // bepaal gevoelstemperatuur
  int lichtSterkte = analogRead(1);             // lichtintensiteit
  long timestamp = klok_getUnixTime();          // timestamp
  char timeString[17];                          
  klok_getDateTime(timeString);                 // leesbare tijd
  
  //sla op in bestand
  opslag_SaveIntervalData(timestamp, timeString, temp, heatIndex, humidity, lichtSterkte, co2, sound);
}

