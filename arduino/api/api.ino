//#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <FreeRTOS.h>
  
//#include <Adafruit_BME280.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_NeoPixel.h>

//config red
IPAddress local_IP(192, 168, 0, 15);
//IPAddress local_IP(192, 168, 0, 177);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
const char *SSID = "Enganchate a esta 8llllllllD";
const char *PWD = "S3b4st14n19961";

#define LED 2
#define PIN21 T0
#define PIN22 T4
#define PIN23 T5
  
// Web server running on port 80

WebServer server(80);
  

  
// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];
  
// env variable
int temperature;
int humidity;
int pressure;
  
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);
   
  WiFi.begin(SSID, PWD);
   
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    // we can even make the ESP32 to sleep
  }
  
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}
  
void create_json(char *tag, float value, char *unit) {  
  jsonDocument.clear();  
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);
}
  
void add_json_object(char *tag, float value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit; 
}
 
void read_sensor_data(void * parameter) {
   for (;;) {
     //temperature = analogRead(21);
     //humidity = analogRead(22);
     //pressure = analogRead(23); 
     temperature = touchRead(PIN21);
     humidity = touchRead(PIN22);
     pressure = touchRead(PIN23);
     
     //Serial.println(temperature);
     //temperature = random(1,100);
     //humidity = random(1,100);
     //pressure = random(1,100);
     
     //Serial.println("temperature");
     //Serial.println(temperature);
     //Serial.println("humidity");
     //Serial.println(humidity);
     //Serial.println("pressure");
     //Serial.println(pressure);
     Serial.println("Read sensor data");
  
     // delay the task
     //vTaskDelay(30000 / portTICK_PERIOD_MS);
     vTaskDelay(2500);
   }
}
void getServer() {
  Serial.println("Get server in / ");
  create_json("Api esp32 on fire",1.1,"/");
  server.send(200, "application/json", buffer);
}
  
void getTemperature() {
  Serial.println("Get temperature");
  create_json("temperature", temperature, "°C");
  server.send(200, "application/json", buffer);
}
  
void getHumidity() {
  Serial.println("Get humidity");
  create_json("humidity", humidity, "%");
  server.send(200, "application/json", buffer);
}
  
void getPressure() {
  Serial.println("Get pressure");
  create_json("pressure", pressure, "mBar");
  server.send(200, "application/json", buffer);
}
  
void getEnv() {
  Serial.println("Get env");
  jsonDocument.clear();
  add_json_object("temperature", temperature, "°C");
  add_json_object("humidity", humidity, "%");
  add_json_object("pressure", pressure, "mBar");
  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}

void handlePostSprinkler() {
  Serial.println("POST Sprinkler");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (server.hasArg("plain") == false) {
    //handle error here
    Serial.print("Post error");    
  }else{
   // Respond to the client
  server.send(200, "application/json", "{\"status\":\"200\"}"); 
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);
  Serial.print("body: ");
  Serial.println(body);
  for(int i=0;i<3; i++){
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    }
  }
}

void handlePostBomb() {
  Serial.println("POST Bomb");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (server.hasArg("plain") == false) {
    //handle error here
    Serial.print("Post error");    
  }else{
   // Respond to the client
  server.send(200, "application/json", "{\"status\":\"200\"}"); 
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);
  Serial.print("body: ");
  Serial.println(body);
  for(int i=0;i<5; i++){
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    }  
  }
}

void handlePostValve() {
  Serial.println("POST Valve");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (server.hasArg("plain") == false) {
    //handle error here
    Serial.print("Post error");    
  }else{
   // Respond to the client
  server.send(200, "application/json", "{\"status\":\"200\"}"); 
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);
  Serial.print("body: ");
  Serial.println(body);
  for(int i=0;i<7; i++){
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    }
  }
}
  
// setup API resources
void setup_routing() {
  server.on("/",getServer);
  server.on("/temperature", getTemperature);
  server.on("/pressure", getPressure);
  server.on("/humidity", getHumidity);
  server.on("/env", getEnv);
  server.on("/sprinkler", HTTP_POST, handlePostSprinkler);
  server.on("/bomb", HTTP_POST, handlePostBomb);
  server.on("/valve", HTTP_POST, handlePostValve);
  
  
  // start server
  server.begin();
}
 
 
void setup_task() {
  xTaskCreate(
    read_sensor_data,    
    "Read sensor data",  
    1000,            
    NULL,            
    1,               
    NULL            
  );
}
  
void setup() {
   Serial.begin(115200);
   pinMode(LED,OUTPUT);
   //pinMode(PIN21,INPUT);
   //pinMode(PIN22,INPUT);
   //pinMode(PIN23,INPUT);
 
  connectToWiFi();
  setup_task();
  setup_routing();  
  // Initialize Neopixel
  //pixels.begin();
}
  
void loop() {
  server.handleClient();  
}
