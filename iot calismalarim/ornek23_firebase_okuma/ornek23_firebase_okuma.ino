// Firebase Realtime Databaseden okuduğumuz sıcaklık verisine göre ledi yakıp söndürme
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//********************************************************
const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "*********";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "*****************************"   // baglanilacak olan firebase host adresi
#define FIREBASE_AUTH "*****************************"  // baglanilacak olan firebase key
//************************************************************
void setup() {
  pinMode(D0,OUTPUT);                   // D0 pinini cikis yap
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
  Serial.println("Wifi agına baglanıyor");
  
  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  Serial.println("Connecting Firebase Realtime Database");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  digitalWrite(D0,LOW);
}
//************************************************************
void loop() 
{
  float sicak=Firebase.getFloat("Sicaklik");
  Serial.print("Okunan Sicaklik Degeri: ");
  Serial.println(sicak);
  if(sicak<24)
  {
    Serial.println("LED yaniyor");
    digitalWrite(D0,HIGH);    // ledi yak
  }
  else
  {
    Serial.println("LED sonuyor");
    digitalWrite(D0,LOW);     // ledi sondur
  }
  delay(5000);
}
