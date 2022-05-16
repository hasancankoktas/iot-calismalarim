#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "lnffYD1NyfjRC-7ZVWNrIG9weqAFBpWa";
char ssid[] = "xxxxxxxxxxxx";   // baglanilacak olan wifi aginin adi  
char pass[] = "xxxxxxxxxxxx";   // baglanilacak olan wifi aginin sifresi
//************************************************************
void setup()
{
  pinMode(D1,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(D1,LOW);
}
//************************************************************
void loop()
{
  Blynk.run();
}
