#include <Servo.h>

Servo servo1;
Servo servo2;

const int servo1Pin = 10;
const int servo2Pin = 11;
int lightVal;
int counter =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo1.write(0);
  servo2.write(0);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 
  lightVal = analogRead(A0);
  Serial.println(lightVal);
  delay(100);

  if(lightVal < 60){
    counter++;
    if(counter == 1){
      servo1.write(90);
      Serial.println("onee");
    }
    if(counter ==2){
      servo2.write(90);
      Serial.println("Twooo");
    }
    if(counter ==3){
      servo1.write(0);
      servo2.write(0);
      Serial.println("Bothhh");
      counter = 0;
    }
    delay(500);
  }
  
}


