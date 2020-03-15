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

void mqtt_publish_sensor_data() {
  char tempString[8];
  char humString[8];
  char pressString[8];
  // char gasString[8];
  
  dtostrf(temperature, 1, 2, tempString);
  mqttClient.publish("home/1/temperature", tempString);
  
  dtostrf(humidity, 1, 2, humString);
  mqttClient.publish("home/1/humidity", humString);
  
  dtostrf(pressure, 1, 2, pressString);
  mqttClient.publish("home/1/pressure", pressString);

  // dtostrf(gasSensorValue, 1, 2, gasString);
  mqttClient.publish("home/1/gas", String(gasSensorValue).c_str());
}

void loop() {
  // main code here, run in an endless loop:
  if(!mqttClient.connected()){
    mqtt_reconnect();
  }
  mqttClient.loop();

  read_barometric_sensor();
  read_gas_sensor();
  mqtt_publish_sensor_data();
}

void read_barometric_sensor() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
}


void read_gas_sensor() {
  gasSensorValue = analogRead(GAS_IN_PIN); // read analog input pin 0
  delay(1000);
}