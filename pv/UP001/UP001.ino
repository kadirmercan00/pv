// AUTOMATICALLY GENERATED MONOLITHIC SKETCH

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include <Fonts/FreeSans9pt7b.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <NimBLEDevice.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <deque>
#include <time.h>
#include <vector>

// >>> FILE: include/features.h >>>

#define FEATURE_DISPLAY 1   // 0=ekransÄ±z, 1=TFT ekranlÄ±
#define FEATURE_BUTTONS 1   // 0=butonsuz, 1=4 buton
#define FEATURE_VIBRATION 1 // 0=yok, 1=titreÅŸim motoru

#define FEATURE_BLE 1       // BLE beacon tarama
#define FEATURE_MQTT_AWS 0  // AWS IoT MQTT (TLS)
#define FEATURE_MQTT_PROV 1 // PROVANCE MQTT (plaintext)
#define FEATURE_OTA 0       // HTTPS OTA gÃ¼ncellemeleri
#define FEATURE_NTP 1       // NTP zaman senkronizasyonu

// "TR" veya "EN"
#define DEVICE_LANG "EN"

#define DEBUG_SERIAL 1       // Serial debug Ã§Ä±ktÄ±sÄ±
#define DEBUG_PAYLOADS 1     // MQTT payload loglarÄ±
#define DEBUG_STATUS_MS 5000 // Status log aralÄ±ÄŸÄ± (ms)

// <<< FILE: include/features.h <<<

// >>> FILE: src/config/config.h >>>

#define CARD_ID "UP001"
#define DEVICE_TYPE "cardv1"
#define FW_VERSION "2.1.0"

#define CUSTOMER_ID "ECE_TR"
#define SITE_ID "ece_mall_01"
#define MODULE_NAME "prostaff"

#define THINGNAME                                                              \
  "pv-" CUSTOMER_ID "-" SITE_ID "-" MODULE_NAME "-" DEVICE_TYPE "-" CARD_ID

#define WIFI_SSID_DEFAULT "Executive Office"
#define WIFI_PASS_DEFAULT "H!ghTr44"

#define PROV_MQTT_SERVER "91.191.173.28"
#define PROV_MQTT_PORT 1883
#define PROV_MQTT_USER ""
#define PROV_MQTT_PASS ""

#define PROV_DEVICE_GROUP "{BACFE55B-367A-4C1B-94AC-4352DA401E5E}"
#define PROV_DEVICE_ID CARD_ID // Use main CARD_ID

#define PROV_TOPIC_PREFIX "PROVANCE"
#define PROV_TOPIC "PROVANCE" // Main topic for publishing
#define PROV_TOPIC_TASK "TASK"

// LED (WS2812B)
#define LED_DATA_PIN 27
#define LED_NUM_LEDS 2
#define LED_BRIGHTNESS 30

// TFT Display (ST7735)
#define TFT_CS 5
#define TFT_RST 17
#define TFT_DC 16
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_POWER 4

// TFT Display Settings
#define TFT_WIDTH 160
#define TFT_HEIGHT 128
#define TFT_HEADER_HEIGHT 15
#define TFT_LINE_HEIGHT 15
#define TFT_MARGIN 4
#define TFT_BACKGROUND 0x0000   // BLACK
#define TFT_HEADER_COLOR 0x001F // BLUE
#define TFT_TASK_COLOR 0xFFFF   // WHITE
#define TFT_ACCEPT_COLOR 0x001F // BLUE
#define TFT_REJECT_COLOR 0xF800 // RED
#define TFT_FONT_SMALL 1
#define TFT_FONT_MEDIUM 2

// Buttons
#define BTN_ACCEPT 22
#define BTN_REJECT 26
#define BTN_UP 21
#define BTN_DOWN 19

// Vibration
#define VIBRATION_PIN 15

// Battery
#define BATTERY_PIN 34

#define BLE_SCAN_SECONDS 1
#define BLE_SCAN_INTERVAL 100 // ms
#define BLE_RSSI_MIN -85
#define BLE_UUID_PREFIX "00000000-0000-0000-0000"
#define MQTT_RECONNECT_MS 5000
#define WIFI_RETRY_MS 10000

// <<< FILE: src/config/config.h <<<

// >>> FILE: src/core/debug.h >>>

// DEBUG MACROS

#if DEBUG_SERIAL
#define DPRINT(x) Serial.print(x)
#define DPRINTLN(x) Serial.println(x)
#define DPRINTF(...) Serial.printf(__VA_ARGS__)
#else
#define DPRINT(x)
#define DPRINTLN(x)
#define DPRINTF(...)
#endif

// Section-based debug macros
#define LOG_BOOT(...) DPRINTF("[BOOT] " __VA_ARGS__)
#define LOG_WIFI(...) DPRINTF("[WIFI] " __VA_ARGS__)
#define LOG_MQTT(...) DPRINTF("[MQTT] " __VA_ARGS__)
#define LOG_BLE(...) DPRINTF("[BLE] " __VA_ARGS__)
#define LOG_OTA(...) DPRINTF("[OTA] " __VA_ARGS__)
#define LOG_LED(...) DPRINTF("[LED] " __VA_ARGS__)
#define LOG_TIME(...) DPRINTF("[TIME] " __VA_ARGS__)

// <<< FILE: src/core/debug.h <<<

// >>> FILE: include/lang/lang.h >>>

// LANGUAGE SYSTEM - Multi-language string interface

enum class StringID {
  // Header
  ID_PREFIX,

  // Main Screen
  NO_ACTIVE_TASK,

  // Task Screen
  LOCATION,
  SUB_SERVICE,
  STR_DEVICE_TYPE,

  // Actions
  ACCEPTED,
  TASK_REJECTED,
  TASK_COMPLETED,

  // Errors
  WRONG_LOCATION,
  GO_TO_CORRECT,
  LOCATION_DOT,
  WEAK_SIGNAL,
  RSSI,
  REQUIRED,
  GET_CLOSER,
  SYSTEM_ERROR
};

class Language {
public:
  virtual const char *getText(StringID id) = 0;
  virtual ~Language() {}
};

// Global language pointer (set in main.cpp based on FEATURE_LANG)
extern Language *currentLang;

// <<< FILE: include/lang/lang.h <<<

// >>> FILE: include/lang/lang_en.h >>>

class EnglishLanguage : public Language {
public:
  const char *getText(StringID id) override {
    switch (id) {
    case StringID::ID_PREFIX:
      return "Id: ";
    case StringID::NO_ACTIVE_TASK:
      return "No Active Task";
    case StringID::LOCATION:
      return "Location: ";
    case StringID::SUB_SERVICE:
      return "Sub Service: ";
    case StringID::STR_DEVICE_TYPE:
      return "Device: ";
    case StringID::ACCEPTED:
      return "Accepted";
    case StringID::TASK_REJECTED:
      return "Task Rejected";
    case StringID::TASK_COMPLETED:
      return "Completed";
    case StringID::WRONG_LOCATION:
      return "Wrong Location!";
    case StringID::GO_TO_CORRECT:
      return "Go to Correct";
    case StringID::LOCATION_DOT:
      return "Location...";
    case StringID::WEAK_SIGNAL:
      return "Weak Signal!";
    case StringID::RSSI:
      return "RSSI: ";
    case StringID::REQUIRED:
      return "Required: >";
    case StringID::GET_CLOSER:
      return "Get Closer!";
    case StringID::SYSTEM_ERROR:
      return "System Error!";
    default:
      return "???";
    }
  }
};

// <<< FILE: include/lang/lang_en.h <<<

// >>> FILE: include/lang/lang_tr.h >>>

class TurkishLanguage : public Language {
public:
  const char *getText(StringID id) override {
    switch (id) {
    case StringID::ID_PREFIX:
      return "Id: ";
    case StringID::NO_ACTIVE_TASK:
      return "Aktif Gorev Yok";
    case StringID::LOCATION:
      return "Konum: ";
    case StringID::SUB_SERVICE:
      return "Alt Hizmet: ";
    case StringID::STR_DEVICE_TYPE:
      return "Cihaz: ";
    case StringID::ACCEPTED:
      return "Kabul Edildi";
    case StringID::TASK_REJECTED:
      return "Gorev Reddedildi";
    case StringID::TASK_COMPLETED:
      return "Tamamlandi";
    case StringID::WRONG_LOCATION:
      return "Yanlis Konum!";
    case StringID::GO_TO_CORRECT:
      return "Dogru Konuma";
    case StringID::LOCATION_DOT:
      return "Gidin...";
    case StringID::WEAK_SIGNAL:
      return "Zayif Sinyal!";
    case StringID::RSSI:
      return "RSSI: ";
    case StringID::REQUIRED:
      return "Gerekli: >";
    case StringID::GET_CLOSER:
      return "YaklasÄ±n!";
    case StringID::SYSTEM_ERROR:
      return "Sistem Hatasi!";
    default:
      return "???";
    }
  }
};

// <<< FILE: include/lang/lang_tr.h <<<

// >>> FILE: src/core/time_mgr.h >>>

// TIME MANAGER - NTP sync and timestamp utilities

#include <Arduino.h>
#include <time.h>

class TimeManager {
public:
  // NTP sunucusundan zamanÄ± senkronize et
  void begin(long gmtOffset = 10800, int daylightOffset = 0);

  // Zaman senkronize oldu mu?
  bool isSynced();

  // ISO8601 UTC timestamp: "2024-01-15T14:30:00Z"
  String getTimestampUTC();

  // ISO8601 local timestamp
  String getTimestampLocal();

  // Unix timestamp
  time_t getUnixTime();

  // Saat:Dakika string (ekran iÃ§in)
  String getTimeString();

private:
  bool _synced = false;
};

extern TimeManager timeMgr;

// <<< FILE: src/core/time_mgr.h <<<

// >>> FILE: src/core/time_mgr.cpp >>>

TimeManager timeMgr;

void TimeManager::begin(long gmtOffset, int daylightOffset) {
  LOG_TIME("Configuring NTP (GMT+%d)...\n", gmtOffset / 3600);
  configTime(gmtOffset, daylightOffset, "pool.ntp.org", "time.nist.gov");

  // Ä°lk sync'i bekle (max 10 saniye)
  int retries = 0;
  while (!isSynced() && retries < 20) {
    delay(500);
    retries++;
  }

  if (_synced) {
    LOG_TIME("NTP synced: %s\n", getTimestampLocal().c_str());
  } else {
    LOG_TIME("NTP sync timeout!\n");
  }
}

bool TimeManager::isSynced() {
  time_t now = time(nullptr);
  _synced = (now > 1700000000); // 2023-11-14'ten bÃ¼yÃ¼kse senkronize
  return _synced;
}

String TimeManager::getTimestampUTC() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  char buf[30];
  strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(buf);
}

String TimeManager::getTimestampLocal() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);

  char buf[30];
  strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", &timeinfo);
  return String(buf);
}

time_t TimeManager::getUnixTime() { return time(nullptr); }

String TimeManager::getTimeString() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);

  char buf[6];
  strftime(buf, sizeof(buf), "%H:%M", &timeinfo);
  return String(buf);
}

// <<< FILE: src/core/time_mgr.cpp <<<

// >>> FILE: src/wifi/wifi_mgr.h >>>

// WIFI MANAGER - Connection management with backoff retry

#include <Arduino.h>
#include <WiFi.h>

class WifiManager {
public:
  // WiFi baÄŸlantÄ±sÄ±nÄ± baÅŸlat (NVS'ten yÃ¼kler veya default kullanÄ±r)
  bool begin();

  // Yeni bilgileri kaydet
  void saveCredentials(const char *ssid, const char *password);

  // BaÄŸlÄ± mÄ±?
  bool isConnected();

  // Loop'ta Ã§aÄŸrÄ±lacak - baÄŸlantÄ± kopmuÅŸsa yeniden baÄŸlan
  void tick();

  // IP adresi
  String getIP();

  // Sinyal gÃ¼cÃ¼
  int getRSSI();

  // MAC adresi
  String getMAC();

private:
  const char *_ssid = nullptr;
  const char *_password = nullptr;

  // Backoff retry
  uint32_t _retryAtMs = 0;
  uint32_t _backoffMs = 1000;
  static const uint32_t BACKOFF_MAX_MS = 30000;
  static const uint32_t RETRY_INTERVAL_MS = 10000;
};

extern WifiManager wifiMgr;

// <<< FILE: src/wifi/wifi_mgr.h <<<

// >>> FILE: src/wifi/wifi_mgr.cpp >>>

#include <Preferences.h>
#include <esp_wifi.h>

WifiManager wifiMgr;
Preferences preferences;

bool WifiManager::begin() {
  // Load from NVS
  preferences.begin("wifi", false);
  String saved_ssid = preferences.getString("ssid", "");
  String saved_pass = preferences.getString("password", "");
  preferences.end();

  if (saved_ssid.length() > 0) {
    _ssid = strdup(saved_ssid.c_str());
    _password = strdup(saved_pass.c_str());
    LOG_WIFI("Loaded credentials: %s\n", _ssid);
  } else {
    _ssid = WIFI_SSID_DEFAULT;
    _password = WIFI_PASS_DEFAULT;
    LOG_WIFI("Using default credentials: %s\n", _ssid);
  }

  LOG_WIFI("Connecting to: %s\n", _ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  // BLE ile birlikte Ã§alÄ±ÅŸabilmesi iÃ§in modem sleep aktif
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);

  uint32_t startMs = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startMs > WIFI_RETRY_MS) {
      LOG_WIFI("Connection timeout!\n");
      return false;
    }
    delay(100);
    DPRINT(".");
  }

  DPRINTLN("");
  LOG_WIFI("Connected! IP: %s\n", getIP().c_str());
  LOG_WIFI("RSSI: %d dBm\n", getRSSI());

  _backoffMs = 1000; // Reset backoff
  return true;
}

void WifiManager::saveCredentials(const char *ssid, const char *password) {
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
  LOG_WIFI("Saved new credentials: %s\n", ssid);
}

bool WifiManager::isConnected() { return WiFi.status() == WL_CONNECTED; }

void WifiManager::tick() {
  if (isConnected()) {
    _backoffMs = 1000; // Reset backoff when connected
    return;
  }

  uint32_t now = millis();
  if (now < _retryAtMs) {
    return; // HenÃ¼z retry zamanÄ± gelmedi
  }

  LOG_WIFI("Reconnecting (backoff: %dms)...\n", _backoffMs);
  WiFi.reconnect();

  // Exponential backoff
  _retryAtMs = now + _backoffMs;
  _backoffMs = min(_backoffMs * 2, BACKOFF_MAX_MS);
}

String WifiManager::getIP() { return WiFi.localIP().toString(); }

int WifiManager::getRSSI() { return WiFi.RSSI(); }

String WifiManager::getMAC() { return WiFi.macAddress(); }

// <<< FILE: src/wifi/wifi_mgr.cpp <<<

// >>> FILE: src/led/led_status.h >>>

// LED STATUS - FastLED based status indicator

#include <Arduino.h>
#include <FastLED.h>

enum class LedState {
  LED_OFF,
  LED_WIFI_CONNECTING, // Mavi yanÄ±p sÃ¶nen
  LED_WIFI_CONNECTED,  // YeÅŸil
  LED_MQTT_OK,         // AÃ§Ä±k yeÅŸil (MQTT_CONNECTED yerine)
  LED_BEACON_PUBLISH,  // Mor (kÄ±sa flash)
  LED_ERROR,           // KÄ±rmÄ±zÄ±
  LED_OTA_PROGRESS     // SarÄ± yanÄ±p sÃ¶nen
};

class LedStatus {
public:
  void begin(uint8_t pin, uint8_t numLeds, uint8_t brightness);

  // Durumu ayarla
  void setState(LedState state);

  // Flash (kÄ±sa sÃ¼re farklÄ± renk)
  void flash(CRGB color, uint16_t durationMs = 200);

  // Manuel renk ayarla
  void setColor(CRGB color);

  // Kapat
  void off();

  // Loop'ta Ã§aÄŸrÄ±lmalÄ± (animasyonlar iÃ§in)
  void tick();

private:
  CRGB *_leds = nullptr;
  uint8_t _numLeds = 1;
  LedState _currentState = LedState::LED_OFF;

  uint32_t _blinkMs = 0;
  bool _blinkOn = false;

  uint32_t _flashUntilMs = 0;
  CRGB _flashColor;
  CRGB _previousColor;
};

extern LedStatus ledStatus;

// <<< FILE: src/led/led_status.h <<<

// >>> FILE: src/led/led_status.cpp >>>

LedStatus ledStatus;

// Statik LED array (FastLED gereksinimleri iÃ§in)
static CRGB g_leds[10]; // Max 10 LED destekler

void LedStatus::begin(uint8_t pin, uint8_t numLeds, uint8_t brightness) {
  (void)pin; // pin parametresi device_config.h'den geliyor
  _numLeds = min(numLeds, (uint8_t)10);
  _leds = g_leds;

  // LED_DATA_PIN compile-time constant olarak device_config.h'den geliyor
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(_leds, _numLeds);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  FastLED.show();

  LOG_LED("Initialized %d LEDs on pin %d\n", numLeds, LED_DATA_PIN);
}

void LedStatus::setState(LedState state) {
  if (_currentState == state)
    return;

  _currentState = state;

  switch (state) {
  case LedState::LED_OFF:
  case LedState::LED_WIFI_CONNECTED:
  case LedState::LED_MQTT_OK:
    off();
    break;

  case LedState::LED_WIFI_CONNECTING:
    // User requested dark, but maybe keep blink for connecting?
    // "led sadece gÃ¶rev geldiÄŸindde yanacak" -> strict interpretation: OFF.
    // Let's keep it OFF for connecting too to be safe, or maybe very short
    // flash? Let's stick to OFF for now to strict compliance.
    off();
    break;

  case LedState::LED_ERROR:
    setColor(CRGB::Red); // Keep errors visible? Or off?
    // Let's keep Red for critical errors, but user might want it off.
    // Let's assume Error is exception.
    break;

  case LedState::LED_OTA_PROGRESS:
    _blinkMs = millis();
    _blinkOn = true;
    setColor(CRGB::Yellow);
    break;

  default:
    off();
    break;
  }
}

void LedStatus::flash(CRGB color, uint16_t durationMs) {
  _previousColor = _leds[0];
  _flashColor = color;
  _flashUntilMs = millis() + durationMs;
  setColor(color);
}

void LedStatus::setColor(CRGB color) {
  for (int i = 0; i < _numLeds; i++) {
    _leds[i] = color;
  }
  FastLED.show();
}

void LedStatus::off() {
  FastLED.clear();
  FastLED.show();
}

void LedStatus::tick() {
  uint32_t now = millis();

  // Flash kontrolÃ¼
  if (_flashUntilMs > 0 && now > _flashUntilMs) {
    _flashUntilMs = 0;
    setColor(_previousColor);
    return;
  }

  // Blink animasyonlarÄ±
  if (_currentState == LedState::LED_WIFI_CONNECTING ||
      _currentState == LedState::LED_OTA_PROGRESS) {

    if (now - _blinkMs > 500) {
      _blinkMs = now;
      _blinkOn = !_blinkOn;

      if (_blinkOn) {
        if (_currentState == LedState::LED_WIFI_CONNECTING) {
          setColor(CRGB::Blue);
        } else {
          setColor(CRGB::Yellow);
        }
      } else {
        off();
      }
    }
  }
}

// <<< FILE: src/led/led_status.cpp <<<

// >>> FILE: src/mqtt/mqtt_prov.h >>>

// PROVANCE MQTT CLIENT - Plaintext MQTT for legacy system

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

// Callback tipi
typedef void (*ProvMessageCallback)(const char *topic, const char *payload,
                                    size_t length);

class ProvMqttClient {
public:
  // BaÄŸlantÄ±yÄ± baÅŸlat
  void begin(const char *server, uint16_t port, const char *user,
             const char *pass, const char *clientId);

  // Callback ayarla
  void setCallback(ProvMessageCallback cb);

  // BaÄŸlÄ± mÄ±?
  bool isConnected();

  // BaÄŸlantÄ±yÄ± kontrol et ve yeniden baÄŸlan
  bool ensureConnected();

  // Topic'e abone ol
  void subscribe(const char *topic);

  // Mesaj yayÄ±nla
  bool publish(const char *topic, const char *payload);

  // Loop'ta Ã§aÄŸrÄ±lmalÄ±
  void loop();

private:
  WiFiClient _wifiClient;
  PubSubClient _mqttClient;

  const char *_clientId = nullptr;
  const char *_user = nullptr;
  const char *_pass = nullptr;
  const char *_subTopic = nullptr;
  ProvMessageCallback _callback = nullptr;

  uint32_t _lastRetryMs = 0;
  static const uint32_t RETRY_INTERVAL_MS = 5000;

  static void _internalCallback(char *topic, byte *payload,
                                unsigned int length);
  static ProvMqttClient *_instance;
};

extern ProvMqttClient provMqtt;

// <<< FILE: src/mqtt/mqtt_prov.h <<<

// >>> FILE: src/mqtt/mqtt_prov.cpp >>>

#include <WiFi.h>

ProvMqttClient provMqtt;
ProvMqttClient *ProvMqttClient::_instance = nullptr;

void ProvMqttClient::begin(const char *server, uint16_t port, const char *user,
                           const char *pass, const char *clientId) {
  _instance = this;
  _clientId = clientId;
  _user = user;
  _pass = pass;

  LOG_MQTT("PROVANCE: %s:%d\n", server, port);

  _mqttClient.setClient(_wifiClient);
  _mqttClient.setServer(server, port);
  _mqttClient.setKeepAlive(60);
  _mqttClient.setBufferSize(512);
  _mqttClient.setCallback(_internalCallback);
}

void ProvMqttClient::setCallback(ProvMessageCallback cb) { _callback = cb; }

bool ProvMqttClient::isConnected() { return _mqttClient.connected(); }

bool ProvMqttClient::ensureConnected() {
  if (_mqttClient.connected()) {
    return true;
  }

  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  uint32_t now = millis();
  if (now - _lastRetryMs < RETRY_INTERVAL_MS) {
    return false;
  }
  _lastRetryMs = now;

  LOG_MQTT("PROVANCE connecting as %s...\n", _clientId);

  bool connected = false;
  if (_user && strlen(_user) > 0) {
    connected = _mqttClient.connect(_clientId, _user, _pass);
  } else {
    connected = _mqttClient.connect(_clientId);
  }

  if (connected) {
    LOG_MQTT("PROVANCE connected!\n");
    if (_subTopic) {
      _mqttClient.subscribe(_subTopic);
      LOG_MQTT("PROV re-subscribed: %s\n", _subTopic);
    }
    return true;
  }

  LOG_MQTT("PROVANCE connection failed, state=%d\n", _mqttClient.state());
  return false;
}

void ProvMqttClient::subscribe(const char *topic) {
  _subTopic = topic;
  if (_mqttClient.connected()) {
    _mqttClient.subscribe(topic);
    LOG_MQTT("PROV subscribed: %s\n", topic);
  }
}

bool ProvMqttClient::publish(const char *topic, const char *payload) {
  if (!_mqttClient.connected()) {
    return false;
  }

  bool ok = _mqttClient.publish(topic, payload);

#if DEBUG_PAYLOADS
  LOG_MQTT("PROV â†’ %s: %s\n", topic, payload);
#endif

  return ok;
}

void ProvMqttClient::loop() { _mqttClient.loop(); }

void ProvMqttClient::_internalCallback(char *topic, byte *payload,
                                       unsigned int length) {
  if (_instance && _instance->_callback) {
    char *buf = (char *)malloc(length + 1);
    if (buf) {
      memcpy(buf, payload, length);
      buf[length] = '\0';
      _instance->_callback(topic, buf, length);
      free(buf);
    }
  }
}

// <<< FILE: src/mqtt/mqtt_prov.cpp <<<

// >>> FILE: src/ble/ble_scan.h >>>

// BLE SCANNER - FreeRTOS task for beacon scanning

#include <Arduino.h>

struct BeaconData {
  String uuid;
  int rssi;
  bool valid;
};

class BleScanner {
public:
  // BaÅŸlat (FreeRTOS task oluÅŸturur)
  void begin();

  // Son bulunan beacon'Ä± al (thread-safe)
  BeaconData getLatestBeacon();

  // Beacon deÄŸiÅŸti mi? (deÄŸiÅŸim algÄ±landÄ±ktan sonra false'a dÃ¶ner)
  bool hasChanged();

  // DeÄŸiÅŸimi acknowledge et
  void acknowledgeChange();

  // Scanning'i durdur/baÅŸlat
  void pause();
  void resume();

private:
  static void _scanTask(void *param);

  BeaconData _latestBeacon = {"", -999, false};
  BeaconData _previousBeacon = {"", -999, false};
  bool _changed = false;
  bool _paused = false;

  SemaphoreHandle_t _mutex = nullptr;
  TaskHandle_t _taskHandle = nullptr;
};

extern BleScanner bleScanner;

// <<< FILE: src/ble/ble_scan.h <<<

// >>> FILE: src/ble/ble_scan.cpp >>>

#include <NimBLEDevice.h>

BleScanner bleScanner;

void BleScanner::begin() {
  LOG_BLE("Initializing NimBLE...\n");

  NimBLEDevice::init("");

  _mutex = xSemaphoreCreateMutex();

  // FreeRTOS task - Core 0'da Ã§alÄ±ÅŸsÄ±n (WiFi Core 1'de)
  xTaskCreatePinnedToCore(_scanTask, "BLE_Scan", 4096, this, 1, &_taskHandle,
                          0 // Core 0
  );

  LOG_BLE("Scan task started on Core 0\n");
}

void BleScanner::_scanTask(void *param) {
  BleScanner *self = (BleScanner *)param;

  NimBLEScan *pScan = NimBLEDevice::getScan();
  pScan->setActiveScan(true);
  pScan->setInterval(BLE_SCAN_INTERVAL);
  pScan->setWindow(99);

  for (;;) {
    if (self->_paused) {
      vTaskDelay(pdMS_TO_TICKS(500));
      continue;
    }

    // Scan baÅŸlat
    NimBLEScanResults results =
        pScan->getResults(BLE_SCAN_SECONDS * 1000, false);

    String bestUUID = "";
    int bestRSSI = -999;

    // SonuÃ§larÄ± tara
    for (int i = 0; i < results.getCount(); i++) {
      const NimBLEAdvertisedDevice *dev = results.getDevice(i);

      if (dev->haveServiceUUID()) {
        std::string uuid = dev->getServiceUUID().toString();
        String uuidStr = String(uuid.c_str());

        // UUID prefix kontrolÃ¼
        if (uuidStr.startsWith(BLE_UUID_PREFIX)) {
          int rssi = dev->getRSSI();

          if (rssi > bestRSSI && rssi > BLE_RSSI_MIN) {
            bestRSSI = rssi;
            bestUUID = uuidStr;
          }
        }
      }
    }

    pScan->clearResults();

    // Sonucu gÃ¼ncelle (thread-safe)
    if (xSemaphoreTake(self->_mutex, pdMS_TO_TICKS(100))) {
      // Beacon deÄŸiÅŸimi kontrolÃ¼
      if (bestUUID != self->_latestBeacon.uuid) {
        self->_previousBeacon = self->_latestBeacon;
        self->_changed = true;

        LOG_BLE("Beacon changed: %s â†’ %s (RSSI: %d)\n",
                self->_previousBeacon.uuid.c_str(), bestUUID.c_str(), bestRSSI);
      }

      self->_latestBeacon.uuid = bestUUID;
      self->_latestBeacon.rssi = bestRSSI;
      self->_latestBeacon.valid = (bestUUID.length() > 0);

      xSemaphoreGive(self->_mutex);
    }

    // Sonraki scan'e kadar bekle (30 saniye varsayÄ±lan)
    vTaskDelay(pdMS_TO_TICKS(30000));
  }
}

BeaconData BleScanner::getLatestBeacon() {
  BeaconData result = {"", -999, false};

  if (xSemaphoreTake(_mutex, pdMS_TO_TICKS(100))) {
    result = _latestBeacon;
    xSemaphoreGive(_mutex);
  }

  return result;
}

bool BleScanner::hasChanged() {
  bool changed = false;
  if (xSemaphoreTake(_mutex, pdMS_TO_TICKS(100))) {
    changed = _changed;
    xSemaphoreGive(_mutex);
  }
  return changed;
}

void BleScanner::acknowledgeChange() {
  if (xSemaphoreTake(_mutex, pdMS_TO_TICKS(100))) {
    _changed = false;
    xSemaphoreGive(_mutex);
  }
}

void BleScanner::pause() { _paused = true; }

void BleScanner::resume() { _paused = false; }

// <<< FILE: src/ble/ble_scan.cpp <<<

// >>> FILE: src/ota/ota_mgr.h >>>

// OTA MANAGER - HTTPS OTA updates from manifest

#include <Arduino.h>

class OtaManager {
public:
  // OTA baÅŸlat
  void begin(const char *manifestUrl, const char *currentVersion);

  // GÃ¼ncelleme kontrolÃ¼ (blocking)
  bool checkForUpdate();

  // GÃ¼ncelleme uygula (blocking, cihaz restart olur)
  void applyUpdate();

  // Loop'ta Ã§aÄŸrÄ±lmalÄ± (periyodik kontrol iÃ§in)
  void tick();

  // GÃ¼ncelleme mevcut mu?
  bool updateAvailable();

  // Yeni versiyon bilgisi
  String getNewVersion();
  String getNewUrl();

private:
  const char *_manifestUrl = nullptr;
  const char *_currentVersion = nullptr;

  String _newVersion = "";
  String _newUrl = "";
  bool _updateAvailable = false;

  uint32_t _lastCheckMs = 0;
  uint32_t _checkIntervalMs = 3600000; // 1 saat
  uint32_t _firstCheckDelayMs = 60000; // 1 dakika
  bool _firstCheckDone = false;

  // Semver karÅŸÄ±laÅŸtÄ±rma
  bool isNewerVersion(const String &remote, const String &local);
};

extern OtaManager otaMgr;

// <<< FILE: src/ota/ota_mgr.h <<<

// >>> FILE: src/ota/ota_mgr.cpp >>>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

OtaManager otaMgr;

void OtaManager::begin(const char *manifestUrl, const char *currentVersion) {
  _manifestUrl = manifestUrl;
  _currentVersion = currentVersion;

  LOG_OTA("Initialized, current version: %s\n", currentVersion);
  LOG_OTA("Manifest: %s\n", manifestUrl);
}

bool OtaManager::checkForUpdate() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  LOG_OTA("Checking for updates...\n");

  WiFiClientSecure client;
  client.setInsecure(); // Skip certificate validation

  HTTPClient http;
  http.begin(client, _manifestUrl);
  http.setTimeout(10000);

  int httpCode = http.GET();

  if (httpCode != HTTP_CODE_OK) {
    LOG_OTA("Manifest fetch failed: %d\n", httpCode);
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  // Parse JSON
  StaticJsonDocument<512> doc;
  DeserializationError err = deserializeJson(doc, payload);

  if (err) {
    LOG_OTA("JSON parse error: %s\n", err.c_str());
    return false;
  }

  const char *remoteVersion = doc["version"];
  const char *firmwareUrl = doc["url"];

  if (!remoteVersion || !firmwareUrl) {
    LOG_OTA("Invalid manifest format\n");
    return false;
  }

  LOG_OTA("Remote version: %s\n", remoteVersion);

  if (isNewerVersion(String(remoteVersion), String(_currentVersion))) {
    _newVersion = String(remoteVersion);
    _newUrl = String(firmwareUrl);
    _updateAvailable = true;

    LOG_OTA("Update available: %s â†’ %s\n", _currentVersion, remoteVersion);
    return true;
  }

  LOG_OTA("Already up to date\n");
  return false;
}

void OtaManager::applyUpdate() {
  if (!_updateAvailable || _newUrl.length() == 0) {
    LOG_OTA("No update to apply\n");
    return;
  }

  LOG_OTA("Applying update from: %s\n", _newUrl.c_str());
  ledStatus.setState(LedState::LED_OTA_PROGRESS);

  WiFiClientSecure client;
  client.setInsecure();

  httpUpdate.setLedPin(LED_DATA_PIN, LOW);

  t_httpUpdate_return ret = httpUpdate.update(client, _newUrl);

  switch (ret) {
  case HTTP_UPDATE_FAILED:
    LOG_OTA("Update failed: %s\n", httpUpdate.getLastErrorString().c_str());
    ledStatus.setState(LedState::LED_ERROR);
    break;

  case HTTP_UPDATE_NO_UPDATES:
    LOG_OTA("No updates available\n");
    break;

  case HTTP_UPDATE_OK:
    LOG_OTA("Update successful, restarting...\n");
    ESP.restart();
    break;
  }
}

void OtaManager::tick() {
  uint32_t now = millis();

  // Ä°lk kontrol gecikmesi
  if (!_firstCheckDone) {
    if (now < _firstCheckDelayMs) {
      return;
    }
    _firstCheckDone = true;
    checkForUpdate();
    _lastCheckMs = now;
    return;
  }

  // Periyodik kontrol
  if (now - _lastCheckMs >= _checkIntervalMs) {
    _lastCheckMs = now;
    checkForUpdate();
  }
}

bool OtaManager::updateAvailable() { return _updateAvailable; }

String OtaManager::getNewVersion() { return _newVersion; }

String OtaManager::getNewUrl() { return _newUrl; }

bool OtaManager::isNewerVersion(const String &remote, const String &local) {
  // Simple semver comparison (major.minor.patch)
  int rMaj, rMin, rPat;
  int lMaj, lMin, lPat;

  if (sscanf(remote.c_str(), "%d.%d.%d", &rMaj, &rMin, &rPat) != 3)
    return false;
  if (sscanf(local.c_str(), "%d.%d.%d", &lMaj, &lMin, &lPat) != 3)
    return false;

  if (rMaj > lMaj)
    return true;
  if (rMaj < lMaj)
    return false;
  if (rMin > lMin)
    return true;
  if (rMin < lMin)
    return false;
  return rPat > lPat;
}

// <<< FILE: src/ota/ota_mgr.cpp <<<

// >>> FILE: src/display/tft_mgr.h >>>

// TFT MANAGER - ST7735 Display with power management

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class TftManager {
public:
  void begin();

  void powerOn();
  void powerOff();
  void ensureOn(uint32_t durationMs);
  bool isOn() { return _screenOn; }

  void tick(); // Timeout kontrolÃ¼ (loop'ta Ã§aÄŸrÄ±lmalÄ±)

  void drawHeader(const char *deviceId);
  void drawBattery(float batteryPct);
  void clearContent();

  // Direct TFT access
  Adafruit_ST7735 &getTft() { return *_tft; }

  uint16_t headerColor();

private:
  Adafruit_ST7735 *_tft = nullptr;
  bool _screenOn = false;
  uint32_t _screenOnUntil = 0;
};

extern TftManager tftManager;

// <<< FILE: src/display/tft_mgr.h <<<

// >>> FILE: src/display/tft_mgr.cpp >>>

#include <Arduino.h>

TftManager tftManager;

// RGB565 color constants
#define COLOR_WHITE 0xFFFF
#define COLOR_GREEN 0x07E0

void TftManager::begin() {
  pinMode(TFT_POWER, OUTPUT);
  digitalWrite(TFT_POWER, LOW);
  _screenOn = false;
  _screenOnUntil = 0;

  // TFT'yi oluÅŸtur (power aÃ§Ä±ldÄ±ÄŸÄ±nda init edilecek)
  _tft = new Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

  LOG_BOOT("TFT initialized (power off)\n");
}

void TftManager::powerOn() {
  digitalWrite(TFT_POWER, HIGH);
  delay(60);

  _tft->initR(INITR_BLACKTAB);
  _tft->setRotation(1);
  _screenOn = true;

  _tft->fillScreen(TFT_BACKGROUND);
  _tft->fillRect(0, 0, TFT_WIDTH, TFT_HEADER_HEIGHT, headerColor());

  LOG_BOOT("TFT powered on\n");
}

void TftManager::powerOff() {
  if (!_screenOn) {
    digitalWrite(TFT_POWER, LOW);
    return;
  }

  _tft->fillScreen(TFT_BACKGROUND);
  delay(10);
  digitalWrite(TFT_POWER, LOW);
  _screenOn = false;

  LOG_BOOT("TFT powered off\n");
}

void TftManager::ensureOn(uint32_t durationMs) {
  uint32_t until = millis() + durationMs;
  if (until < _screenOnUntil) {
    // Already on for longer
  } else {
    _screenOnUntil = until;
  }

  if (!_screenOn) {
    powerOn();
  }
}

void TftManager::tick() {
  if (_screenOn && _screenOnUntil > 0 && millis() > _screenOnUntil) {
    powerOff();
  }
}

uint16_t TftManager::headerColor() {
  if (wifiMgr.isConnected())
    return TFT_HEADER_COLOR;
  return TFT_REJECT_COLOR;
}

void TftManager::drawHeader(const char *deviceId) {
  if (!_screenOn)
    return;

  _tft->fillRect(0, 0, TFT_WIDTH, TFT_HEADER_HEIGHT, headerColor());
  _tft->setTextSize(TFT_FONT_SMALL);
  _tft->setTextColor(COLOR_WHITE);
  _tft->setCursor(TFT_MARGIN, (TFT_HEADER_HEIGHT - 8) / 2);
  _tft->print("Id: ");
  _tft->print(deviceId);
}

void TftManager::drawBattery(float batteryPct) {
  if (!_screenOn)
    return;

  int barW = 6;
  int barH = TFT_HEADER_HEIGHT - 4;
  int barX = TFT_WIDTH - TFT_MARGIN - barW;
  int barY = 2;

  _tft->drawRect(barX, barY, barW, barH, COLOR_WHITE);

  int fillH = (int)((batteryPct / 100.0) * (barH - 2));
  _tft->fillRect(barX + 1, barY + barH - 1 - fillH, barW - 2, fillH,
                 COLOR_GREEN);

  String pct = String((int)batteryPct) + "%";
  _tft->setTextSize(TFT_FONT_SMALL);
  _tft->setTextColor(COLOR_WHITE);
  int txtX = barX - (pct.length() * 6) - 2;
  int txtY = (TFT_HEADER_HEIGHT - 8) / 2;
  _tft->setCursor(txtX, txtY);
  _tft->print(pct);
}

void TftManager::clearContent() {
  if (!_screenOn)
    return;
  _tft->fillRect(0, TFT_HEADER_HEIGHT, TFT_WIDTH,
                 TFT_HEIGHT - TFT_HEADER_HEIGHT, TFT_BACKGROUND);
}

// <<< FILE: src/display/tft_mgr.cpp <<<

// >>> FILE: src/display/ui_screens.h >>>

// UI SCREENS - Task display functions

#include <Arduino.h>

struct TaskData {
  String section;
  String subCategory;
  String deviceType;
  String taskId;
  String beaconId;
};

void showMainScreen(const char *deviceId, float batteryPct);
void showIncomingTask(const TaskData &task, float batteryPct);
void showAcceptedTask(const TaskData &task, float batteryPct);
void showMessage(const char *msg, uint16_t color, float batteryPct);
void showWrongLocation(float batteryPct);
void showWeakSignal(int currentRSSI, int requiredRSSI, float batteryPct);
void showSystemError(float batteryPct);

// <<< FILE: src/display/ui_screens.h <<<

// >>> FILE: src/display/ui_screens.cpp >>>

#include <Adafruit_ST7735.h>
#include <deque>

extern std::deque<TaskData> g_taskQueue;

void showMainScreen(const char *deviceId, float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tft.fillScreen(TFT_BACKGROUND);

  tftManager.drawHeader(deviceId);
  tftManager.drawBattery(batteryPct);

  // "No Active Task" mesajÄ± - Centered
  tft.setTextSize(TFT_FONT_SMALL);
  tft.setTextColor(0xFFFF); // White

  const char *text;
  if (!g_taskQueue.empty()) {
    // Pending tasks
    static char buf[32];
    snprintf(buf, sizeof(buf), "Waiting: %d",
             g_taskQueue.size()); // Hardcoded Turkish for now or add to Lang
    text = buf;
  } else {
    text = currentLang->getText(StringID::NO_ACTIVE_TASK);
  }
  int len = strlen(text);
  int pxLen = len * 6; // 6px per char for size 1
  int x = (TFT_WIDTH - pxLen) / 2;
  if (x < TFT_MARGIN)
    x = TFT_MARGIN;

  int y = (TFT_HEIGHT - TFT_HEADER_HEIGHT) / 2 + TFT_HEADER_HEIGHT - 4;

  tft.setCursor(x, y);
  tft.print(text);
}

void showIncomingTask(const TaskData &task, float batteryPct) {
  tftManager.ensureOn(90000); // GÃ¶rev varken ekranÄ± uzun sÃ¼re aÃ§Ä±k tut

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();
  tftManager.drawHeader(CARD_ID); // Ensure header is shown

  tft.setTextSize(TFT_FONT_SMALL);
  tft.setTextColor(TFT_TASK_COLOR);

  int x = TFT_MARGIN;
  int y = TFT_HEADER_HEIGHT + 8;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::LOCATION));
  y += TFT_LINE_HEIGHT;

  tft.setCursor(x, y);
  tft.print(task.section);
  // Handle wrapping by reading cursor Y
  y = tft.getCursorY() + TFT_LINE_HEIGHT + 4;

  // Sub Service REMOVED as per user request
  // tft.setCursor(x, y);
  // tft.print(currentLang->getText(StringID::SUB_SERVICE));
  // y += TFT_LINE_HEIGHT;
  // tft.setCursor(x, y);
  // tft.print(task.subCategory);
  // y += TFT_LINE_HEIGHT;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::STR_DEVICE_TYPE));
  y += TFT_LINE_HEIGHT;

  tft.setTextSize(TFT_FONT_MEDIUM); // Larger font for Device
  tft.setCursor(x, y);
  tft.print(task.deviceType);

  tftManager.drawBattery(batteryPct);
}

void showAcceptedTask(const TaskData &task, float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();
  tftManager.drawHeader(CARD_ID);

  // Title
  tft.setTextSize(TFT_FONT_MEDIUM);
  tft.setTextColor(TFT_ACCEPT_COLOR);
  int y = TFT_HEADER_HEIGHT + 5;
  tft.setCursor(TFT_MARGIN, y);
  tft.print(currentLang->getText(StringID::ACCEPTED));

  // Details
  tft.setTextSize(TFT_FONT_SMALL);
  tft.setTextColor(ST7735_WHITE);

  y += 20;        // Space after title
  int lineH = 11; // Compressed line height

  tft.setCursor(TFT_MARGIN, y);
  tft.print(currentLang->getText(StringID::LOCATION));
  y += lineH;
  tft.setCursor(TFT_MARGIN, y);
  tft.print(task.section);
  // Update Y based on cursor in case of wrap
  y = tft.getCursorY() + lineH + 4;

  // Sub Service REMOVED
  // tft.setCursor(TFT_MARGIN, y);
  // tft.print(currentLang->getText(StringID::SUB_SERVICE));
  // y += lineH;
  // tft.setCursor(TFT_MARGIN, y);
  // tft.print(task.subCategory);
  // y += lineH + 4;

  tft.setCursor(TFT_MARGIN, y);
  tft.print(currentLang->getText(StringID::STR_DEVICE_TYPE));
  y += lineH;

  tft.setTextSize(TFT_FONT_MEDIUM); // Larger font
  tft.setCursor(TFT_MARGIN, y);
  tft.print(task.deviceType);

  tftManager.drawBattery(batteryPct);
}

void showMessage(const char *msg, uint16_t color, float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();

  tft.setTextSize(TFT_FONT_MEDIUM);
  tft.setTextColor(color);
  tft.setCursor(TFT_MARGIN, TFT_HEADER_HEIGHT + 40);
  tft.print(msg);

  tftManager.drawBattery(batteryPct);
}

void showWrongLocation(float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(TFT_REJECT_COLOR);

  int x = TFT_MARGIN;
  int y = TFT_HEADER_HEIGHT + 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::WRONG_LOCATION));
  y += 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::GO_TO_CORRECT));
  y += 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::LOCATION_DOT));

  tft.setFont(NULL);

  tftManager.drawBattery(batteryPct);
}

void showWeakSignal(int currentRSSI, int requiredRSSI, float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(TFT_REJECT_COLOR);

  int x = TFT_MARGIN;
  int y = TFT_HEADER_HEIGHT + 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::WEAK_SIGNAL));
  y += 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::RSSI));
  tft.print(currentRSSI);
  y += 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::REQUIRED));
  tft.print(requiredRSSI);
  y += 20;

  tft.setCursor(x, y);
  tft.print(currentLang->getText(StringID::GET_CLOSER));

  tft.setFont(NULL);

  tftManager.drawBattery(batteryPct);
}

void showSystemError(float batteryPct) {
  tftManager.ensureOn(25000);

  Adafruit_ST7735 &tft = tftManager.getTft();
  tftManager.clearContent();

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.setTextColor(TFT_REJECT_COLOR);
  tft.setCursor(TFT_MARGIN, TFT_HEADER_HEIGHT + 20);
  tft.print(currentLang->getText(StringID::SYSTEM_ERROR));

  tft.setFont(NULL);

  tftManager.drawBattery(batteryPct);
}

// <<< FILE: src/display/ui_screens.cpp <<<

// >>> FILE: src/buttons/button_handler.h >>>

// BUTTON HANDLER - 4-button debounced input

#include <Arduino.h>

enum class ButtonEvent { NONE, UP, DOWN, ACCEPT, REJECT };

class ButtonHandler {
public:
  void begin();
  ButtonEvent poll(); // Non-blocking, loop'ta Ã§aÄŸrÄ±lmalÄ±

private:
  uint32_t _lastAcceptDebounce = 0;
  uint32_t _lastRejectDebounce = 0;
  uint32_t _lastUpDebounce = 0;
  uint32_t _lastDownDebounce = 0;

  static constexpr uint32_t DEBOUNCE_MS = 50;
};

extern ButtonHandler buttonHandler;

// <<< FILE: src/buttons/button_handler.h <<<

// >>> FILE: src/buttons/button_handler.cpp >>>

ButtonHandler buttonHandler;

void ButtonHandler::begin() {
  pinMode(BTN_ACCEPT, INPUT_PULLUP);
  pinMode(BTN_REJECT, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  LOG_BOOT("Buttons initialized\n");
}

ButtonEvent ButtonHandler::poll() {
  uint32_t now = millis();

  if (digitalRead(BTN_UP) == LOW && now - _lastUpDebounce > DEBOUNCE_MS) {
    _lastUpDebounce = now;
    LOG_BOOT("[Button] UP\n");
    return ButtonEvent::UP;
  }

  if (digitalRead(BTN_DOWN) == LOW && now - _lastDownDebounce > DEBOUNCE_MS) {
    _lastDownDebounce = now;
    LOG_BOOT("[Button] DOWN\n");
    return ButtonEvent::DOWN;
  }

  if (digitalRead(BTN_ACCEPT) == LOW &&
      now - _lastAcceptDebounce > DEBOUNCE_MS) {
    _lastAcceptDebounce = now;
    LOG_BOOT("[Button] ACCEPT\n");
    return ButtonEvent::ACCEPT;
  }

  if (digitalRead(BTN_REJECT) == LOW &&
      now - _lastRejectDebounce > DEBOUNCE_MS) {
    _lastRejectDebounce = now;
    LOG_BOOT("[Button] REJECT\n");
    return ButtonEvent::REJECT;
  }

  return ButtonEvent::NONE;
}

// <<< FILE: src/buttons/button_handler.cpp <<<

// >>> FILE: src/main.cpp >>>

//
// PERSONNEL CARD v2 - ModÃ¼ler ESP32 Firmware
//
#include <Arduino.h>
#include <deque>

// Config

// Core

// Modules

#if FEATURE_MQTT_PROV
#endif

#if FEATURE_BLE
#endif

#if FEATURE_OTA
#endif

#if FEATURE_DISPLAY

#endif

#if FEATURE_BUTTONS
#endif

#include <ArduinoJson.h>

//
// GLOBALS
//
static uint32_t g_lastStatusMs = 0;

#if FEATURE_DISPLAY
// Language instance
Language *currentLang = nullptr;

// Battery
float g_batteryPct = 100.0;

// Task state
TaskData g_incomingTask;
TaskData g_acceptedTask;
bool g_taskAvailable = false;
bool g_viewingAcceptedTask = false;
std::deque<TaskData> g_taskQueue;
#endif

//
// BATTERY (if enabled)
//
#if FEATURE_DISPLAY
void updateBattery() {
  const float R1 = 1000.0, R2 = 3300.0;
  int adc = 0;
  for (int i = 0; i < 17; i++) {
    adc += analogRead(BATTERY_PIN);
    delay(1);
  }
  adc /= 17;
  float voltage = (adc * 3.3 / 4095.0) * ((R1 + R2) / R2);

  if (voltage >= 4.20)
    g_batteryPct = 100;
  else if (voltage >= 3.90)
    g_batteryPct = 80;
  else if (voltage >= 3.60)
    g_batteryPct = 55;
  else if (voltage >= 3.30)
    g_batteryPct = 30;
  else if (voltage >= 3.00)
    g_batteryPct = 10;
  else
    g_batteryPct = 0;
}
#endif

//
// PAYLOAD BUILDERS
//

String buildProvPayload(const String &beaconId) {
  StaticJsonDocument<384> doc;

  doc["deviceGroupId"] = PROV_DEVICE_GROUP;
  doc["deviceId"] = PROV_DEVICE_ID;
  doc["dateTime"] = timeMgr.getTimestampLocal();

  JsonObject data = doc.createNestedObject("data");
  data["beaconId"] = beaconId.length() > 0 ? beaconId : (const char *)nullptr;
  data["taskId"] = nullptr;
  data["status"] = nullptr;

  String output;
  serializeJson(doc, output);
  return output;
}

String buildProvTaskStatus(const String &taskId, int status) {
  StaticJsonDocument<384> doc;

  doc["deviceGroupId"] = PROV_DEVICE_GROUP;
  doc["deviceId"] = PROV_DEVICE_ID;
  doc["dateTime"] = timeMgr.getTimestampLocal();

  JsonObject data = doc.createNestedObject("data");
  data["taskId"] = taskId;
  data["status"] = status;
  data["beaconId"] = nullptr;

  String output;
  serializeJson(doc, output);
  return output;
}

//
// TASK CALLBACKS (PROVANCE MQTT)
//
#if FEATURE_MQTT_PROV && FEATURE_DISPLAY
void processWiFiCommand(const char *ssid, const char *pass) {
  LOG_MQTT("Received WiFi update command\n");

  // Show on screen
  tftManager.ensureOn(25000);
  Adafruit_ST7735 &tft = tftManager.getTft();
  tft.fillScreen(TFT_BACKGROUND);
  tftManager.drawHeader(CARD_ID);

  tft.setTextSize(1);
  tft.setTextColor(TFT_TASK_COLOR);
  tft.setCursor(TFT_MARGIN, TFT_HEADER_HEIGHT + 20);
  tft.print("Updating WiFi...");
  tft.setCursor(TFT_MARGIN, TFT_HEADER_HEIGHT + 35);
  tft.print("SSID: ");
  tft.print(ssid);

  // Save and restart
  wifiMgr.saveCredentials(ssid, pass);

  delay(2000);
  ESP.restart();
}

void onProvMqttMessage(const char *topic, const char *payload, size_t length) {
  LOG_MQTT("[PROV] Message on %s: %s\n", topic, payload);

  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, payload, length)) {
    LOG_MQTT("[PROV] JSON parse error\n");
    return;
  }

  // Check for config commands (command field in JSON)
  const char *cmd = doc["command"];
  if (cmd) {
    // deviceId kontrolÃ¼ â€” sadece bu cihaza gelen komutu iÅŸle
    const char *targetId = doc["deviceId"];
    if (!targetId || strcmp(targetId, CARD_ID) != 0) {
      LOG_MQTT("[PROV] Ignored command for %s\n", targetId ? targetId : "null");
      return;
    }

    if (strcmp(cmd, "setWiFi") == 0) {
      const char *ssid = doc["ssid"];
      const char *pass = doc["password"];
      if (ssid && pass) {
        processWiFiCommand(ssid, pass);
      }
    }
    return;
  }

  // Task mesajÄ± mÄ±?
  if (doc.containsKey("taskId") && doc.containsKey("section")) {
    // Check Device ID
    const char *targetDevice = doc["deviceId"];
    if (targetDevice && strcmp(targetDevice, CARD_ID) != 0) {
      LOG_MQTT("[MQTT] Ignored task for %s\n", targetDevice);
      return;
    }

    TaskData newTask;
    newTask.section = doc["section"].as<String>();
    newTask.subCategory = doc["serviceSubCategory"].as<String>();
    newTask.deviceType = doc["deviceType"].as<String>();
    newTask.taskId = doc["taskId"].as<String>();
    newTask.beaconId = doc["beaconId"].as<String>();

    bool busy = g_taskAvailable || (g_acceptedTask.taskId.length() > 0);

    if (busy) {
      g_taskQueue.push_back(newTask);
      LOG_MQTT("[TASK] Queued task: %s (Queue: %d)\n", newTask.taskId.c_str(),
               g_taskQueue.size());
      // KuyruÄŸa alÄ±ndÄ± bildirimi: LED + motor kÄ±sa (1sn)
      ledStatus.setColor(CRGB::Blue);
#if FEATURE_VIBRATION
      digitalWrite(VIBRATION_PIN, HIGH);
#endif
      delay(1000);
#if FEATURE_VIBRATION
      digitalWrite(VIBRATION_PIN, LOW);
#endif
      ledStatus.off();
    } else {
      g_incomingTask = newTask;
      g_taskAvailable = true;
      LOG_MQTT("[TASK] New task: %s\n", g_incomingTask.taskId.c_str());

      // 1. EkranÄ± aÃ§ ve gÃ¶revi gÃ¶ster (showIncomingTask kendi ensureOn'unu
      // Ã§aÄŸÄ±rÄ±r)
      updateBattery();
      showIncomingTask(g_incomingTask, g_batteryPct);

      // 2. LED + Motor birlikte baÅŸlat
      ledStatus.setColor(CRGB::Blue);
#if FEATURE_VIBRATION
      digitalWrite(VIBRATION_PIN, HIGH);
#endif

      // 3. Hepsi birlikte 2 saniye Ã§alÄ±ÅŸsÄ±n
      delay(2000);

      // 4. Motor kapat, LED kapat
#if FEATURE_VIBRATION
      digitalWrite(VIBRATION_PIN, LOW);
#endif
      ledStatus.off();
    }
  }
}
#endif

//
// BEACON PUBLISH
//
void publishBeaconIfChanged() {
#if FEATURE_BLE
  if (!bleScanner.hasChanged()) {
    return;
  }

  BeaconData beacon = bleScanner.getLatestBeacon();
  bleScanner.acknowledgeChange();

  // LED flash
  ledStatus.flash(CRGB::Purple, 200);

#if FEATURE_MQTT_PROV
  if (provMqtt.isConnected()) {
    String payload = buildProvPayload(beacon.uuid);
    provMqtt.publish(PROV_TOPIC, payload.c_str());
  }
#endif
#endif
}

//
// BUTTON HANDLING
//
#if FEATURE_BUTTONS && FEATURE_DISPLAY
void handleButtons() {
  ButtonEvent evt = buttonHandler.poll();

  if (evt == ButtonEvent::NONE)
    return;

  updateBattery();
  tftManager.ensureOn(25000);

  switch (evt) {
  case ButtonEvent::UP:
    if (g_taskAvailable) {
      showIncomingTask(g_incomingTask, g_batteryPct);
    } else if (g_acceptedTask.taskId.length() > 0) {
      g_viewingAcceptedTask = true;
      showAcceptedTask(g_acceptedTask, g_batteryPct);
    }
    break;

  case ButtonEvent::DOWN:
    g_viewingAcceptedTask = false;
    showMainScreen(CARD_ID, g_batteryPct);
    break;

  case ButtonEvent::ACCEPT:
    if (g_viewingAcceptedTask && g_acceptedTask.taskId.length() > 0) {
      // Task complete - beacon kontrolÃ¼
      BeaconData beacon = bleScanner.getLatestBeacon();

      if (beacon.uuid != g_acceptedTask.beaconId) {
        showWrongLocation(g_batteryPct);
#if FEATURE_VIBRATION
        digitalWrite(VIBRATION_PIN, HIGH);
        delay(500);
        digitalWrite(VIBRATION_PIN, LOW);
#endif
        return;
      }

      if (beacon.rssi <= BLE_RSSI_MIN) {
        showWeakSignal(beacon.rssi, BLE_RSSI_MIN, g_batteryPct);
#if FEATURE_VIBRATION
        digitalWrite(VIBRATION_PIN, HIGH);
        delay(500);
        digitalWrite(VIBRATION_PIN, LOW);
#endif
        return;
      }

      // Complete!
      String payload =
          buildProvTaskStatus(g_acceptedTask.taskId, 3); // 3=completed
      provMqtt.publish(PROV_TOPIC, payload.c_str());

      showMessage(currentLang->getText(StringID::TASK_COMPLETED),
                  TFT_ACCEPT_COLOR, g_batteryPct);
      g_acceptedTask = TaskData();
      g_viewingAcceptedTask = false;

      // Check queue
      if (!g_taskQueue.empty()) {
        g_incomingTask = g_taskQueue.front();
        g_taskQueue.pop_front();
        g_taskAvailable = true;
        showIncomingTask(g_incomingTask, g_batteryPct);
        ledStatus.flash(CRGB::Blue, 2000);
      } else {
        showMainScreen(CARD_ID, g_batteryPct);
      }

    } else if (g_taskAvailable) {
      // Accept task
      g_acceptedTask = g_incomingTask;
      g_incomingTask = TaskData();
      g_taskAvailable = false;

      String payload =
          buildProvTaskStatus(g_acceptedTask.taskId, 1); // 1=accepted
      provMqtt.publish(PROV_TOPIC, payload.c_str());

      showMessage(currentLang->getText(StringID::ACCEPTED), TFT_ACCEPT_COLOR,
                  g_batteryPct);
      ledStatus.off(); // Turn off LED when accepted
    }
    break;

  case ButtonEvent::REJECT:
    if (g_taskAvailable) {
      String payload =
          buildProvTaskStatus(g_incomingTask.taskId, 2); // 2=rejected
      provMqtt.publish(PROV_TOPIC, payload.c_str());

      showMessage(currentLang->getText(StringID::TASK_REJECTED),
                  TFT_REJECT_COLOR, g_batteryPct);
      g_incomingTask = TaskData();
      g_taskAvailable = false;

      // Check queue
      if (!g_taskQueue.empty()) {
        g_incomingTask = g_taskQueue.front();
        g_taskQueue.pop_front();
        g_taskAvailable = true;
        showIncomingTask(g_incomingTask, g_batteryPct);
        ledStatus.flash(CRGB::Blue, 2000);
      }
    }
    break;

  default:
    break;
  }
}
#endif

//
// STATUS LOG
//
void printStatus() {
#if DEBUG_SERIAL
  uint32_t now = millis();
  if (now - g_lastStatusMs < DEBUG_STATUS_MS)
    return;
  g_lastStatusMs = now;

  DPRINTF("\n[STATUS] Uptime: %ds | WiFi: %s (%d dBm)", now / 1000,
          wifiMgr.isConnected() ? "OK" : "DISCONNECTED", wifiMgr.getRSSI());

#if FEATURE_MQTT_PROV
  DPRINTF(" | PROV: %s", provMqtt.isConnected() ? "OK" : "NO");
#endif

#if FEATURE_BLE
  BeaconData b = bleScanner.getLatestBeacon();
  if (b.valid) {
    DPRINTF(" | Beacon: %s (%d)", b.uuid.c_str(), b.rssi);
  }
#endif

  DPRINTLN("");
#endif
}

//
// SETUP
//
void setup() {
  Serial.begin(115200);
  delay(500);

  LOG_BOOT("\n\n========================================\n");
  LOG_BOOT("  Personnel Card v%s\n", FW_VERSION);
  LOG_BOOT("  Card ID: %s\n", CARD_ID);
  LOG_BOOT("  ThingName: %s\n", THINGNAME);
  LOG_BOOT("========================================\n\n");

// Language setup
#if FEATURE_DISPLAY
  if (strcmp(DEVICE_LANG, "EN") == 0) {
    currentLang = new EnglishLanguage();
  } else {
    currentLang = new TurkishLanguage();
  }
#endif

  // LED baÅŸlat
  ledStatus.begin(LED_DATA_PIN, LED_NUM_LEDS, LED_BRIGHTNESS);
  ledStatus.setState(LedState::LED_OFF);
  LOG_BOOT("LED initialized\n");

// Display baÅŸlat
#if FEATURE_DISPLAY
  pinMode(BATTERY_PIN, INPUT);
  tftManager.begin();
  LOG_BOOT("TFT initialized\n");
#endif

// Buttons baÅŸlat
#if FEATURE_BUTTONS
  buttonHandler.begin();
#endif

// Vibration
#if FEATURE_VIBRATION
  pinMode(VIBRATION_PIN, OUTPUT);
  digitalWrite(VIBRATION_PIN, LOW);
  LOG_BOOT("Vibration initialized\n");
#endif

  // WiFi baÄŸlan
  if (!wifiMgr.begin()) {
    LOG_BOOT("WiFi failed, restarting...\n");
    delay(3000);
    ESP.restart();
  }
  // ledStatus.setState(LedState::LED_WIFI_CONNECTED); // Removed steady state

// NTP zaman senkronizasyonu
#if FEATURE_NTP
  timeMgr.begin(10800); // GMT+3
#endif

// PROVANCE MQTT
#if FEATURE_MQTT_PROV
  provMqtt.begin(PROV_MQTT_SERVER, PROV_MQTT_PORT, PROV_MQTT_USER,
                 PROV_MQTT_PASS, PROV_DEVICE_ID);
#if FEATURE_DISPLAY
  provMqtt.setCallback(onProvMqttMessage);
  provMqtt.subscribe(
      PROV_TOPIC_TASK); // Tek topic: hem task hem config komutlarÄ±
#endif
#endif

// BLE Scanner
#if FEATURE_BLE
  bleScanner.begin();
#endif

// OTA
#if FEATURE_OTA
  otaMgr.begin(OTA_MANIFEST_URL, FW_VERSION);
#endif

// Display ilk ekran
#if FEATURE_DISPLAY
  updateBattery();
  showMainScreen(CARD_ID, g_batteryPct);
#endif

  LOG_BOOT("\n========================================\n");
  LOG_BOOT("  System Ready!\n");
  LOG_BOOT("========================================\n\n");
}

//
// LOOP
//
void loop() {
  // WiFi yeniden baÄŸlanma
  wifiMgr.tick();

// MQTT baÄŸlantÄ±larÄ±
#if FEATURE_MQTT_AWS
  awsMqtt.ensureConnected();
  awsMqtt.loop();
#endif

#if FEATURE_MQTT_PROV
  provMqtt.ensureConnected();
  provMqtt.loop();
#endif

  // MQTT bağlandıysa LED güncelle
#if FEATURE_MQTT_PROV
  if (provMqtt.isConnected()) {
    ledStatus.setState(LedState::LED_MQTT_OK);
  } else if (wifiMgr.isConnected()) {
    ledStatus.setState(LedState::LED_WIFI_CONNECTED);
  }
#endif

  // Beacon publish
  publishBeaconIfChanged();

// OTA kontrolÃ¼
#if FEATURE_OTA
  otaMgr.tick();
#endif

  // LED animasyonlarÄ±
  ledStatus.tick();

// Display timeout
#if FEATURE_DISPLAY
  tftManager.tick();
#endif

// Buttons
#if FEATURE_BUTTONS && FEATURE_DISPLAY
  handleButtons();
#endif

  // Status log
  printStatus();
}

// <<< FILE: src/main.cpp <<<