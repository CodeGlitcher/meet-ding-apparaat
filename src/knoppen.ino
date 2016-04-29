int knoppen_selecteer_pin;
int knoppen_potmeter_pin;

long laatst_gedrukt = 0;

void (*func)(void);

void knoppen_init(int selecteer, int pot)
{
  knoppen_selecteer_pin = selecteer;
  knoppen_potmeter_pin = pot;

  attachInterrupt(0, knop_selecteer, FALLING);
}

void knoppen_set_selecteer_listener(void(*f)(void))
{
  func = f;
}

void knop_selecteer()
{
  if (millis() - laatst_gedrukt < 250){
    return;
  }
  laatst_gedrukt = millis();

  func();
}

void knoppen_loop()
{
  char buffer[50];
  sprintf(buffer, "Waarde is: %d", knoppen_waarde());
  log_println(buffer);
}

int knoppen_waarde()
{
  // 0 - 1023 -> 0-100
  int knoppen_potmeter_waarde = analogRead(knoppen_potmeter_pin);

  // 0-1000
  knoppen_potmeter_waarde -= 12;
  if (knoppen_potmeter_waarde > 1000) {
    knoppen_potmeter_waarde = 1000;
  } else if (knoppen_potmeter_waarde < 0) {
    knoppen_potmeter_waarde = 0;
  }

  knoppen_potmeter_waarde /= 10;

  return knoppen_potmeter_waarde;
}
