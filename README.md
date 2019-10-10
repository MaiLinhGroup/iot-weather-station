IoT Weather Station
===========

## Hardware

- MCU [Wemos D1 mini](https://wiki.wemos.cc/products:d1:d1_mini)
- absolute barometric pressure sensor [GY BMP 280](https://components101.com/sensors/gy-bmp280-module)

## Software

- IDE of your choice
- Library for the sensor by [Adafruit](https://github.com/adafruit/Adafruit_BMP280_Library)

## Getting Started

- clone the code
```console
foo@bar:~$ git clone git@github.com:MaiLinhGroup/iot-weather-station.git
```

- open `src/main.h` and replace the default values for WiFi with own WiFi credentials
- depending on which IDE *(please check out the respective documentation)*, compile and flash the code to the board
- open a serial monitor, if needed set `baud_rate: 115200` , and press the reset button on the MCU to reboot the MCU
- after reboot the MCU will display its `IP address` in the serial monitor, enter/open this address in any browser to see weather station information


## Note

- [idea for the project and great source of further explanation](https://lastminuteengineers.com/bme280-esp8266-weather-station/)
- [examples for ESP8266 with Arduino](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples)