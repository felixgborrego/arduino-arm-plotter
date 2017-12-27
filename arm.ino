/*
 * arm.ino
 *
 *  Created on: 18 Dec 2017
 */

#include <Servo.h>
#include "Join.h"
#include "Arm.h"
#include <string.h>

#define SHOLDER_SIGNAL_PIN 11
#define SHOULDER_PYSICAL_MIN_ANGLE_FOR_0 25
#define SHOULDER_PYSICAL_MIN_ANGLE_FOR_90 115
#define LEN_ARM_SEGMENT1 10.0
#define SHOLDER_INITIAL_ANGLE 90

#define ELBOW_SIGNAL_PIN 9
#define ELBOW_PYSICAL_MIN_ANGLE_FOR_0 20
#define ELBOW_PYSICAL_MIN_ANGLE_FOR_90 110
#define LEN_ARM_SEGMENT2 14
#define ELBOW_INITIAL_ANGLE 90

// Used by the draw methods (to avoid getting out of range)
#define MinX 8.0
#define MinY 4.0
#define MaxX 16.0
#define MaxY 16.0

double inReadInt1 = -1.0;
double inReadInt2 = -1.0;
char inReadChar = '0';

Join shoulder(SHOULDER_PYSICAL_MIN_ANGLE_FOR_0, SHOULDER_PYSICAL_MIN_ANGLE_FOR_90, SHOLDER_SIGNAL_PIN);
Join elbow(ELBOW_PYSICAL_MIN_ANGLE_FOR_0, ELBOW_PYSICAL_MIN_ANGLE_FOR_90, ELBOW_SIGNAL_PIN);
Arm arm(&shoulder, LEN_ARM_SEGMENT1, &elbow, LEN_ARM_SEGMENT2);


void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);

	shoulder.setup(SHOLDER_INITIAL_ANGLE);
	elbow.setup(ELBOW_INITIAL_ANGLE);
}

void loop() {
	readChar();

	// Initial position
	if(inReadChar == 'i')  {
		arm.move(MinX, MinY);
	}

	// print an n
	if(inReadChar == 'n')  {
		drawN();
		inReadChar = '0';
	}

	delay(2000);
}


void readChar() {
	Serial.println("inReadChar...");
	while (Serial.available()) {
		Serial.println("Data available...");
		String text = Serial.readString();
		Serial.println("Read: "+ text);
		inReadChar = text.charAt(0);
	    delay(2);  //slow looping to allow buffer to fill with next character
	  }
	//Serial.println("readReadInt read: " + String(inReadInt));
}

// Util method for debug
void readAngles(){
		while (Serial.available()) {
			Serial.println("Data available...");
			String text =   Serial.readString();
			Serial.println("Read: "+ text);
			int commaIndex = text.indexOf(',');
			inReadInt1 = text.substring(0, commaIndex).toDouble();
			inReadInt2 = text.substring(commaIndex + 1).toDouble();
		    delay(2);  //slow looping to allow buffer to fill with next character
		    Serial.println("angles read, a1: " + String(inReadInt1)+ " a2: "+  String(inReadInt2));
		}
}




/**
 * Simple path to draw a N.
 */
void drawN() {
	// Draw line from (0,0) to -> (0,10)
	for (double y = MinY; y < MaxY; y=y+0.2) {
		arm.move(MinX, y);
		delay(100);
	}
	double x;
	for (double delta = 0; MaxY-delta >= MinY; delta=delta+0.2) {
		x = MinX+(delta/2) ;
		arm.move(x, MaxY-delta);
		delay(100);
	}

	for (double y = MinY; y < MaxY; y=y+0.2) {
		arm.move(x, y);
		delay(100);
	}
}



