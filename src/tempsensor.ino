
/**
* DHT22 Temperature Sensor
*/
#include "DHT.h"
#define DHTTYPE DHT22
DHT dht(TEMP_PIN, DHTTYPE);

//temp values
float humidity, celcius, fahrenheit = 0.0;

long prev_millis = 0;

void sensor_temp_init()  {
  dht.begin();
}

void sensor_temp_loop() {
   if(millis() - prev_millis >= 1000) { //1 sec test
     prev_millis = millis();
     sensor_temp_read_values();
  
     log_enable();

     //http://stackoverflow.com/questions/905928/using-floats-with-sprintf-in-embedded-c
     char str[100];
     int d1 = celcius; //get integer
     float f2 = celcius - d1; //get fractional
     int d2 = trunc(f2 * 10000); //to integer
  
     sprintf (str, "Celcius: %d.%04d\n", d1, d2);
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
