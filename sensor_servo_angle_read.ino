#include <Servo.h>

#define MIC_PIN A0

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int amplitude;
int lastAmplitude;
bool forwards = true;
bool backwards = false;
float threshold = 50; 
int angle;
// int soundSourceAngle;
int servoPosition;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  amplitude = analogRead(MIC_PIN);
  threshold = amplitude;
  myservo.read();  
}

void loop() { 
  threshold = threshold + 0.1 * float(amplitude - threshold + 75);
  servoPosition = angle;
  angle = amplitude;

  for (pos = 0; pos <= 180; pos += 1) {
    // take reading from mic
    amplitude = analogRead(MIC_PIN);
    // if statement that checks if our amplitude is about threshold and only records values if it is

  if(amplitude >= threshold) {
    // assign current reading to last reading
    lastAmplitude = amplitude;
  }

}


    // compare readings, switch direction if needed
    if(amplitude < lastAmplitude) {
      forwards = !forwards;
      backwards = !backwards;
    }

    // handle going forwards and backwards
    if(backwards && !forwards) {
      pos = 180 - pos;
      if(pos == 0) { // if we hit zero degrees (the threshold), change direction
        forwards = true;
        backwards = false;
      }
    } 
    else if(forwards && !backwards) {
      if(pos == 180) { // if we hit 180 degrees also change direction
        forwards = false;
        backwards = true;
      }
    }

    // if amplitude is loud enough then record the angle
    if(amplitude > 5) {
      angle = servoPosition;
      Serial.print("sound detected at around ");
      Serial.print(angle);
      Serial.println(" degress");
    }

  // 
  Serial.print("amp= ");
  Serial.print(amplitude);
  Serial.print(",");
  Serial.print("threshold= ");
  Serial.print(threshold);
  Serial.println("");
      // move servo
  myservo.write(pos);
  delay(5);
  }
