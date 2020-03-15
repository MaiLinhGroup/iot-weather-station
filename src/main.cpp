#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "main.h"

// declare function signatures
void read_barometric_sensor();
void read_gas_sensor();

Adafruit_BME280 bme;
float temperature, humidity, pressure;

int prevConductivity = 0;
int prevGas = -1;
int gasSensorValue;

const char* ssid = MY_SSID;
const char* pwd = MY_PSWD;
const char* mqttServer = MQTT_BROKER_ADDR;
const int mqttPort = MQTT_PORT;

WiFiClient espClient;
PubSubClient mqttClient(espClient);


void setup() {
  // put your setup code here, run once before main loop:
  Serial.begin(115200);
  delay(100);  

  Serial.println(F("Weather Station setup."));

  // setup sensor
  while (!bme.begin(BME280_ADDRESS_ALTERNATE))
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
  mqttClient.setServer(mqttServer, mqttPort);
}

void mqtt_reconnect() {
  // Loop until reconnected
  while (!mqttClient.connected()) {
 
    if (mqttClient.connect("ESP8266Client")) {
 
      // Serial.println("connected");
 
    } else {
 
      Serial.println("Connecting to MQTT...");
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
 
    }
  }
}

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
void mqtt_hello_world() {
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    if (mqttClient.publish("test/hello/world", msg)) {
      Serial.print("Publish message: ");
      Serial.println(msg);
    }

  } 
}

void mqtt_publish_sensor_data() {
  char tempString[8];
  char humString[8];
  char pressString[8];
  // char gasString[8];
  
  dtostrf(temperature, 1, 2, tempString);
  mqttClient.publish("esp8266/temperature", tempString);
  
  dtostrf(humidity, 1, 2, humString);
  mqttClient.publish("esp8266/humidity", humString);
  
  dtostrf(pressure, 1, 2, pressString);
  mqttClient.publish("esp8266/pressure", pressString);

  // dtostrf(gasSensorValue, 1, 2, gasString);
  mqttClient.publish("esp8266/gas", String(gasSensorValue).c_str());
}

void loop() {
  // main code here, run in an endless loop:
  if(!mqttClient.connected()){
    mqtt_reconnect();
  }
  mqttClient.loop();

  read_barometric_sensor();
  // Serial.println("---");
  read_gas_sensor();
  mqtt_publish_sensor_data();
}

void read_barometric_sensor() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  // Serial.println(temperature);
  // Serial.println(humidity);
  // Serial.println(pressure);
}


void read_gas_sensor() {
  gasSensorValue = analogRead(0); // read analog input pin 0
  // Serial.println(gasSensorValue, DEC);
  delay(1000);
}