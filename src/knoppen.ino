// Deze module zorgt voor interactie met de knoppen
// knp -> knoppen

long knoppen_laatst_gedrukt = 0;
long knoppen_laatste_loop = 0;

int knoppen_potmeter_laatste_waarde = -1;

void (*knoppen_select_func)(void);
void (*knoppen_pot_func)(int);

// Initaliseerd knoppen
inline void knp_init()
{
  log_print(F("Knoppen"));
  attachInterrupt(SELECTEER_PIN, knp_selecteer, FALLING);
  log_println(" ... klaar");
}

// Stel een callback functie in voor de knop
void knp_setSelecteerCallback(void(*f)(void))
{
  knoppen_select_func = f;
}

// Stel een callback functie in voor potmeter
void knp_setPotCallback(void(*f)(int))
{
  knoppen_pot_func = f;
}

// Controlleer of de knop is ingedrukt en roep de callback aan
void knp_selecteer()
{
  if (millis() - knoppen_laatst_gedrukt < 250){
    return;
  }
  knoppen_laatst_gedrukt = millis();
  
  log_println("Knop ingedrukt");

  if (knoppen_select_func){
    knoppen_select_func();
  } else {
    log_println("Geen knop callback");
  }
}

// Controleer of er waardes veranderen, zo ja, dan is de potmeter veranderd
void knp_loop()
{
  if (millis() - knoppen_laatste_loop > 50){
    knoppen_laatste_loop = millis();

    int huidige_waarde = knp_potmeterWaarde();
    if (knoppen_potmeter_laatste_waarde != huidige_waarde){
      knoppen_potmeter_laatste_waarde = huidige_waarde;
      
      char buffer[23];
      sprintf(buffer, "Potmeter waarde is: %d", huidige_waarde);
      log_println(buffer);

      if (knoppen_pot_func){
        knoppen_pot_func(huidige_waarde);
      } else {
        log_println(F("Geen potmeter callback"));
      }
    }
  }
}

// Bereken de waarde van de potmeter
int knp_potmeterWaarde()
{
  // 0 - 1023 -> 0-100
  int knoppen__potmeter_waarde = analogRead(POTMETER_PIN);

  // 0-1000
  knoppen__potmeter_waarde -= 12;
  if (knoppen__potmeter_waarde > 1000) {
    knoppen__potmeter_waarde = 1000;
  } else if (knoppen__potmeter_waarde < 0) {
    knoppen__potmeter_waarde = 0;
  }

  knoppen__potmeter_waarde /= (1000.0/ops_getAntwoordAantal());
  knoppen__potmeter_waarde = knoppen__potmeter_waarde == ops_getAntwoordAantal() ? ops_getAntwoordAantal()-1 : knoppen__potmeter_waarde;

  return knoppen__potmeter_waarde;
}
