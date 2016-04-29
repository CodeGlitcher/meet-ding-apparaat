#include "printf.h"
long serialPort = 115200;

void setup()  {
  Serial.begin(serialPort);
  // printf_begin();

  setupSdkaart();
  setupTempSensor(serialPort);
}

void loop() {
  loopTempSensor();

  Serial.print("Celcius: ");
  Serial.print(getCelcius());
  Serial.println(" ");
}
