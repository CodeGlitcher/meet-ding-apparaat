
/**
* DHT11 Temperature Sensor
*/
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//temp values
float humidity, celcius, fahrenheit = 0.0;

//interval in millis
bool do_interval = true;
unsigned long prev_millis = 0;
const long interval = 500;

void setupTempSensor(long port)  {
  Serial.begin(port);
  Serial.println("DHT11 setup");
  dht.begin();
}

void loopTempSensor() {
  if(do_interval) {
    unsigned long curr_millis = millis();
    if(curr_millis - prev_millis >= interval) {
      prev_millis = curr_millis;
      readDHTValues();
    }
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
