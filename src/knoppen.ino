int knoppen_selecteer_pin;
int knoppen_potmeter_pin;

int knoppen_potmeter_waarde;

void knoppen_init(int selecteer, int pot){
  knoppen_selecteer_pin = selecteer;
  knoppen_potmeter_pin = pot;

  pinMode(knoppen_selecteer_pin,INPUT);
  //pinMode(knoppen_potmeter_pin, INPUT);

  attachInterrupt(knoppen_selecteer_pin, knop_selecteer, FALLING);
}

void knop_selecteer(){

}

void knoppen_loop(){
  //char buffer [50];
  //sprintf(buffer, "potmeterwaarde is: %d", analogRead(knoppen_potmeter_pin));
  //delay(1000);
  //log_println(buffer);
}
