#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TMP36PIN A0
#define temperature_pin V5

const char* ssid = "YOUR_OWN_WiFi_SSID";
const char* password = "YOUR_OWN_WiFi_PASSWORD";
const char* auth_token = "YOUR_OWN_AUTH_TOKEN";

BlynkTimer blynk_timer;


void sendSensordata() {
  // Get temperature from TMP36 sensor
  float adcVal = analogRead(TMP36PIN);
  float c = ((adcVal * (3300.0/1024)) - 500) / 10;

  // Send to a virtual bin on the Blynk server
  Blynk.virtualWrite(temperature_pin, c);
}

void setup() {
  delay(500);
  Serial.begin(74880);
  BLYNK_LOG2("Rest Reason: ", ESP.getResetReason());

  // Connect to the Blynk server
  BLYNK_LOG("*** Connect to the Blynk server ***");
  Blynk.begin(auth_token, ssid, password);

  // Setup a function to be called every 1000[ms]
  blynk_timer.setInterval(1000L, sendSensordata);
 }

void loop() {
  Blynk.run();
  blynk_timer.run();
}
