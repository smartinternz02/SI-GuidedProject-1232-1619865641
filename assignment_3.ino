  #include "DHT.h"
#define DHTPIN 4  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int temp ;
int humidity;
void setup() {
 Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
dht.begin();
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  pinMode(13,OUTPUT);//light
  pinMode(4, OUTPUT);//light
  pinMode(21,OUTPUT);//fan
  Serial.begin(9600);
}
void loop() 
{
// put your main code here, to run repeatedly:
  int ldr=analogRead(15);
  display.clearDisplay();
  display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
Serial.print("the intensity is");
Serial.println(ldr);
display.print("the intensity is");
display.println(ldr);
display.clearDisplay();
display.display();
delay(1000);
display.clearDisplay();
display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
if(ldr>4000)
{
digitalWrite(13, LOW);  
  delay(1000);                      
  digitalWrite(4, LOW);   
  delay(1000);  
   digitalWrite(21, LOW);
   Serial.println("bright");
   display.println("bright");
   display.clearDisplay();
   display.display();   
  delay(1000); 
} 
  else if(ldr>1000 && ldr<2000)
  {                    
  digitalWrite(13, HIGH);    
  delay(1000);                       
  digitalWrite(4, HIGH);
  digitalWrite(21, HIGH);
   Serial.println("Moderately bright");
   display.println("Moderately bright");
   display.clearDisplay();
   display.display();
  delay(1000); 
}
else 
{
  digitalWrite(13, HIGH);    
  delay(1000);                       
  digitalWrite(4, HIGH);
  digitalWrite(21, HIGH);
   Serial.println("dark"); 
   display.println("dark"); 
   display.clearDisplay();
   display.display();  
  delay(1000); 
}
display.clearDisplay();
display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
   delay(2000);
 float h = dht.readHumidity();
  float t = dht.readTemperature();
 float f = dht.readTemperature(true);
 if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
 float hif = dht.computeHeatIndex(f, h);
 float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
if(temp>=50 && humidity>=80)
{
display.print("temp is high =");
display.println(t);
display.clearDisplay();
display.display();
digitalWrite(21,HIGH);
delay(1000);
}
else if(temp<10 && humidity<5)
{
display.print("temp is low =");
display.println(t);
display.clearDisplay();
display.display();
digitalWrite(21,LOW);
delay(1000);
}
else{
  display.print("temp is moderate =");
display.println(t);
display.clearDisplay();
display.display();
digitalWrite(21,HIGH);
delay(1000);
}
}
