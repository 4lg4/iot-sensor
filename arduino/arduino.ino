#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// WiFi settings
const char* wifiName = "Alga&Paula";
const char* wifiPassword = "minha@casa@australia";

// Service
const char* serviceUrl = "http://connected.alga.me/api"; 
const char* serviceToken = "SuperSecret@t0k3n"; 
const char* clientId = "josias"; 
const char* iotId = "josias-temperature-sensor"; 

// float resolution = 3.3/1023;// 3.3 is the supply volt  & 1023 is max analog read value

// TODO: create script based on this code
// https://42bots.com/tutorials/esp8266-wifi-tutorial-arduino-ide/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  WiFi.begin(wifiName, wifiPassword);
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

// "debounce"
int sendInterval = 0;
int sendFlag = 0; 

float getRead() {
  float read_ = analogRead(A0);
  // float temp = read_ * 1.7;
  return read_;
}
// void loop() {
//   Serial.println("-------------------------------------");
//   Serial.println(read_);
//   Serial.println(temp);

//   int httpCode = http.POST(JSONmessageBuffer); //Send the request
//   String payload = http.getString(); //Get the response payload
//   Serial.println(httpCode); //Print HTTP return code
//   Serial.println(payload); //Print request response payload
//   http.end(); //Close connection

//   digitalWrite(LED_BUILTIN, HIGH);
//   delay(500);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(500);
// }


void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["sensorType"] = "Temperature";
 
    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
    values.add(getRead()); //Add value to array
 
    // JsonArray& timestamps = JSONencoder.createNestedArray("timestamps"); //JSON array
    // timestamps.add("10:10"); //Add value to array
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http; // Declare object of class HTTPClient
 
    http.begin(serviceUrl +"/"+ clientId +"/"+ iotId);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("token", serviceToken);
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(30000);  //Send a request every 30 seconds
 
}
