#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>  // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN D2 // DHT11PIN olarak Dijital 2'yi belirliyoruz.

dht11 DHT11;        // DHT11 nesnesini olusturuyoruz

char auth[] = "lnffYD1NyfjRC-7ZVWNrIG9weqAFBpWa";
char ssid[] = "xxxxxxxxxxxx";   // baglanilacak olan wifi aginin adi  
char pass[] = "xxxxxxxxxxxx";   // baglanilacak olan wifi aginin sifresi

//************************************************************
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
//************************************************************
void loop()
{
  Blynk.run();
  delay(2000);
  DHT11.read(DHT11PIN);   // sensoru oku
  Blynk.virtualWrite(V2, DHT11.temperature);
  Blynk.virtualWrite(V3, DHT11.humidity);
}
