
#include <Servo.h>

Servo myservo;
const int trigPin = 9;
const int echoPin = 10;  // Defines Tirg and Echo pins of the Ultrasonic Sensor
int distance;
long duration;
const int LightPin = 8;
int lightint;
int diff;
double ratio;
int corr_anlight2;
int ndiff;
int pos = 90; 
int n;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(9);
  Serial.begin(9600);
  n=0;
}

void loop() {
  myservo.write(pos);
  int anlight1 = analogRead(A0);//white wire
  int anlight2 = analogRead(A1);//green wire
  
  
  diff=anlight1-anlight2;
  ratio=anlight1/anlight2;

  
  if (anlight2>195) {
    corr_anlight2=anlight2*((-0.583*log(anlight2))+5.0732);//multiply input by adjustment ratio
  }
  else {
    corr_anlight2=anlight2*((0.2283*log(anlight2))+0.6937);
  }
  
  ndiff=anlight1-corr_anlight2;

  if (anlight2>800) {
  if (ndiff>200){//if white is dimmer than green, open blinds
    if (n<3){//open limit
      pos=180;
      myservo.write(pos);
      ndiff=0;
      delay(1000);
      n=n+1;
      }
    pos=90;
    myservo.write(pos);
    
  }
  
  else if (ndiff<100){//green is dimmer than white, close blinds
     if (n>0){
      pos=0;
      myservo.write(pos);
      ndiff=0;
      delay(1000);
      n=n-1;
     }
     pos=90;
     myservo.write(pos);
  }
  }
  distance = calculateDistance();
  Serial.print(distance);
  Serial.print(",");   
  Serial.print(anlight1);
  Serial.print(",");
  Serial.print(corr_anlight2);
  Serial.print(",");
  //Serial.print(diff);
  //Serial.print(",");
  //Serial.print(ratio);
  //Serial.print(",");
  Serial.print(ndiff);
  Serial.print(",");
  Serial.print(n);
  Serial.print(",");
  Serial.println();
  delay(500);
}

int calculateDistance()
{ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
