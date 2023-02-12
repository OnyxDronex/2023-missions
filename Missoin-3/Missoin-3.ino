#include <Servo.h>

Servo servo1;
Servo servo2;

const int SERVO_1_PIN = 10;
const int SERVO_2_PIN = 11;
const int TOLRANCE = 40;
const int FLASHLIGHT_VAL= 60;
int updateDelay = 200;
int counter = 0;
int lightVal;
int roomLightVal;


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  servo1.write(0);
  servo2.write(0);
  Serial.begin(9600);
  roomLightVal = analogRead(A0);

}

void loop() {
  // put your main code here, to run repeatedly:

  updateLightVal();
  Serial.println(lightVal);
  if (lightVal < FLASHLIGHT_VAL) {
    counter++;
    if (counter == 1) {
      servo1.write(90);
      Serial.println("onee");
    }
    if (counter == 2) {
      servo2.write(90);
      Serial.println("Twooo");
    }
    if (counter == 3) {
      servo1.write(0);
      servo2.write(0);
      Serial.println("Bothhh");
      counter = 0;
    }
    waitForNormalLight();
  }
}

void waitForNormalLight() {
  while (lightVal  < roomLightVal - TOLRANCE) {
    updateLightVal();
    Serial.println("waiting...");
  }
}

void updateLightVal() {
  lightVal = analogRead(A0);
  delay(updateDelay);
}
