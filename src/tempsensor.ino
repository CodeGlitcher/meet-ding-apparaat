
/**
* DHT11 Temperature Sensor
*/
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float humidity, celcius, fahrenheit = 0.0;

void setupTempSensor(long port)  {
  Serial.begin(port);
  Serial.println("DHT11 setup");
  dht.begin();
}

void loopTempSensor() {

  //Read values
  humidity = dht.readHumidity();
  celcius = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);

  //test delay
  delay(1000);
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
