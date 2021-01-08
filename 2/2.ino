
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
//const int speed = 150; 
void setup()
{
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

//ham dieu khien dong co 
void Motor(bool a1, bool a2, bool a3, bool a4,int speed)  {
  analogWrite(ENA,speed);
  digitalWrite(IN1,a1);
  digitalWrite(IN2,a2);
  digitalWrite(IN3,a3);
  digitalWrite(IN4,a4);
  analogWrite(ENB,speed);
}
//ham khoang cach doi so la trig echo
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

 
void loop()
{
  int distanceFront = distance(trigfront,echofront);
  int distanceLeft = distance(trigleft,echoleft);
  int distanceRight = distance(trigright,echoright);
  
Serial.print(distanceFront); Serial.print("cm     ");
Serial.print(distanceLeft); Serial.print("cm     ");
Serial.print(distanceRight); Serial.println("cm     ");
  int time = 500;
  if ( distanceFront > 9){
  Motor(1,0,1,0,speed);
  }
  else {
    if (distanceLeft > 9){
      Motor(0,1,1,0,speed);
      delay(time);
    }
    else {
      if (distanceRight > 9){
        Motor(1,0,0,1,speed);
        delay(time);
        }
      else {
        Motor(1,0,0,1,1);
        delay(2*time);
        }
    }
      
  }

  

}
