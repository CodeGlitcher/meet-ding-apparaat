// Deze module regelt de interactie met de geluidssensor
// gld -> geluid

// Constanten
const int sampleWindow = 50;

// Variabelen
unsigned int sample;
unsigned int sampleCount = 0; //samples count
unsigned long peaksum = 0; //Som van alle peaks

long lastCheck = 0;

// Voer geluid_minmax() elke 10e van een seconde uit
void gld_loop() 
{ 
  if(millis() - lastCheck > 100) {
    lastCheck = millis();
    gld_minMax();
  }
}

// Bereken de laagste en hoogste waarde die er te horen zijn
// binnen de sample windows
void gld_minMax() {
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

//Opvragen gemiddelde peaks
int gld_avg() {
  unsigned int retVal = peaksum/sampleCount;
  peaksum = 0;
  sampleCount = 0;
  return retVal;
}


