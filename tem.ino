#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
 
void setup()
{
 Serial.begin(115200);
 Serial.println(F("DHTxx test!"));
 dht.begin();
}
void loop()
{
 delay(2000);
 
 
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
 

//Affichage// 
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

}
