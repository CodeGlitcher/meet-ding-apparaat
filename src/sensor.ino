// Deze module zorgt dat er elk x-aantal seconden een meting wordt opgeslagen
// sns -> sensor

int interval;
long lastRead = 0;

void sns_init() {
  log_print(F("Sensoren"));
  interval = ops_getSensorInterval() * 1000;
  log_println(F(" ... klaar"));
}

void sns_loop() {
  //bekijk of interval voorbij is
  if(interval <= 0 || (millis() - lastRead < interval) || (ops_getBegintijd() > klk_getHour() && klk_getHour() > ops_getEindtijd())) {
    return;
  }
  lastRead = millis();

  tem_readValues();                    // vertel dht22 om sensor uit te lezen
  int co2 = analogRead(CO2_PIN);                // CO2
  int sound = gld_avg();                        // geluid
  double temp = tem_celcius();          // temperatuur
  double humidity = tem_humidity();     // luchtvochtigheid
  double heatIndex = tem_heatIndexC(); // bepaal gevoelstemperatuur
  int lichtSterkte = analogRead(LDR_PIN);       // lichtintensiteit
  long timestamp = klk_getUnixTime();           // timestamp
  char timeString[17];                          
  klk_getDateTime(timeString);                  // leesbare tijd
  
  //sla op in bestand
  ops_saveIntervalData(timestamp, timeString, temp, heatIndex, humidity, lichtSterkte, co2, sound);
}

