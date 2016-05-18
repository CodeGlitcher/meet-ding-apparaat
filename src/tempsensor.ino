
/**
* DHT22 Temperature Sensor
*/
DHT dht(DHTPIN, DHTTYPE);

//temp values
float humidity, celcius, fahrenheit = 0.0;

long prev_millis = 0;

inline void sensor_temp_init()  {
  dht.begin();
}

void sensor_temp_loop() {

}

void sensor_temp_read_values() {
  humidity = dht.readHumidity();
  celcius = dht.readTemperature() + CELCIUS_CORRECTION;
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
