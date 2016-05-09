// ANALOG 0-5
#define POTMETER_PIN 0

// INTERRTUPT 0-1
#define SELECTEER_PIN 0

// DIGITAL 3-13
#define BUZZER_PIN 3
#define LICHT_PIN 4

const long baud = 57600;

// Initieer alle componenten
void setup(){
  log_init(baud);
  opslag_init();
  knoppen_init(SELECTEER_PIN, POTMETER_PIN);
  buzzer_init(BUZZER_PIN);
  licht_init(LICHT_PIN);
  
  knoppen_set_pot_callback(&pot_callback);

  log_println("Alle componenten zijn geïnitialiseerd ");
}

int screen = 1;
void loop(){
  opslag_loop();
  knoppen_loop();
  buzzer_loop();
}

void pot_callback(int val){
}
