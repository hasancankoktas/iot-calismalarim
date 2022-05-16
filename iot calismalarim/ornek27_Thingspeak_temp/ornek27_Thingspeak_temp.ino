// ESP modulu Thingspeak.com sitesine sıcaklik gönderecek
#include <ESP8266WiFi.h>
#include "ThingSpeak.h" 
#include <dht11.h>          // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN D1         // DHT11PIN olarak Dijital 1'yi belirliyoruz.
//************************************************************
const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "*********";      // baglanilacak olan wifi aginin sifresi

#define SECRET_CH_ID xxxxx            // Secret channel ID si
const char *SECRET_WRITE_APIKEY = "xxxxxxxxxxxxxxxxx";  // write api key

float sicaklik=0.0, nem=0.0;

dht11 DHT11;                    // DHT11 nesnesi olusturuluyor

WiFiClient  wifi_istemci;
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

  ThingSpeak.begin(wifi_istemci);  // Initialize ThingSpeak
}
//************************************************************
void loop() 
{
 sicaklik_olc();               // sicakligi olc
 int x = ThingSpeak.writeField(SECRET_CH_ID, 1, sicaklik, SECRET_WRITE_APIKEY);    // alan 1 e sicaklik yaz
  if(x == 200)
    Serial.println("Kanala veri yazildi!");
  else
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
    delay(18000);     // thingspeak sitesi 15sn de bir güncelleme yapıyor o yüzden 18sn bekle
  x = ThingSpeak.writeField(SECRET_CH_ID, 2, nem, SECRET_WRITE_APIKEY);    // alan 2 e sicaklik yaz
  if(x == 200)
    Serial.println("Kanala veri yazildi!");
  else
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));

  delay(18000);     // thingspeak sitesi 15sn de bir güncelleme yapıyor o yüzden 18sn bekle
}
//**************** sicaklik olcumu ********************
void sicaklik_olc()
{
  DHT11.read(DHT11PIN);       // sicaklik sensorunu oku
  sicaklik=DHT11.temperature; // sicaklik degerini sicaklik degiskenine ata
  nem=DHT11.humidity;         // nem degerini nem degiskenine ata
  delay(200);                 // 200ms bekle
}
