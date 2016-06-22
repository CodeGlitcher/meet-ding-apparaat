//50ms = 20hz
//500 ms = 10,000hz
//10,000hz adc snelheid
const int sampleWindow = 50; 
unsigned int sample;

//unsigned int sampleAmount = 0; //max samples
unsigned int sampleCount = 0; //samples count
unsigned long peaksum = 0; //Som van alle peaks

long lastCheck = 0;

//bool bysamples = false;
 
void geluid_loop() 
{ 
  if(millis() - lastCheck > 100) {
    lastCheck = millis();
    geluid_minmax();
  }
}

void geluid_minmax() {
  unsigned long startMillis = millis();  //Window
  unsigned int peakToPeak = 0;   //Min-max peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(GELUID_PIN);
    //min levels
    if (sample > signalMax)
    {
      signalMax = sample; 
    } //max levels
    else if (sample < signalMin)
    {
      signalMin = sample;
    }
  }
  // max - min = piek-piek amplitude
  peakToPeak = signalMax - signalMin;
  peaksum = peaksum + peakToPeak;
  sampleCount++;
}

//Geluid aan de hand van aantal samples
//void geluid_samples_start(unsigned long samples) {
//
//  bysamples = true;
//  sampleAmount = samples; //lees samples
//  sampleCount = 0; //counter
//
//  while(sampleCount < sampleAmount) {
//    geluid_minmax();
//  }
//}

//Geluid aan de hand van aantal millis
//void geluid_millis_start(unsigned long paramillis) {
//  
//  bysamples = false;
//  unsigned long endmillis = millis() + paramillis;
//  sampleCount = 0;
//
//  while(millis() < endmillis) {
//    geluid_minmax();
//  }
//}

//Opvragen gemiddelde peaks
int geluid_avg() {
  unsigned int retVal = peaksum/sampleCount;
  peaksum = 0;
  sampleCount = 0;
  return retVal;
}

//void setSampleWindow(unsigned int window) {
//  sampleWindow = window;
//}


