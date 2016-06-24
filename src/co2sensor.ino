#define DC_GAIN (8.5)
#define READ_SAMPLE_TIMES (10)
#define READ_SAMPLE_INTERVAL (50)
#define ZERO_POINT_X (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define ZERO_POINT_VOLTAGE (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define MAX_POINT_VOLTAGE (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define REACTION_VOLTAGE (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

float CO2Curve[3] = {ZERO_POINT_X, ZERO_POINT_VOLTAGE, (REACTION_VOLTAGE / (2.602 - 4))};
int percentage;
int prevppm;

void sensor_co2_init() {
  Serial.print("Co2(MG-811) Init\n");
}

void sensor_co2_loop() {

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
    if(prevppm < 1000) {
      return 400;
    }
    else {
      return 9999;    
    }
  } else {
    float *pcurve = CO2Curve;
    int ppm = pow(10, (volts - pcurve[1]) / pcurve[2] + pcurve[0]);
    prevppm = ppm;
    volts = 0;
    return ppm;
  }
}


 
