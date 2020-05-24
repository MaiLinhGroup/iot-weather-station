IoT Weather Station
===========

## Hardware

- MCU [Wemos D1 mini](https://wiki.wemos.cc/products:d1:d1_mini)
- absolute barometric pressure sensor [GY BME 280](https://protosupplies.com/product/gy-bme280-pressure-humidity-temperature-sensor-module/)

## Software

- IDE of your choice (Recommendation is [VSCode with Platformio](https://platformio.org/install/ide?install=vscode))
## Dependencies
- Library for the temperature sensor by [Adafruit](https://github.com/adafruit/Adafruit_BME280_Library)(there are alternatives available though)
- Library for [Pub-Sub](https://github.com/knolleary/pubsubclient) over MQTT
- Library for the Air Quality sensor [MQ135](https://platformio.org/lib/show/2537/TroykaMQ)

## Getting Started

- clone the code
```console
foo@bar:~$ git clone git@github.com:MaiLinhGroup/iot-weather-station.git
```

- open `src/main.h` and replace the default values for WiFi with own WiFi credentials
- depending on which IDE *(please check out the respective documentation)*, resolve the aforementioned dependencies, compile and flash the code to the board
- open a serial monitor, if needed set `baud_rate: 115200` , and press the reset button on the MCU to reboot the MCU
- after reboot the MCU will display its `IP address` in the serial monitor, enter/open this address in any browser to see weather station information


## Note

- [idea for the project and great source of further explanation](https://lastminuteengineers.com/bme280-esp8266-weather-station/)
- [examples for ESP8266 with Arduino](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples)
