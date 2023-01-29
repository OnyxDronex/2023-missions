#include "SoftwareSerial.h"
#include <Adafruit_NeoPixel.h>
#define PIN A2
#define NUMPIXELS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

SoftwareSerial myBlue(4, 5);

void setup() {
  myBlue.begin(9600);
  pixels.begin();
  Serial.begin(9600);

}

void loop() {
  sendNumbers();
  printInput();
  turnOnLight(bluetoothAsciiAOutputToNumber());
}


void sendNumbers() {
  for (int i = 0; i < 10 ; i++) {
    myBlue.println(i);
    delay(1000);
  }
}

void printInput() {
  while (myBlue.available() == 0 ) {
  }
  Serial.println((char)myBlue.read());
}

int bluetoothAsciiAOutputToNumber() {
  int numOfLightToTurnOn;
  while (myBlue.available() == 0 ) {
  }
  delay(100);
  if (myBlue.available()  >= 2) {
    byte tens = myBlue.read();
    byte unit = myBlue.read();
    tens = (tens - '0') * 10;
    unit = unit - '0';
    numOfLightToTurnOn = tens + unit;

  } else {
    numOfLightToTurnOn = myBlue.read() - '0';
  }
  return numOfLightToTurnOn;

}

void turnOnLight(int leds) {
  pixels.clear();
  for (int i = 0; i < leds; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 100, 255));
    pixels.show();
  }
}
