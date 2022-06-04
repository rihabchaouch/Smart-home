#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h> 

#define BLYNK_TEMPLATE_ID "TMPL7nuaewdt"
#define BLYNK_DEVICE_NAME "dhtBlynk"
#define BLYNK_AUTH_TOKEN "JDYDHN-2XFiI70nGVcP7mfjbS289mt0F"


char auth[] = BLYNK_AUTH_TOKEN ; //ta5ou blynk token=id //


#define DHTPIN 2  //Digital pin
#define DHTTYPE DHT11 //define card (or DHT11)
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer; //intanse timer min biblo//


void SendSensor (){   //methode nab3dhou donne les appar//

  float h = dht.readHumidity(); //read humidity
  float t = dht.readTemperature(); //read temperature Celsius
  Serial.println("temp= ");
    Serial.println(t);
    Serial.println("hum= ");
    Serial.println(h);
    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
         }
   Blynk.virtualWrite(V0,h);
   Blynk.virtualWrite(V2,t); // pin virtial
         

 
}


//WiFi carte 
const char *ssid = "RIHAB-CHAOUCH 9930"; //Wifi Name
const char *pass = "3m2t6_16"; //Wifi password



void setup() {
  //Set software serial baud to 115200
  Serial.begin(115200); //ferq de port
  Blynk.begin(auth,ssid,pass);
  dht.begin();
  timer.setInterval(1000l,SendSensor);  // 1 s refrache les donnes//  
}

void loop() {
  Blynk.run();
  timer.run();
}
