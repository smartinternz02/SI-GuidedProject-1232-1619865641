 #include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String command;


void callback(char* topic, byte* payload, unsigned int payloadLength);

// CHANGE TO YOUR WIFI CREDENTIALS
const char* ssid = "vivo";//your wifi ssid
const char* password = "Harika@123";//your password

// CHANGE TO YOUR DEVICE CREDENTIALS AS PER IN IBM BLUMIX
#define ORG "tr5m2e"
#define DEVICE_TYPE "ESP32"
#define DEVICE_ID "12345"
#define TOKEN "12345678" //  Authentication Token OF THE DEVICE

//  PIN DECLARATIONS 

#define led1 2
#define led2 0


//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";// cmd  REPRESENT command type AND COMMAND IS TEST OF FORMAT STRING
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;


WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

int publishInterval = 5000; // 30 seconds
long lastPublishMillis;
void control_func();

void setup() {
  
  Serial.begin(115200);
  Serial.println();

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
 
   
  wifiConnect();
  mqttConnect();
}

void loop() {


 if (millis() - lastPublishMillis > publishInterval)
  {
    control_func();
    lastPublishMillis = millis();
  }
  
  if (!client.loop()) {
    mqttConnect();
  }
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected, IP address: "); 
  Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) 
  {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    
    initManagedDevice();
    Serial.println();
  }
}

void initManagedDevice() {
  if (client.subscribe(topic)) {
   
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  
  Serial.print("callback invoked for topic: ");
  Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    
    command+= (char)payload[i];
  }
  
  Serial.print("data: "+ command);
  control_func();
  command= "";
}

void control_func()
{
  
   
  if(command== "lightoff")
 {

         display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 25);
           digitalWrite(led1,LOW);
           digitalWrite(led2,LOW);
          display.print("Light OFF");
          delay(1000);
          Serial.println(".......lights are off..........");
          display.clearDisplay();
          display.display(); 
 
    
  }
  else if(command== "lighton")
  {
     
 display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(3, 25);
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
     Serial.println(".......lights are on..........");
        delay(1000);
          display.clearDisplay();
          display.display(); 
  }

   
  else
  {
    Serial.println("......no commands have been subscribed..........");
   
    }
}
