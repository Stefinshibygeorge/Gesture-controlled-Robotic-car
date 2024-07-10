#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h> // for I2C communication
#include <Adafruit_ADXL345_U.h> // ADXL345 accelerometer library

// Replace with your network credentials
const char* ssid = "MyESP";
const char* password = "01234567";

AsyncWebServer server(80);

// Initialize the ADXL345 sensor
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(0x53);

void setup() {
  Serial.begin(115200);
  
  // Initialize the ADXL345 sensor
  while(!accel.begin()) {
    Serial.println("ADXL345 initialization failed!");
  }
  Serial.println("ADXL Sucess!");
  
  // Connect to Wi-Fi network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  // Print IP address
  Serial.println(WiFi.softAPIP());

  // Route to read accelerometer data
  server.on("/Xacc", HTTP_GET, [](AsyncWebServerRequest *request){
    sensors_event_t event;
    accel.getEvent(&event);
    String x_response = String(event.acceleration.x);
    request->send(200, "text/plain", x_response);
  });

    server.on("/Yacc", HTTP_GET, [](AsyncWebServerRequest *request){
    sensors_event_t event;
    accel.getEvent(&event);
    String y_response = String(event.acceleration.y);
    request->send(200, "text/plain", y_response);
  });

    server.on("/Zacc", HTTP_GET, [](AsyncWebServerRequest *request){
    sensors_event_t event;
    accel.getEvent(&event);
    String z_response = String(event.acceleration.z);
    request->send(200, "text/plain", z_response);
  });
  
  // Start server
  server.begin();
}

void loop() {
  // Nothing to do here since everything is handled in setup()
}
