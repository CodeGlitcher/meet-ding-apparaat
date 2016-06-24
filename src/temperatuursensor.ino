// Deze module communiceert met de temperatuur sensor
// tem -> temperatuur

/**
* DHT22 Temperature Sensor
*/
DHT dht(DHTPIN, DHTTYPE);

//temp values
float humidity, celcius, fahrenheit = 0.0;

long prev_millis = 0;

inline void tem_init()  {
  log_print(F("DHT sensor"));
  dht.begin();
  log_println(F(" ... klaar"));
}

void tem_readValues() {
  humidity = dht.readHumidity();
  celcius = dht.readTemperature() + CELCIUS_CORRECTION;
  fahrenheit = dht.readTemperature(true);
}

float tem_humidity() {
  return humidity;
}

float tem_celcius() {
  return celcius;
}

float tem_fahrenheit() {
  return fahrenheit;
}

//Gevoelstempratuur in celcius
float tem_heatIndexC() {
  return dht.computeHeatIndex(celcius, humidity, false);
}

//Fahrenheit == false
float tem_heatIndexF() {
  return dht.computeHeatIndex(fahrenheit, humidity, true);
}
