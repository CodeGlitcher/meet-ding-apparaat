// ANALOG 0-5
#define POTMETER_PIN 0

// INTERRTUPT 0-1
#define SELECTEER_PIN 0

// DIGITAL 3-13
#define BUZZER_PIN 3
#define LICHT_PIN 4
#define TEMP_PIN 5

const long baud = 57600;

void setup()  {
  log_init(baud);

  opslag_init();
  knoppen_init(SELECTEER_PIN, POTMETER_PIN);
  buzzer_init(BUZZER_PIN);
  licht_init(LICHT_PIN);
  
  sensor_temp_init();

  log_print("Alle componenten zijn geïnitialiseerd ");
}

void loop() {
  sensor_temp_loop();
  opslag_loop();
  knoppen_loop();
  buzzer_loop();
}
