#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur

// WiFi
const char *ssid = "RIHAB-CHAOUCH 9930"; // Enter your WiFi name
const char *password = "3m2t6_16";  // Enter WiFi password

// MQTT Broker
//const char *mqtt_broker = "robotn-cloud-server.robotika.systems"; //@ip
#define mqtt_broker "broker.hivemq.com"
 const char *mqtt_username = "robotika";
const char *mqtt_password = "robotika";
 const int mqtt_port = 1883; 


//#define topic_1 "Hello everyone"  //Topic 

WiFiClient espClient; //lib 
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    
  }
  Serial.println();
} 

    
void setup() {
 
// Set software serial baud to 115200;
  Serial.begin(115200);
 Serial.println(F("DHTxx test!"));
 dht.begin();
  
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  

  while (!client.connected()) {
     String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      
      Serial.println("Connected to the public mqtt broke");
     
 
  
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {

 
      float h = dht.readHumidity();
        float t = dht.readTemperature();
       float f = dht.readTemperature(true);

             if (isnan(h) || isnan(t) || isnan(f))
 {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 
 float hif = dht.computeHeatIndex(f, h);
 
 float hic = dht.computeHeatIndex(t, h, false);
 Serial.print("Humidite: ");
 Serial.print(h);
 Serial.print(F("%Temperature: "));
 Serial.print(t);
 Serial.print(F(" °C "));
 Serial.println(f);
 Serial.print(F(" °F head index "));
 Serial.print(hic);
 Serial.println(F(" °C "));
 Serial.print(hif);
 Serial.println(F("°F"));
        
         
          client.publish("temperature_topic",String(t).c_str(), true);
          Serial.println("temperature value  published successfully");
           client.publish("humidity_topic", String(h).c_str(), true);
          Serial.println("humidity value  published successfully");
          
          client.subscribe("temperature_topic");
           client.subscribe("humidity_topic");
        
           
      } 
      else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  };
 
}


void loop() {
  client.loop();

}
