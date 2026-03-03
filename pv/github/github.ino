#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>


// WiFi Ayarları
const char *ssid = "PROVANCE";
const char *password = "Provance!2025";

// GitHub'daki .bin dosyasının RAW linki
// Örnek:
// "https://raw.githubusercontent.com/kullaniciAdi/repoAdi/main/firmware.bin"
const char *firmware_url = "https://raw.githubusercontent.com/kadirmercan00/pv/main/pv/UP001/UP001.bin";

// Mevcut versiyon bilgisi (Güncelleme kontrolü için)
String current_version = "1.0.0";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("\n--- ESP32 GitHub OTA Ornegi ---");
  Serial.println("Mevcut Versiyon: " + current_version);

  // WiFi'ye bağlan
  WiFi.begin(ssid, password);
  Serial.print("WiFi'ye baglaniyor");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nBaglandi!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());

  // Güncellemeyi başlat
  checkForUpdates();
}

void loop() {
  // OTA işlemi genelde setup'ta veya özel bir komut geldiğinde yapılır
  // Burada boş bırakıyoruz.
}

void checkForUpdates() {
  Serial.println("GitHub'dan guncelleme kontrol ediliyor: " +
                 String(firmware_url));

  // HTTPS bağlantısı için güvenli istemci oluştur
  WiFiClientSecure client;

  // DİKKAT: GitHub sertifikası zamanla değişebileceği için veya
  // hafıza dostu olması adına sertifika doğrulamasını atlıyoruz (Insecure).
  // Gerçek prodüksiyon ortamlarında GitHub root CA sertifikasını
  // (client.setCACert) kullanmanız önerilir.
  client.setInsecure();

  // HTTPUpdate kütüphanesini kullanarak güncellemeyi başlat
  // Bu işlem dosyayı indirecek ve flash belleğe yazacaktır.
  t_httpUpdate_return ret = httpUpdate.update(client, firmware_url);

  switch (ret) {
  case HTTP_UPDATE_FAILED:
    Serial.printf("Guncelleme Basarisiz. Hata: (%d): %s\n",
                  httpUpdate.getLastError(),
                  httpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    Serial.println("Yeni guncelleme yok.");
    break;

  case HTTP_UPDATE_OK:
    Serial.println(
        "Guncelleme basariyla tamamlandi! ESP32 yeniden baslatiliyor...");
    // Not: HTTP_UPDATE_OK döndüğünde ESP genellikle otomatik olarak yeniden
    // başlar Kütüphane otomatik restart'ı sağladığı için bu satır print
    // edilmeyebilir.
    break;
  }
}
