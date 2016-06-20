//50ms = 20hz
//500 ms = 10,000hz
//10,000hz adc snelheid
const int sampleWindow = 10000; 
unsigned int sample;

//Som van alle peaks
int peaksum = 0;

void geluid_setup() 
{
}
 
void geluid_loop() 
{ 
}

private geluid_minmax() {
  unsigned long startMillis = millis();  //Window
  unsigned int peakToPeak = 0;   //Min-max peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(GELUID_PIN);
      if (sample < 1024) //filter
      {
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
   }
   // max - min = piek-piek amplitude
   peakToPeak = signalMax - signalMin;
   peaksum = peaksum + peakToPeak;
}

//Geluid aan de hand van aantal samples
public geluid_samples_start(long samples) {

  int sampleAmount = samples; //lees samples
  int sampleCount = 0; //counter

  while(sampleCount < sampleAmount) {
    geluid_minmax();
    sampleCount++;
  }
}

//Geluid aan de hand van aantal millis
public geluid_millis_start(long paramillis) {

  long endmillis = millis() + paramillis;

  while(millis() < endmillis) {
    geluid_minmax();
  }
}

//Opvragen gemiddelde peaks
int geluid_avg() {
  return peaksum / sampleAmount;
}


