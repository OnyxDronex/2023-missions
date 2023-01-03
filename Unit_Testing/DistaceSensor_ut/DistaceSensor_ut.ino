
#include "DistanceSensor.h"


DistSens = DistanceSensor();

void setup() {
  Serial.begin(9600);
  DistSens.Init();
}

void loop() {

	DistSens.StartMeasure();
	delay(100);
	float dist = DistSens.GetResult();
	Serial.print("The distance is:");
	Serial.println(dist);
}