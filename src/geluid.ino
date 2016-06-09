#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

//Hoe vaak uit te voeren
#define FFTTIMES 10

#include <FFT.h> // include the library

static int times_index = 0;
static int fft_times = FFTTIMES;
static bool fft_loop = false;

static bool oncetest = true; //TEST
static bool onceprint = true; //TEST

double freq_out[FFTTIMES];
double mag_out[FFTTIMES];

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
}

void loop() {

  //TEST CODE
  if(oncetest) { do_fft_times(); oncetest = false;  }

  if(fft_times >= 0) {
    
      while(fft_loop) { // reduces jitter

        if(fft_times <= 0) { break; }
        
        cli();  // UDRE interrupt slows this way down on arduino1.0
        for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
          while(!(ADCSRA & 0x10)); // wait for adc to be ready
          ADCSRA = 0xf5; // restart adc
          byte m = ADCL; // fetch adc data
          byte j = ADCH;
          int k = (j << 8) | m; // form into an int
          k -= 0x0200; // form into a signed int
          k <<= 6; // form into a 16b signed int
          fft_input[i] = k; // put real data into even bins
          fft_input[i+1] = 0; // set odd bins to 0
        }
        fft_window(); // window the data for better frequency response
        fft_reorder(); // reorder the data before doing the fft
        fft_run(); // process the data in the fft
        fft_mag_log(); // take the output of the fft
        sei();
    
        //Debug FFT magnitude array    
//        for (byte i = 0 ; i < FFT_N/2 ; i++) { 
//          Serial.print(fft_log_out[i]); // send out the data
//          Serial.print(" ");
//        }
//        Serial.println(" ");
    
        double hz_rate = 1440; //SAMPLING RATE ARDUINO UNO!
        double max_mag = -1;
        double max_mag_index = -1;

        //skip eerste 3 magnitudes (artefacts?)
        for (byte i = 3 ; i < FFT_N/2 ; i++) { 
          if(fft_log_out[i] > max_mag) {
            max_mag = fft_log_out[i];
            max_mag_index = i;
          }
        }

        //TEST PRINT
//        Serial.print("magnitude:  "); Serial.print(max_mag); Serial.println("");
//        Serial.print("mag index: "); Serial.print(max_mag_index); Serial.println("");
//        Serial.print("hz_rate: "); Serial.print(hz_rate); Serial.println("");
//        Serial.print("FFT_N: "); Serial.print(FFT_N); Serial.println("");

        mag_out[times_index] = max_mag;
  
        double wave_freq = max_mag_index * hz_rate / FFT_N;
        freq_out[times_index] = wave_freq;

        fft_times--;
        times_index++;
    }

    //TEST PRINT
     if(onceprint) { 
       Serial.println("MAGS");

      for (int i = 0 ; i < sizeof(mag_out)/sizeof(double) ; i++) { 
        Serial.print(mag_out[i]);
        Serial.print(" ");
      }
      Serial.println("\nFREQS");
 
      for (int i = 0 ; i < sizeof(freq_out)/sizeof(double) ; i++) { 
        Serial.print(freq_out[i]);
        Serial.print(" ");
      }
      Serial.println("");


      
      onceprint = false;
    }
  }
}

void do_fft_times() {
  fft_times = FFTTIMES;
  times_index = 0;
  fft_loop = true;
}

float get_peak(int index) {
  return freq_out[index];
}
