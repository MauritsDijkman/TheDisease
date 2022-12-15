#ifndef STEER_TO_TARGET_H
#define STEER_TO_TARGET_H

#include "Vector.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Node.h"

using namespace MATH;
using namespace std;

class SteerToTarget : public SteeringBehaviour
{
private:
	KinematicBody* character;
	Vec3 target;

	float maxAcceleration = 1.0f;
	float maxSpeed = 2.0f;
	float targetRadius = 0.2f;
	float slowRadius = 3.0f;
	float timeToTarget = 0.01f;

	Vec3 direction;
	float distance;
	float targetSpeed;
	Vec3 targetVelocity;

public:
	SteerToTarget(KinematicBody* character_, Vec3 target_);
	virtual ~SteerToTarget();
	SteeringOutput* getSteering();
};

#endif // !STEER_TO_TARGET_H
