const int sampleWindow = 500; //50ms = 20hz, 500ms = 10,000hz
unsigned int sample;

unsigned long startMillis = 0;  //Window
unsigned int peakToPeak = 0;   //Min-max peak level
unsigned int signalMax = 0;
unsigned int signalMin = 1024;

bool geluidSample = false;
int sampleAmount = 0; //lees samples
int sampleCount = 0; //counter

//Som van alle peaks
int peaksum = 0;

void geluid_setup() 
{
}
 
void geluid_loop() 
{ 
  sampleCount = sampleCount + 1;
  if(geluidSample && sampleCount > sampleAmount) {
    geluidSample = false;
  }
  
  if(geluidSample && sampleCount < sampleAmount ) {
    geluid_minmax();
  }
}

private geluid_minmax() {
   startMillis = millis();
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

public geluid_start(long samples) {
  sampleAmount = samples;
  geluidSample = true;
}

//Opvragen gemiddelde peaks
int geluid_avg() {
  return peaksum / sampleAmount;
}


