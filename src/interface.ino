// Deze module handelt de interface, en de interactie er mee af.
// inf -> interface

// Variabelen
byte modus = 0; // 0 = inactief, 1 = vraag stellen, 2 = data opslaan, 3 = bedanken
long modus_last_change = 0;
long last_question = 0;
long question_asked = 0;
bool potmeter_has_changed = false;

// Kijk of er iets moet veranderen
inline void inf_loop(){
  
  // Moeten we beginnen met vragen stellen?
  bool shouldAsk = modus == 0;
  shouldAsk = shouldAsk && (millis() - last_question > ops_getVraagInterval() * 1000ul);
  shouldAsk = shouldAsk && ops_magOpDezeDag(klk_getDayOfWeek());
  shouldAsk = shouldAsk && (ops_getBegintijd() < klk_getHour());
  shouldAsk = shouldAsk && (ops_getEindtijd() > klk_getHour());  

  // Ja, vragen stellen
  if (shouldAsk){
    sch_reset();
    sch_stelVraag();
    sch_drawCijfer(-1);
    potmeter_has_changed = false;
    modus = 1;
    question_asked = millis();
  }
  
  // check of er al 5 min lang een vraag wordt gesteld
  if (modus == 1) {
    long dif = millis() - question_asked;
    long minute = 60l*1000;
    if (dif > 5 * minute) {                //als vraag langer dan 5 minuten gesteld wordt
      last_question = millis();
      modus = 0;
      sch_reset();
      digitalWrite(WARNLED_PIN, LOW);
    } else if (dif > 4*minute) {
      digitalWrite(WARNLED_PIN, HIGH);
    } else if (dif > 3*minute)  {
      digitalWrite(WARNLED_PIN, (dif % 500 < 250));
    } else if (dif > 2*minute) {
      digitalWrite(WARNLED_PIN, (dif % 1000 < 500));
    } else if (dif > minute) {
      digitalWrite(WARNLED_PIN, (dif % 2000 < 1000));
    }
  }

  // Als er een antwoord gegeven is
  if (modus == 2){
    digitalWrite(WARNLED_PIN, LOW);
    tem_readValues();
    long  time = klk_getUnixTime();
    char timeString[17];
    klk_getDateTime(timeString);
    double temp = tem_celcius();
    double heatIndex = tem_heatIndexC();
    double humidity = tem_humidity();
    int lichtSterkte = analogRead(1);
    int CO2 = 0;
    int geluid = 0;
    int antwoordNr = knp_potmeterWaarde();
    
    ops_saveUserData(time, timeString,temp,heatIndex,humidity, lichtSterkte, CO2, geluid, antwoordNr);

    if (sch_getCurVraagNr() != 0){
      sch_reset();
      sch_stelVraag();
      sch_drawCijfer(-1);
      potmeter_has_changed = false;
      modus=1;
      question_asked = millis();
    } else {
      modus_last_change = millis();
      sch_reset();
      sch_drawBedankt(10,50);
      modus=3;
    }
  }

  if (modus==3 && millis() - modus_last_change > 5000){
    last_question = millis();
    
    modus=0;
    modus_last_change = millis();
    sch_reset();   
  }
}

// Als er op de knop is gedrukt
void inf_selecteerPressed(){
  if (modus==1 && potmeter_has_changed){
    modus = 2;
  }
}

// Als er aan de potmeter is gedraaid
void inf_potmeterChanged(int antwoordnr) {
  if (modus!=1){
    return;
  }

  potmeter_has_changed = true;
  
  sch_drawCijfer(antwoordnr);
}
