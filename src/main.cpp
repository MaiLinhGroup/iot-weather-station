#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "main.h"

// declare function signatures
void read_barometric_sensor();

Adafruit_BME280 bme;
float temperature, humidity, pressure, altitude;

const char* ssid = MY_SSID;
const char* pwd = MY_PSWD;
const char* mqtt_server = MQTT_BROKER_ADDR;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup() {
  // put your setup code here, run once before main loop:
  Serial.begin(115200);
  delay(100);  

  Serial.println(F("Weather Station setup."));

  // setup sensor
  while (!bme.begin())
  {
    Serial.println(F("No sensor found, please check wiring!"));
    delay(1500); // wait for 1.5s
  }
  Serial.println(F("Sensor GYBMEP BME/BMP280 found!"));
  
  // setup wifi
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected...!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  // setup mqtt
  mqttClient.setServer(mqtt_server, 1883);
}

void loop() {
  // main code here, run in an endless loop:
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    mqttClient.publish("test", msg);
  }
}

void read_barometric_sensor() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
}