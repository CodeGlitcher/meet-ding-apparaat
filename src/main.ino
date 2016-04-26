const long baud = 115200;

// Initieer alle componenten
void setup(){
  log_init(baud);
  opslag_init();
  knoppen_init(0,4);

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop(){
  opslag_loop();
  knoppen_loop();
}
