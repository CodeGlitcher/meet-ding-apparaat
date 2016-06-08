#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#define FFTTIMES 5
//aantal peaks == ftttimes

#include <FFT.h> // include the library

static int times_index = 0;
static int fft_times = FFTTIMES;
static bool fft_loop = false;

static bool oncetest = true;
static bool onceprint = true;

float freq_peaks[FFTTIMES];

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
    
//        Debug FFT magnitude array    
//        for (byte i = 0 ; i < FFT_N/2 ; i++) { 
//          Serial.println(fft_log_out[i]); // send out the data
//        }
    
        float freq_array[FFT_N/2];
        float hz_rate = 1440; //SAMPLING RATE ARDUINO UNO!
        float max_freq = 0;
        
        //Magnitudes to frequencies
        for (byte i = 0 ; i < FFT_N/2 ; i++) { 
          
          freq_array[i] = fft_log_out[i] * hz_rate / FFT_N;
          
          if(freq_array[i] > max_freq) {
            //filter first two (artefacts?)
            if(i >= 2) { max_freq = freq_array[i]; }
          }
          
          Serial.print(freq_array[i]); 
          Serial.print(" ");
        }

        Serial.println("");
//        Serial.print("MAX FREQ: ");
//        Serial.print(max_freq); Serial.println(" ");

        freq_peaks[times_index] = max_freq;
        
//        Serial.println("");
//        Serial.print(fft_times);
//        Serial.println("");
//        freq_peaks[fft_times] = freq_array[1];

        fft_times--;
        times_index++;
    }

     if(onceprint) { 
       Serial.print("PRINT THING ");
       
      for (int i = 0 ; i < sizeof(freq_peaks)/sizeof(float) ; i++) { 
        Serial.print(freq_peaks[i]);
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
  return freq_peaks[index];
}




