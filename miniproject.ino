#include <WiFi.h>

#define BLED 2 

#define M1_ENA 5
#define M1_ENB 18
#define M2_ENA 19
#define M2_ENB 21

#define M1_A1 13
#define M1_A2 12
#define M1_B1 14
#define M1_B2 27

#define M2_A1 26
#define M2_A2 25
#define M2_B1 33
#define M2_B2 32
                                                                      
const char* ssid = "MyESP";
const char* password = "01234567";

const char* serverIP = "192.168.4.1"; // IP Address of ESP32 Access Point

bool inRange(int val, int minimum, int maximum) {
  return ((minimum <= val) && (val <= maximum));
} 

String fetch_X_SensorValue() {
  WiFiClient client;

  // Connect to server
  if (!client.connect(serverIP, 80)) {
    Serial.println("Connection failed");
    return "--";
  }

  // Send HTTP request
  client.print(String("GET /Xacc HTTP/1.1\r\n") +
               "Host: " + serverIP + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for response
  while (!client.available()) {
    delay(100);
  }

  // Read response
  String response;
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  // Extract sensor value from response
  int valueIndex = response.indexOf("\r\n\r\n") + 4;
  String XsensorValue = response.substring(valueIndex);

  // Close connection
  client.stop();

  return XsensorValue;
}

String fetch_Y_SensorValue() {
  WiFiClient client;

  // Connect to server
  if (!client.connect(serverIP, 80)) {
    Serial.println("Connection failed");
    return "--";
  }

  // Send HTTP request
  client.print(String("GET /Yacc HTTP/1.1\r\n") +
               "Host: " + serverIP + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for response
  while (!client.available()) {
    delay(100);
  }

  // Read response
  String response;
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  // Extract sensor value from response
  int valueIndex = response.indexOf("\r\n\r\n") + 4;
  String YsensorValue = response.substring(valueIndex);

  // Close connection
  client.stop();

  return YsensorValue;
}

String fetch_Z_SensorValue() {
  WiFiClient client;

  // Connect to server
  if (!client.connect(serverIP, 80)) {
    Serial.println("Connection failed");
    return "--";
  }

  // Send HTTP request
  client.print(String("GET /Zacc HTTP/1.1\r\n") +
               "Host: " + serverIP + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for response
  while (!client.available()) {
    delay(100);
  }

  // Read response
  String response;
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  // Extract sensor value from response
  int valueIndex = response.indexOf("\r\n\r\n") + 4;
  String ZsensorValue = response.substring(valueIndex);

  // Close connection
  client.stop();

  return ZsensorValue;
}

void setup() {
  
  Serial.begin(115200);

  pinMode(BLED,OUTPUT);

  pinMode(M1_ENA,OUTPUT);
  pinMode(M1_ENB,OUTPUT);
  pinMode(M2_ENA,OUTPUT);
  pinMode(M2_ENB,OUTPUT);

  pinMode(M1_A1,OUTPUT);
  pinMode(M1_A2,OUTPUT);
  pinMode(M1_B1,OUTPUT);
  pinMode(M1_B2,OUTPUT);

  pinMode(M2_A1,OUTPUT);
  pinMode(M2_A2,OUTPUT);
  pinMode(M2_B1,OUTPUT);
  pinMode(M2_B2,OUTPUT);


  // Connect to ESP32 Access Point
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Access Point...");
  }
  Serial.println("Connected to Access Point");
  digitalWrite(BLED,HIGH);
  delay(100);
  }

  void loop() 
  {

    digitalWrite(M1_ENA,HIGH);
    digitalWrite(M1_ENB,HIGH);
    digitalWrite(M2_ENA,HIGH);
    digitalWrite(M2_ENB,HIGH);


  // Fetch sensor value from server
      
      int speed = 0;
      while(1){
          
          int X_sensorValue = (fetch_X_SensorValue()).toInt();
          int Y_sensorValue = (fetch_Y_SensorValue()).toInt();
          int Z_sensorValue = (fetch_Z_SensorValue()).toInt();    
          Serial.print("X Value: ");
          Serial.println(X_sensorValue);
          Serial.print("Y Value: ");
          Serial.println(Y_sensorValue);
          Serial.print("Z Value: ");
          Serial.println(Z_sensorValue);
          Serial.print("Speed: ");
          Serial.println(speed);
          //right
          while( inRange((fetch_X_SensorValue()).toInt(),-2,7) &&
                 inRange((fetch_Y_SensorValue()).toInt(),7,11) &&
                 inRange((fetch_Z_SensorValue()).toInt(),-2,2))
                {
                  speed = 150;
                
                  analogWrite(M1_ENA,speed);
                  analogWrite(M1_ENB,speed);
                  analogWrite(M2_ENA,speed);
                  analogWrite(M2_ENB,speed);

                  digitalWrite(M1_A1,HIGH);
                  digitalWrite(M1_A2,LOW);
                  digitalWrite(M1_B1,LOW);
                  digitalWrite(M1_B2,LOW);

                  digitalWrite(M2_A1,LOW);
                  digitalWrite(M2_A2,LOW);
                  digitalWrite(M2_B1,HIGH);
                  digitalWrite(M2_B2,LOW); 

                  int X_sensorValue = (fetch_X_SensorValue()).toInt();
                  int Y_sensorValue = (fetch_Y_SensorValue()).toInt();
                  int Z_sensorValue = (fetch_Z_SensorValue()).toInt();    
                  Serial.print("X Value: ");
                  Serial.println(X_sensorValue);
                  Serial.print("Y Value: ");
                  Serial.println(Y_sensorValue);
                  Serial.print("Z Value: ");
                  Serial.println(Z_sensorValue);
                  Serial.print("Speed: ");
                  Serial.println(speed);
                }
          //left
          while( inRange((fetch_Z_SensorValue()).toInt(),-2,7) &&
                 inRange((fetch_Y_SensorValue()).toInt(),-11,-7) &&
                 inRange((fetch_X_SensorValue()).toInt(),-2,2))
                {
                  speed = 150;
                  analogWrite(M1_ENA,speed);
                  analogWrite(M1_ENB,speed);
                  analogWrite(M2_ENA,speed);
                  analogWrite(M2_ENB,speed);

                  digitalWrite(M1_A1,LOW);
                  digitalWrite(M1_A2,LOW);
                  digitalWrite(M1_B1,HIGH);
                  digitalWrite(M1_B2,LOW);

                  digitalWrite(M2_A1,HIGH);
                  digitalWrite(M2_A2,LOW);
                  digitalWrite(M2_B1,LOW);
                  digitalWrite(M2_B2,LOW); 

                  int X_sensorValue = (fetch_Z_SensorValue()).toInt();
                  int Y_sensorValue = (fetch_Y_SensorValue()).toInt();
                  int Z_sensorValue = (fetch_X_SensorValue()).toInt();    
                  Serial.print("X Value: ");
                  Serial.println(X_sensorValue);
                  Serial.print("Y Value: ");
                  Serial.println(Y_sensorValue);
                  Serial.print("Z Value: ");
                  Serial.println(Z_sensorValue);
                  Serial.print("Speed: ");
                  Serial.println(speed); 
                }

          //stop
          while( inRange((fetch_X_SensorValue()).toInt(),-12,-7))        
          {
                  digitalWrite(M1_A1,LOW);
                  digitalWrite(M1_A2,LOW);
                  digitalWrite(M1_B1,LOW);
                  digitalWrite(M1_B2,LOW);

                  digitalWrite(M2_A1,LOW);
                  digitalWrite(M2_A2,LOW);
                  digitalWrite(M2_B1,LOW);
                  digitalWrite(M2_B2,LOW); 

                  int X_sensorValue = (fetch_X_SensorValue()).toInt();
                  int Y_sensorValue = (fetch_Y_SensorValue()).toInt();
                  int Z_sensorValue = (fetch_Z_SensorValue()).toInt();    
                  Serial.print("X Value: ");
                  Serial.println(X_sensorValue);
                  Serial.print("Y Value: ");
                  Serial.println(Y_sensorValue);
                  Serial.print("Z Value: ");
                  Serial.println(Z_sensorValue);
                  Serial.print("Speed: ");
                  Serial.println(speed);
          }

          //forward
          speed = abs(255 - (fetch_X_SensorValue()).toInt() *(255/10));
          if(speed > 150)
            speed = 150;

          analogWrite(M1_ENA,speed);
          analogWrite(M1_ENB,speed);
          analogWrite(M2_ENA,speed);
          analogWrite(M2_ENB,speed);

          digitalWrite(M1_A1,HIGH);
          digitalWrite(M1_A2,LOW);
          digitalWrite(M1_B1,HIGH);
          digitalWrite(M1_B2,LOW);

          digitalWrite(M2_A1,HIGH);
          digitalWrite(M2_A2,LOW);
          digitalWrite(M2_B1,HIGH);
          digitalWrite(M2_B2,LOW);

      }          
    }

  
  
  

  // Add any additional code if needed

