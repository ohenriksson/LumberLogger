# LumberLogger(WIP)
A simple wood moisture logger

## Get started:
* Put in your personal credentials in `Arduino/WiFiFirebase/staticVars.h` and copy it to `C:/staticVars.h` (you can change the location in `firebase.ino`).
* Open `Arduino/WiFiFirebase/wifiFirebase.ino` in the arduino IDE
* Connect and write to the board


## Todo:
* Sleep arduino between measurements.

## Hardware
* Board: Arduino Nano 33 IOT https://store.arduino.cc/arduino-nano-33-iot
* Half-Bridge: TI L293D
* Resistors: 10x22M, 1x3.3M
* Probes: 2 Screws, 8x35mm
* Misc: Case, breadboard and wires
* Power: Usb 5.0v, ?A
* Diodes: 1N4001 x 2


## Firebase Arduino WiFi101
https://github.com/mobizt/Firebase-Arduino-WiFi101

# Inspiration
* https://woodgears.ca/lumber/moisture_meter.html
* https://www.fpl.fs.fed.us/documnts/fplgtr/fplgtr06.pdf

