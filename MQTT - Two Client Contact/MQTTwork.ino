// This example uses an Arduino/Genuino Zero together with
// a WiFi101 Shield or a MKR1000 to connect to shiftr.io.
//
// IMPORTANT: This example uses the new WiFi101 library.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Gilberto Conti
// https://github.com/256dpi/arduino-mqtt

#include <ESP8266WiFi.h>
#include <MQTT.h>

#define Sicaklik D2
#define Basinc D3
#define Yukseklik D4
//#define onbahce2_sure D3

const char ssid[] = "wifeName";
const char pass[] = "wifePassword";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {   
    Serial.print(".");
    delay(1000);
 
  Serial.print("\nconnecting...");  //shiftr.io sitesinden oluşturduğunuz fieldların isimlerini buraya girmeniz gerekmektedir. Eğer şifreniz yok ise silebilirsiniz.
  while (!client.connect("muratt", "TumSinifKullanabilir", "12345678")) {
    Serial.print(".");
    delay(1000);
  }


  Serial.println("\nconnected!");

//MuratTelefonClienti  İndirdiğiniz Virtuino MQTT programınızda Sicaklık basinc ve yukseklik değerlerini göndermek için sisteme topic olarak abone ettik.
  client.subscribe("Sicaklik");
  client.subscribe("Basinc");
  client.subscribe("Yukseklik");
  
}

int sure;
int Sicaklik;
int Basinc;
int Yukseklik;
bool state;   
void messageReceived(String &topic, String &payload) {   // messageReceived Metodu ile topicleri ve bu topiclerini kontrol ettik. Gelen bilgilere göre işlemlerimizi yaptık.
  if(topic == "Sicaklik")
  {
    Sicaklik = payload.toInt();
    Serial.println("Sicaklik bilgisi Geldi" + Sicaklik);
    }
      if(topic== "Yukseklik"){
          Yukseklik = payload.toInt();
          Serial.println("Yukseklik bilgisi Geldi"+ Yukseklik);
      }
      if(topic == "anahtar"){
            anahtarDurum = payload.toInt();
            state = true;
        }
  Serial.println("incoming: " + topic + " - " + payload);
}
long randNumber;
//Virtual programında bir switch olacak on dediğimiz zaman oku() metodunu çağıracağız of dediğimiz zaman duracak Switch metodunu bir topice atacağız gelen değere göre if ile kontrol edeceğiz.
void oku()
{
  
  sure = sure - 2 ;                                      // Topiclere random değer atadık. Burada sizin göndermek istediğiniz veriler random yerine gerçek verilerde olabilir.
  randSicaklik= random(-50,150);                         // Burada 2 ayrı clienti konuşturarak birbirlerine sıcaklık, basınc ve yukseklik değerlerini gönderdik.
  randBasinc= random(0, 1000);
  randYukseklik= random(0, 100);  
  if(sure >= 0){
      Serial.println(String(randSicaklik));
  digitalWrite(Sicaklik,HIGH);
  Serial.println("Sicaklik atandı");
  client.publish("Sicaklik",String(randSicaklik),true,1);

        Serial.println(String(randBasinc));
  digitalWrite(Basinck,HIGH);
  Serial.println("Sicaklik atandı");
  client.publish("Basinc",String(randBasinc),true,1);

        Serial.println(String(randYukseklik));
  digitalWrite(Yukseklik,HIGH);
  Serial.println("Sicaklik atandı");
  client.publish("Yukseklik",String(randYukseklik),true,1);
  }
  else{
    digitalWrite(Sicaklik,LOW);
    digitalWrite(Basinck,LOW);
    digitalWrite(Yukseklik,LOW);
    Serial.println("Sure Bitti");
  }


}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }
  // publish a message roughly every second.
    
    if (millis() - lastMillis > 1000) { //Oku metodunu burada çağırdık her saniye 2 azaltarak değeri yazdırdık.
    if(anahtarDurum == 1 && state = true){  
    oku();
    lastMillis = millis();
    }
  }
  else if(anahtarDurum == 0 && state = false){
      Serial.println("Anahtar Kapalı");
    }
    else
        Serial.println("Durum saptanamadı");
   

}
