
#define ENA 5
#define IN2 2
#define IN1 3
#define IN4 4
#define IN3 7
#define ENB 6
const int trigfront = 9;     // chân trig của HC-SR04
const int echofront = 10;     // chân echo của HC-SR04
const int trigright = 13;     // chân trig của HC-SR04
const int echoright = 8;     // chân echo của HC-SR04
const int trigleft = 12;     // chân trig của HC-SR04
const int echoleft = 11;     // chân echo của HC-SR04


 float distanceFront;
 float distanceLeft;
 float distanceRight;
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

void Motor(bool a1, bool a2, int speedl, bool a3, bool a4,int speedr)  {
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
  delay(500); // phai test de chinh 
  }

void Quaytrai(){
  Motor(0,1,100,1,0,100);
  delay(500);
  }
void Bamtrai(){
    int out;
    float k=2;
    float d = 8;
    out  = k*(d - distanceLeft);
    int speedmean = 100;
    int speedleft = speedmean +out;
    int speedright = speedmean - out;
    
    if (speedleft >255) speedleft  = 255;
    if (speedleft <0) speedleft = 0;
    if (speedright >255) speedright = 255;
    if (speedright <0)  speedright = 0;
    Motor(1,0,speedleft,1,0,speedright);
    
  }

void Bamphai(){
    int out;
    float k=4;
    float d = 6;
    out  = k*(d - distanceRight);
    int speedmean = 130;
    int speedleft = speedmean -out;
    int speedright = speedmean + out;
    
    if (speedleft >255) speedleft  = 255;
    if (speedleft <0) speedleft = 0;
    if (speedright >255) speedright = 255;
    if (speedright <0)  speedright = 0;
    Motor(1,0,speedleft,1,0,speedright);
    
  }
int count = 0;
void loop() {
  distanceFront = distance(trigfront,echofront);
//  distanceLeft = distance(trigleft,echoleft);
  distanceRight = distance(trigright,echoright);
  Serial.println(distanceRight);
 if (distanceFront < 9){
  if (count != 0)  Quayphai();
 }
 count++;
  Bamphai();
 
//Motor(1,0,0,1,0,100);

}
