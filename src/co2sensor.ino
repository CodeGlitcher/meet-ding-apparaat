#define DC_GAIN (8.5)
#define READ_SAMPLE_TIMES (10)
#define READ_SAMPLE_INTERVAL (50)
#define ZERO_POINT_X (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define ZERO_POINT_VOLTAGE (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define MAX_POINT_VOLTAGE (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define REACTION_VOLTAGE (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

float CO2Curve[3] = {ZERO_POINT_X, ZERO_POINT_VOLTAGE, (REACTION_VOLTAGE / (2.602 - 4))};
int percentage;

void sensor_co2_init() {
    log_print(F("CO2 sensor"));
    log_println(F(" ... klaar"));
}

int sensor_co2_ppm() {
  int i;
  float v = 0;
 
  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    v += analogRead(CO2_PIN);
    delay(READ_SAMPLE_INTERVAL);
  }
  v = (v / READ_SAMPLE_TIMES) * 5 / 1024 ;

  float volts = v / DC_GAIN;
  if (volts > ZERO_POINT_VOLTAGE || MAX_POINT_VOLTAGE < 0.265 ) {
    return -1;
  } else {
    float *pcurve = CO2Curve;
    return pow(10, (volts - pcurve[1]) / pcurve[2] + pcurve[0]);
    volts = 0;
  }
}
