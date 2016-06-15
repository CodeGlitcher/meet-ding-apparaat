byte modus = 0; // 0 = inactief, 1 = vraag stellen, 2 = data opslaan, 3 = bedanken
long modus_last_change;

long last_question = 0;

bool potmeter_has_changed = false;

inline void interface_loop(){
  bool shouldAsk = modus == 0;
  shouldAsk = shouldAsk && (millis() - last_question > opslag_getVraagInterval() * 1000);
  shouldAsk = shouldAsk && (opslag_getBegintijd() < klok_getHour());
  shouldAsk = shouldAsk && (opslag_getEindtijd() > klok_getHour());
  
  if (shouldAsk){
    scherm_reset();
    scherm_stel_vraag();
    scherm_draw_cijfer(-1);
    potmeter_has_changed = false;
//    scherm_aan();
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
    int lichtSterkte = analogRead(1);
    int CO2 = 0;
    int geluid = 0;
    int antwoordNr = knoppen_potmeter_waarde();
    
    opslag_SaveUserData(time, timeString,temp,heatIndex,humidity, lichtSterkte, CO2, geluid, antwoordNr);

    if (scherm_get_curvraagnr() != 0){
      scherm_reset();
      scherm_stel_vraag();
      scherm_draw_cijfer(-1);
      potmeter_has_changed = false;
//      scherm_aan();
      modus=1;
    } else {
      modus_last_change = millis();
      scherm_reset();
      scherm_draw_bedankt(10,50);
      modus=3;
    }
  }

  if (modus==3 && millis() - modus_last_change > 5000){
    last_question = millis();
    
    modus=0;
    modus_last_change = millis();
    scherm_reset();
//    scherm_uit();    
  }
}

void interface_selecteer_pressed(){
  if (modus==1 && potmeter_has_changed){
    modus = 2;
  }
}

void interface_potmeter_changed(int antwoordnr) {
  if (modus!=1){
    return;
  }

  potmeter_has_changed = true;
  
  scherm_draw_cijfer(antwoordnr);
}
