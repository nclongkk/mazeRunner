
#define ENA 5
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 7
#define ENB 6
const int trigfront = 9;     // chân trig của HC-SR04
const int echofront = 10;     // chân echo của HC-SR04
const int trigleft = 13;     // chân trig của HC-SR04
const int echoleft = 8;     // chân echo của HC-SR04
const int trigright = 12;     // chân trig của HC-SR04
const int echoright = 11;     // chân echo của HC-SR04


 float distanceFront
 float distanceLeft
 float distanceRight
void setup() {
 Serial.begin(9600);
pinMode(trigfront,OUTPUT);
pinMode(echofront,INPUT);
pinMode(trigleft,OUTPUT);
pinMode(echoleft,INPUT);
pinMode(trigright,OUTPUT);
pinMode(echoright,INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void Motor(bool a1, bool a2,speedl, bool a3, bool a4,int speedr)  {
  analogWrite(ENA,speedl);
  digitalWrite(IN1,a1);
  digitalWrite(IN2,a2);
  digitalWrite(IN3,a3);
  digitalWrite(IN4,a4);
  analogWrite(ENB,speedr);
}

float distance (int trig, int echo){
  unsigned long a;
float d;
digitalWrite(trig,0);
delayMicroseconds(2);
digitalWrite(trig,1);
delayMicroseconds(5);
digitalWrite(trig,0);
a= pulseIn(echo,1);
d= a/2/29.412;
return d;
}
void Quayphai(){
  Motor(1,0,100,0,1,100);
  delay(100); // phai test
  }

void Bamtrai(){
    int out;
    float kp=1;
    const float d = 8;
    out  = kp*(d - distanceLeft);
    speedmean = 100;
    Motor(1,0,speedmean - out,1,0,speedmean + out);
  }
void loop() {
  distanceFront = distance(trigfront,echofront);
  distanceLeft = distance(trigleft,echoleft);
  distanceRight = distance(trigright,echoright);

 if (distanceFront < 9){
  Quayphai();
 }
  Bamtrai();
 
 

}
