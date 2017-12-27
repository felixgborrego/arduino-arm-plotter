/*
 * Arm.cpp
 *
 *  Created on: 20 Dec 2017
 */
#include "Arm.h"
#include <math.h>
#include <Arduino.h>
Arm::Arm(Join* _shoulder, double _len1, Join* _elbow, double _len2) {
	shoulder = _shoulder;
	len1 = _len1;
	elbow = _elbow;
	len2 = _len2;
	currentX = -1;
	currentY = -1;
}

Arm::~Arm() {
}


/**
 * The law of cosines, transformed so that C is the unknown.
 * The names of the sides and angles correspond to the standard names in mathematical writing.
 * Later, we have to map the sides and angles from our scenario to a, b, c, and C, respectively.
 */
double Arm::lawOfCosines(double a, double b, double c) {
	return acos((a*a + b*b - c*c) / (2.0 * a * b));
}

/**
 * The distance from (0,0) to (x,y). HT to Pythagoras.
 */
double Arm::distance(double x, double y) {
	return sqrt(x*x + y*y);
}

/**
 * Calculating the two joint angles for given x and y.
 *  - First, get the length of line dist
 *  - Calculating angle D1 is trivial. Atan2 is a modified arctan() function that returns unambiguous results.
 *  - D2 can be calculated using the law of cosines where a = dist, b = len1, and c = len2.
 *  - Then A1 is simply the sum of D1 and D2.
 *  - A2 can also be calculated with the law of cosine, but this time with a = len1, b = len2, and c = dist.
 */
Angles Arm::toAngles(double x, double y) {
	Angles angles;
	double dist = distance(x, y);
	double d1 = atan2(y, x);

	double d2 = lawOfCosines(dist, len1, len2);
	//Serial.println("len1: "+String(len1)+", len2: "+String(len2)+ ", dist: "+String(dist) + ", d1: "+ String(d1) + ", d2: " + d2);

	double a1Rad = d1 + d2;
	double a2Rad = lawOfCosines(len1, len2, dist);
	angles.a1 = toDeg(a1Rad);
	angles.a2 = toDeg(a2Rad);
	//Serial.println("a1Rad: "+String(a1Rad) + ", a2Rad: "+String(a1Rad) + ",a1: "+ String(angles.a1) + ", a2: " + String(angles.a2) );
	return angles;
}


double Arm::toDeg(double rad) {
	return rad * 180.0 / M_PI;
}

void Arm::move(double x, double y) {
	if(x!= currentX || y != currentY) {
		currentX = x;
		currentY = y;
		//Serial.println("Move to x="+ String(x) + ", y=" +String(y));
		Angles angles = toAngles(x,y);
		shoulder->move(angles.a1);
		elbow->move(angles.a2);
	}
}
