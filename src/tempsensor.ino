
/**
* DHT11 Temperature Sensor
*/
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//temp values
float humidity, celcius, fahrenheit = 0.0;

long prev_millis = 0;

void setupTempSensor()  {
  Serial.begin(115200);
  dht.begin();
}

void loopTempSensor() {
   if(millis() - prev_millis >= 1000) {
     prev_millis = millis();
     readDHTValues();
  
     log_enable();
  
     char str[100];
     int d1 = celcius;            // Get the integer part (678).
     float f2 = celcius - d1;     // Get fractional part (0.01234567).
     int d2 = trunc(f2 * 10000);   // Turn into integer (123).
     float f3 = f2 * 10000 - d2;   // Get next fractional part (0.4567).
     int d3 = trunc(f3 * 10000);   // Turn into integer (4567).
  
     sprintf (str, "Celcius: %d.%04d%04d\n", d1, d2, d3);
  
     log_println(str);
     log_disable();
   }
}

void readDHTValues() {
  //Read values
  humidity = dht.readHumidity();
  celcius = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);
}

float getHumidity() {
  return humidity;
}

float getCelcius() {
  return celcius;
}

float getFahrenheit() {
  return fahrenheit;
}

//Gevoelens tempratuur in celcius
float getHeatIndexC() {
  return dht.computeHeatIndex(celcius, humidity);
}

//Fahrenheit == false
float getHeatIndexF() {
  return dht.computeHeatIndex(fahrenheit, humidity, false);
}
