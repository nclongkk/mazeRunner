// Sensors declaration
#define trigPin 4
#define echoPin 8
#define trigPinr 6
#define echoPinr 7
#define trigPinl 2
#define echoPinl 13
// Sensors declaration
#define ENB 3
#define IN4 12
#define IN3 11
#define IN2 10
#define IN1 9
#define ENA 5

// Misc declaration
long buzz_distance = 15; //đơn vị cm 
const int speed = 100; //tốc độ:  0-255

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPinr, OUTPUT);
  pinMode(echoPinr, INPUT);
  pinMode(trigPinl, OUTPUT);
  pinMode(echoPinl, INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(9600);
}

//Clusters
void Motor(bool a1, bool a2, bool a3, bool a4)  {
  analogWrite(ENA,speed);
  digitalWrite(IN1,a1);
  digitalWrite(IN2,a2);
  digitalWrite(IN3,a3);
  digitalWrite(IN4,a4);
  analogWrite(ENB,speed);
}
void MotorAB (bool a1, bool a2,  int speedA, bool a3, bool a4, int speedB) {
  analogWrite(ENA,speedA);
  digitalWrite(IN1,a1);
  digitalWrite(IN2,a2);
  digitalWrite(IN3,a3);
  digitalWrite(IN4,a4);
  analogWrite(ENB,speedB);
}

void right() {
  Motor(1,0,0,0);
  Serial.print("Right Speed:");
  Serial.println(speed);
  }


void left() {
  Motor(0,0,0,1);
  Serial.print("Left Speed:");
  Serial.println(speed);
  }


void forward() {
  MotorAB(1,0,140, 1,0, 100);
  Serial.print("Forward Speed:");
  Serial.println(speed);
  }


int search_forward() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance= duration*0.034/2;
  Serial.println(distance);
  return distance;
  }

int search_left() {
  digitalWrite(trigPinl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinl, LOW);
  int duration = pulseIn(echoPinl, HIGH);
  int distance= duration*0.034/2;
  Serial.println(distance);
  return distance;
  }

int search_right() {
  digitalWrite(trigPinr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinr, LOW);
  int duration = pulseIn(echoPinr, HIGH);
  int distance= duration*0.034/2;
  Serial.println(distance);
  return distance;
}
void tilt_left() {
  MotorAB(1, 0, speed - 10, 1, 0, speed);
}

void tilt_right() {
  MotorAB(1, 0, speed, 1, 0, speed - 10);
}

//Main
void loop() {
  search_forward();
  search_left();
  search_right();
  forward();
  //Balancing
//  while (search_left() != search_right()) {
//  Serial.println("Balance");
//
//  if (search_left() > search_right() + 5 && search_left() < buzz_distance)
//  {
//      Serial.println("Balance Left");
//
//    tilt_left();
//    search_left();
//    search_right();
//  }
//  if (search_right() > search_left() + 5 && search_right() < buzz_distance)
//  {
//          Serial.println("Balance Right");
//
//    tilt_right();
//    search_left();
//    search_right();
//  }  
// }
//Locating
if (search_left() > buzz_distance) {
    Serial.println("Left");

forward();
delay(170);
while (search_left() > buzz_distance && search_right() < buzz_distance || search_forward() < buzz_distance) {
  MotorAB(0,1,100,1,0,100);
  delay(100);
  search_left();
  search_right();
  }
}
if (search_right() > buzz_distance){
  Serial.println("Right");
forward();
delay(170);
while (search_right() > buzz_distance && search_left() < buzz_distance || search_forward() < buzz_distance) {
MotorAB(1,0,100,0,1,100);
  delay(100);
  search_left();
  search_right();
  }
}
//Must be the last
while (search_right() == search_left()) {
  Serial.println("Forward");
    forward();
    search_left();
    search_right();
  }


}
