// Firebase Realtime Database e string ve int verisi yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "*********";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "*****************************"   // baglanilacak olan firebase host adresi
#define FIREBASE_AUTH "*****************************"  // baglanilacak olan firebase key
//************************************************************
void setup() {
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
}
//************************************************************
void loop() 
{
  // set string value
  Firebase.setString("Mesaj", "Bizim icin buyuk bir adim");  // Mesaj etiketine Bizim icin buyuk bir adim yaz
  // handle error
  if (Firebase.failed()) {
      Serial.print("Hata kotu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set value
  Firebase.setInt("Sayi", 42);    // Sayi etiketine 42 yaz
  // handle error
  if (Firebase.failed()) {
      Serial.print("Hata kotu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000); 
}
