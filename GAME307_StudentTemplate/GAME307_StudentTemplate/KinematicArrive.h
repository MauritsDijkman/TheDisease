#ifndef  KINEMATIC_ARRIVE_H
#define  KINEMATIC_ARRIVE_H
#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"
using namespace MATH;

class KinematicArrive {
private:
	float radius;
	float timeToTarget;
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;
public:
	KinematicArrive(float radius_, float timeToTarget_, Body* character_, Body* target_);
	KinematicSteeringOutput* getSteering();
};
#endif