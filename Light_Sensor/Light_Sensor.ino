
#include <Servo.h>

Servo myservo;
const int LightPin = 8;
int lightint;
int diff;
double ratio;
int corr_anlight2;
int ndiff;
int pos = 0; 
int n;


void setup() {
  // put your setup code here, to run once:
  //pinMode(LightPin1, INPUT); // Sets the LightPin as an Input
  //pinMode(LightPin2, INPUT); // Sets the LightPin as an Input
  myservo.attach(9);
  Serial.begin(9600);
}
void loop() {
    // put your main code here, to run repeatedly:
  
  int anlight1 = analogRead(A0);
  int anlight2 = analogRead(A1);
  n=0;
  
  diff=anlight1-anlight2;
  ratio=anlight1/anlight2;
  
  if (anlight2>195) {
    corr_anlight2=anlight2*((-0.583*log(anlight2))+5.0732);//multiply input by adjustment ratio
  }
  else {
    corr_anlight2=anlight2*((-0.2283*log(anlight2))+0.6937);
  }
  
  ndiff= anlight1-corr_anlight2;
  
  if (ndiff>100){
    if (n<3){
      pos=180;
      myservo.write(pos);
      delay(1000);
      n=n+1;
    }
    pos=90;
    myservo.write(pos);
  }
  Serial.print(anlight1);
  Serial.print(",");
   /*Serial.print(anlight2);
  Serial.print(",");
  Serial.print(corr_anlight2);
  Serial.print(",");
  Serial.print(diff);
  Serial.print(",");
  Serial.print(ratio);
  Serial.print(",");
  Serial.print(ndiff);
  Serial.print(",");
  Serial.println();
  delay(300);*/
}
