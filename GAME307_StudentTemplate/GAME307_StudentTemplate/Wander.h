#ifndef WANDER_H
#define WANDER_H

#include "Vector.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Node.h"

using namespace MATH;
using namespace std;

class Wander :
	public SteeringBehaviour
{
private:
	KinematicBody* character;

	float maxSpeed = 3.0f;
	float maxRotationSpeed = 50.0f;


	// The radius and forward offset of the wander circle
	float wanderOffset;
	float wanderRadius;

	// The maximum rate at which the wander orientation can change
	float wanderRate;

	// The current orientation of the wander target
	float wanderOrientation;

	// The maximum acceleration of the character
	float maxAcceleration;

	float angle;

	Vec3 GetOrientationVector(KinematicBody* actor_);
	float randomBinomial();

public:
	Wander(KinematicBody* character_);
	virtual ~Wander();

	SteeringOutput* getSteering();
};

#endif // !WANDER_H
