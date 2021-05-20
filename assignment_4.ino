 #include "BluetoothSerial.h"
BluetoothSerial SerialBT;

int a=1;
int b=0;
int motor=3;  //LED
char BTvalue =0;
int trigpin=4;
int echopin=5;


void setup() {
  
   pinMode(motor, OUTPUT);
   Serial.begin(115200);
   pinMode(trigpin,OUTPUT);
   pinMode(echopin,INPUT);
   delay(1000);
    Serial.println("data");
   SerialBT.begin("ESP32test"); //Bluetooth device name
   Serial.println("The device has started, now you can pair it with bluetooth!");
   
}

void loop() {
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }
  if(SerialBT.available()){
    SerialBT.write(SerialBT.read());
  }
 
 digitalWrite(trigpin,HIGH);
 delay(1000);
 digitalWrite(trigpin,LOW);
int duration=pulseIn(echopin,HIGH);
int distance=duration*0.343/2;  //velocity of air=0.343
 Serial.println("distance is equal to ");
 Serial.print(distance);
 char value=a;
     if(SerialBT.available()==a){  
       value=SerialBT.read();
     
 if(distance<250)
 {
SerialBT.println("water level");
 SerialBT.print(distance);
 delay(1000);
     
   SerialBT.println("Tank  is Filled completly ");
   delay(1000);
      SerialBT.println("motor should be switched off ");
    delay(1000);
 }
 
  else if(distance>=250)
 {
   SerialBT.println("water level ");
 SerialBT.print(distance);
 delay(2000);
     
 
  SerialBT.println("tank is unfilled");
  delay(1000);
  SerialBT.println("motor should be switched on ");
  delay(1000);
     
}
     }
     if(SerialBT.available()>b){
       BTvalue=SerialBT.read();
     }
        if(BTvalue=='a'){
          digitalWrite(motor,HIGH);
      }
    else if(BTvalue=='b'){
      digitalWrite(motor,LOW);
      }

}
