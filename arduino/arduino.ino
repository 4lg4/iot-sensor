#include <ESP8266WiFi.h>

// Replace these with your WiFi network settings
const char* ssid = "ESP8266"; //replace this with your WiFi network name
const char* password = "ESP8266Test"; //replace this with your WiFi network password


// float resolution = 3.3/1023;// 3.3 is the supply volt  & 1023 is max analog read value

// TODO: create script based on this code
// https://42bots.com/tutorials/esp8266-wifi-tutorial-arduino-ide/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}
// (adc/1023.0)*500.0


void loop() {
  float read_ = analogRead(A0);
  float temp = read_ * 1.7;

  Serial.println("-------------------------------------");
  Serial.println(read_);
  Serial.println(temp);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
