const long baud = 57600;

// Initieer alle componenten
void setup(){
  log_init(baud);
  opslag_init();
  knoppen_init(2,4);

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop(){
  opslag_loop();
  knoppen_loop();
}
