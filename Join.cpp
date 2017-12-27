/*
 * Join.cpp
 *
 *  Created on: 18 Dec 2017
 */

#include "Arduino.h"
#include "Join.h"

Join::Join(double minAngule, double maxAngle, int pin) {
	maxPhysicalAngle= maxAngle;
	minPhysicalAngle = minAngule;
	currentNormalizedAngle = -1;
	pinAttached = pin;
}

Join::~Join() {
}

void Join::setup(double initialAngle) {
	Serial.println("New Join created. minPhysicalAngle:" + String(minPhysicalAngle) + ", maxPhysicalAngle:  " + String(maxPhysicalAngle));
	servo.attach(pinAttached);
	move(initialAngle);
}

void Join::move(double normalizedAngle) {
	if (normalizedAngle == currentNormalizedAngle) {
		//Serial.println("Already at angle "+ String(currentNormalizedAngle));
		return;
	}


	double physicalAngle = translateToPhysicalAngle(normalizedAngle);
	Serial.println("Moving from "+ String(currentNormalizedAngle)+" to " + String(normalizedAngle) + "[Physical Angle: "+ String(physicalAngle)+"]");
	currentNormalizedAngle = normalizedAngle;

	servo.write((int)physicalAngle);
	delay(40);
}


double Join::translateToPhysicalAngle(double normalizedAngle) {
	int angle = map(normalizedAngle*100, 0, 90* 100, minPhysicalAngle*100, maxPhysicalAngle * 100);
	return angle/100;
}

