#include <WiFi.h>
#include <PubSubClient.h> // to connect to MQTt client in Iot platform
int trigpin=5;
int echopin=4;


float distance;
int    ldr;



const char* ssid = "vivo";//your wifi ssid
const char* password = "Harika@123";//your password

// CHANGE TO YOUR DEVICE CREDENTIALS AS PER IN IBM BLUMIX
#define ORG "tr5m2e"
#define DEVICE_TYPE "ESP32"
#define DEVICE_ID "12345"
#define TOKEN "12345678" // Authentication Token OF THE DEVICE

// PIN DECLARATIONS 



//-------- Customise the above values --------
const char publishTopic[] = "iot-2/evt/Data/fmt/json";
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
//char topic[] = "iot-2/cmd/home/fmt/String";// cmd REPRESENT command type AND COMMAND IS TEST OF FORMAT STRING
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;


WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

int publishInterval = 5000; // 30 seconds
long lastPublishMillis;
void publishData();

void setup() {
  
  Serial.begin(115200);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.println();
  Serial.print("Started");


 
  
  wifiConnect();
  mqttConnect();
}

void loop() {


 if (millis() - lastPublishMillis > publishInterval)
  {
    publishData();
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
    
   
  }
}



void publishData() 
{
 digitalWrite(trigpin,HIGH);
 delay(1000);
 digitalWrite(trigpin,LOW);
//delay(1000);
 int duration=pulseIn(echopin,HIGH);
 distance=duration*0.343/2;  //velocity of air=0.343
 Serial.println("the distance is");
 Serial.print(distance);
 delay(2000);

 int LDRValue=analogRead(32);
   
  Serial.print("ldr value is");
  Serial.print(ldr);
  delay(2000);

  String payload = "{\"d\":{\"distance\":";
  payload += distance;
  payload += ",""\"ldr\":";
  payload += ldr;
  payload += "}}";


  Serial.print("\n");
  Serial.print("Sending payload: "); Serial.println(payload);

  if (client.publish(publishTopic, (char*) payload.c_str())) {
    Serial.println("Publish OK");
  } else {
    Serial.println("Publish FAILED");
  }
}
