#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

//PIN declaration
#define ECHO_PIN 3
#define TXD_PIN 4
#define RXD_PIN 5
#define LED_PIN 6
#define LAZER_PIN 2

//Delays
#define RING_LED_DELAY 100
#define DISTANCE_DELAY 100
#define RING_LED_DELAY 100

//etc
#define RING_LED_NUM 48
#define RED 255
#define BLUE 255
#define GREEN 255
#define DISTANCE_TO_ACTIVATE 300

//objects?
SoftwareSerial myBlue(TXD_PIN, RXD_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(RING_LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

//delayshit
long currentMillis;

long ledPreviousMillis;
long distancePreviousMillis;

int distance;
int currentLed = 0;



void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LAZER_PIN, OUTPUT);
  Serial.begin(9600);
  myBlue.begin(9600);
}

void loop() {
  mainLoop();
}

int getCurrentDistance() {
  word duration, distance;
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58;
  Serial.print("distance = ");
  Serial.println(distance);
  return distance;
}

void sendDistance() {
  if (currentMillis - distancePreviousMillis >= RING_LED_DELAY) {
    distancePreviousMillis = currentMillis;
    myBlue.println(getCurrentDistance());
  }
}

void turnOnLazer() {
  digitalWrite(LAZER_PIN, HIGH);
}

void turnOffLazer() {
  digitalWrite(LAZER_PIN, LOW);
}

void turnOnRings() {
  if (currentMillis - ledPreviousMillis >= RING_LED_DELAY) {
    ledPreviousMillis = currentMillis;
    currentLed++;
    if (currentLed > RING_LED_NUM) {
      currentLed = 0;
    }
    pixels.setPixelColor(currentLed, pixels.Color(RED, GREEN, BLUE));
    pixels.show();
  }
}

void updateTime() {
  currentMillis = millis();
}


void mainLoop() {
  char in;
  updateTime();

  if (myBlue.available() == 0) {
     in = (char)myBlue.read();
  }

  if (in == 'd') {
    sendDistance();
  }

  if (getCurrentDistance() > DISTANCE_TO_ACTIVATE) {
    turnOnRings();
    turnOnLazer();
  }
}
