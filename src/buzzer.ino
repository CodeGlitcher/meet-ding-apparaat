int buzzer_pin;
int buzzer_beep;
bool buzzer_on = false;
long buzzer_laatste_loop;

void buzzer_init(int pin){
  buzzer_pin = pin;
  buzzer_beep = false;

  pinMode(buzzer_pin, OUTPUT);
}

void buzzer_loop(){
  if (millis() - buzzer_laatste_loop > 100){
    buzzer_laatste_loop = millis();

    if (!buzzer_on && buzzer_beep > 0){
      buzzer_on = true;
      buzzer_beep--;

      digitalWrite(buzzer_pin, HIGH);
    } else {
      buzzer_on = false;

      digitalWrite(buzzer_pin, LOW);
    }
  }

}

inline void buzzer_warn(int beeps){
  buzzer_beep = beeps;
}

inline void buzzer_warn(){
  buzzer_beep = 2;  
}
