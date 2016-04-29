
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

void sensor_temp_init()  {
  Serial.begin(115200);
  dht.begin();
}

void sensor_temp_loop() {
   if(millis() - prev_millis >= 1000) {
     prev_millis = millis();
     sensor_temp_read_values();
  
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

void sensor_temp_read_values() {
  humidity = dht.readHumidity();
  celcius = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);
}

float sensor_temp_humidity() {
  return humidity;
}

float sensor_temp_celcius() {
  return celcius;
}

float sensor_temp_fahrenheit() {
  return fahrenheit;
}

//Gevoelens tempratuur in celcius
float sensor_temp_heatindex_c() {
  return dht.computeHeatIndex(celcius, humidity);
}

//Fahrenheit == false
float sensor_temp_heatindex_f() {
  return dht.computeHeatIndex(fahrenheit, humidity, false);
}
