#define echoPin 5
#include <Adafruit_NeoPixel.h>
#define PIN 12
#define NUM_LEDS 24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  strip.begin();
  strip.setBrightness(50); 
  strip.show();
}

void loop() {
  distance = getCurrentDistance();
  turnOnLightByDistance(distance);
}

void red() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
  }

}

void blue() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
    strip.show();
  }
}

void green() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
    strip.show();
  }
}

void purple() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 255));
    strip.show();
  }
}

void turnOnLightByDistance(int distance) {
  if (distance < 100) {
    red();
  }
  if (distance > 100 && distance < 200) {
    blue();
  }
  if (distance > 200 && distance < 300) {
    green();
  }
  if (distance > 300) {
    purple();
  }
}

int getCurrentDistance() {
  word duration, distance;
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;
  Serial.print("distance = ");
  Serial.println(distance);
  delay(50);
  return distance;
}

