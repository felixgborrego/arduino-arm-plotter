/*
 * Join.h
 *
 *  Created on: 18 Dec 2017
 */

#ifndef JOIN_H_
#define JOIN_H_
#include <Servo.h>

class Join {
	Servo servo;
public:
	// Current angle (between 0 to 90 degree)
	double currentNormalizedAngle;
	double minPhysicalAngle;
	double maxPhysicalAngle;
	int pinAttached;

	/**
	 * minAngule: the angle for 0 degree
	 * maxAngle: the angle for 90 degree
	 */
	Join(double minAngule, double maxAngle, int pin);
	virtual ~Join();
	// Angle between 0 and 90 degrees
	void move(double normalizedAngle);
	void setup(double initialAngle);
private:
	double translateToPhysicalAngle(double normalizedAngle);
};

#endif /* JOIN_H_ */
