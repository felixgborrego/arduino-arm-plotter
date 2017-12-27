/*
 * Arm.h
 *
 *  Created on: 20 Dec 2017
 */

#ifndef ARM_H_
#define ARM_H_
#include "Join.h"

typedef struct {
    double a1, a2;
} Angles;

class Arm {
	Join* shoulder;
	Join* elbow;
	double len1; // upper arm length
	double len2; // 	forearm length
	double currentX;
	double currentY;
public:
	Arm(Join* _shoulder, double _len1, Join* _elbow, double _len2);
	virtual ~Arm();
	void move(double x, double y);
private:

	double lawOfCosines(double a, double b, double c);
	double distance(double x, double y);
	Angles toAngles(double x, double y);
	double toDeg(double rad);
};

#endif /* ARM_H_ */
