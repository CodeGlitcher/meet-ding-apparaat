int licht_pin;

void licht_init(int pin) {
  licht_pin = pin;

  pinMode(licht_pin, OUTPUT);
}


inline void licht_aan() {
  digitalWrite(licht_pin, HIGH);
}

inline void licht_uit() {
  digitalWrite(licht_pin, LOW);
}
