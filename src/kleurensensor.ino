#include <TimerOne.h>
#include <ColorRecognition.h>
#include <ColorRecognitionTCS230.h>

ColorRecognitionTCS230* tcs230 = ColorRecognitionTCS230::getInstance();

void setup() {
  Serial.begin(9600);
 
  tcs230->initialize(2, 3, 4);

  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(8, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  
  Serial.print("Adjusting the white balance... show something white to the sensor.");
  // Show something white to it during 4 seconds.
  tcs230->adjustWhiteBalance();
}

void loop() 
{ 
    Serial.print("Red: ");
    Serial.println(tcs230->getRed());
    Serial.print("Green: ");
    Serial.println(tcs230->getGreen()); 
    Serial.print("Blue ");
    Serial.println(tcs230->getBlue());
    
    int R = tcs230->getRed();
    int G = tcs230->getGreen();
    int B = tcs230->getBlue();
    Serial.print("Kleurwarmte: ");
    Serial.println(berekenKleurwarmte(R, G, B));
    Serial.println("K");
    delay(1000); 
}

double berekenKleurwarmte(int R, int G, int B)
{
  double X = (-0.14282)*(R) + (1.54924)*(G) + (-0.95641)*(B);
  double Y = (-0.32466)*(R) + (1.57837)*(G) + (-0.73191)*(B);
  Serial.print("Lichtsterkte (Lux): ");
  Serial.println(Y);
  double Z = (-0.68202)*(R) + (0.77073)*(G) + (0.56332)*(B);

  double x = X/(X + Y + Z);
  double y = Y/(X + Y + Z);

  double n = (x - 0.3320)/(0.1858 - y);
  Serial.print("n: ");
  Serial.println(n);

  double CCT = 449*pow(n,3) + 3525*sq(n) + 6823.3*n + 5520.33;
  return CCT;
}
