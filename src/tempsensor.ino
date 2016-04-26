
/**
* DHT11 Temprature Sensor
*/
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setupTempSensor()  {
  Serial.begin(115200);
  Serial.println("DHT11 setup");
  dht.begin();
}

void loopTempSensor() {

  //Read values
  float humidity = dht.readHumidity();
  float celcius = dht.readTemperature();
  float fahrenheit = dht.readTemperature(true);



  //Heat index


  Serial.println("Humidity: ");
  Serial.print(humidity);
  Serial.println("Celcius: ");
  Serial.print(celcius);
  delay(2000);
}
