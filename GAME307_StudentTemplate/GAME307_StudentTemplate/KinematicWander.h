#ifndef  KINEMATIC_WANDER_H
#define  KINEMATIC_WANDER_H
#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicWander {

private:
	KinematicSteeringOutput* result;
	Body* character;
	float maxSpeed;
	float maxRotation;
	float randomBinomial();
	Vec3 GetOrientationVector();

public:
	KinematicWander(Body* character_, float maxSpeed_, float maxRotation_);
	KinematicSteeringOutput* getSteering();
};
#endif