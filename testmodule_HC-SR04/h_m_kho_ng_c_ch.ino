const int trig = 9;     // chân trig của HC-SR04
const int echo = 10;     // chân echo của HC-SR04
 
void setup()
{
Serial.begin(9600);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);

}
 
void loop()
{
unsigned long a;
float d;
digitalWrite(trig,0);
delayMicroseconds(2);
digitalWrite(trig,1);
delayMicroseconds(5);
digitalWrite(trig,0);
a= pulseIn(echo,1);
d= a/2/29.412;
Serial.print(d); Serial.println("cm");
delay(200);
  

}
