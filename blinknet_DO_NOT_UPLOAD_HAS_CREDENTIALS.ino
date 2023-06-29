#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "WIFI_SSID"
#define STAPSK "WIFI_password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "OTA-LEDS";

void setup() {
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, LOW);  // Inverted state - Turn the LED OFF


  Serial.println("Booting");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Retrying connection...");
  }

  Serial.println("Connected");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
 // Serial.println("loop");
 // Serial.println("-");
}
