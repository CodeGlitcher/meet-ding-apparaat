byte modus = 0; // 0 = inactief, 1 = vraag stellen, 2 = data opslaan, 3 = bedanken
long modus_last_change;

inline void interface_loop(){

  if (modus==0){
    scherm_reset();
    scherm_stel_vraag();
    scherm_draw_cijfer(35, 90, -1);
    scherm_aan();
    modus = 1;
  }

  if (modus == 2){
    sensor_temp_read_values();
    long  time = klok_getUnixTime();
    char timeString[17];
    klok_getDateTime(timeString);
    double temp = sensor_temp_celcius();
    double heatIndex = sensor_temp_heatindex_c();
    double humidity = sensor_temp_humidity();
    int lichtKleur = 0;
    int lichtSterkte = analogRead(1);
    int CO2 = 0;
    int geluid = 0;
    int antwoordNr = knoppen_potmeter_waarde();
    
    opslag_SaveData(time, timeString,temp,heatIndex,humidity, lichtKleur, lichtSterkte, CO2, geluid, antwoordNr);

    modus_last_change = millis();
    scherm_reset();
    scherm_draw_bedankt(10,50);


    modus=3;
  }

  if (modus==3 && millis() - modus_last_change > 5000){
    modus=0;
    modus_last_change = millis();
    scherm_reset();
    scherm_uit();    
  }
}

void interface_selecteer_pressed(){
  if (modus==1){
    modus = 2;
  }
}

void interface_potmeter_changed(int val) {
  if (modus!=1){
    return;
  }
  
  scherm_draw_cijfer(35, 90, val);
}
