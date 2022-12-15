#include "SteerToTarget.h"

SteerToTarget::SteerToTarget(KinematicBody* character_, Vec3 target_)
{
	character = character_;
	target = target_;
}

SteerToTarget::~SteerToTarget() {}

SteeringOutput* SteerToTarget::getSteering()
{
	result = new SteeringOutput;
	direction = target - character->getPos();
	distance = VMath::mag(direction);

	if (distance < targetRadius)
		return new SteeringOutput(Vec3(0, 0, 0), 0.0f);

	if (distance > slowRadius)
		targetSpeed = maxSpeed;
	else
		targetSpeed = maxSpeed * distance / slowRadius;

	targetVelocity = direction;
	targetVelocity = VMath::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	result->linear = targetVelocity - character->getVel();
	result->linear /= timeToTarget;

	if (VMath::mag(result->linear) > maxAcceleration)
	{
		result->linear = VMath::normalize(result->linear);
		result->linear *= maxAcceleration;
	}

	result->angular = 0;
	return result;
}