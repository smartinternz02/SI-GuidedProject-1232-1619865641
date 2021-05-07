 #include<Servo.h>
int trigpin=6;
int echopin=9;
int ledpin=13;
Servo motor;
void setup()
{
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  motor.attach(2);
}
void loop()
{
  digitalWrite(trigpin,HIGH);
  delay(1000);
  digitalWrite(trigpin,LOW);
  delay(1000);
  int duration=pulseIn(echopin,HIGH);
  int distance=(duration*0.034)/2;
  Serial.print("distance");
  Serial.println(distance);
  if ((distance>=50)&&(distance<350)){
    motor.write(90);
    Serial.println("angle is 90");
    digitalWrite(ledpin,HIGH);
    delay(1000);
  }
  else
  {
    motor.write(0);
    Serial.print("angle is 0");
    delay(1000);
  digitalWrite(ledpin,LOW);
  }  
}
