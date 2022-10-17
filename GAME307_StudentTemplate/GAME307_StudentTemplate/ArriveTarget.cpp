#include "ArriveTarget.h"

ArriveTarget::ArriveTarget(KinematicBody* character_, Node* target_)
{
	character = character_;
	target = target_;
}

ArriveTarget::~ArriveTarget() {}

SteeringOutput* ArriveTarget::getSteering()
{
	/**/
	result = new SteeringOutput;

	direction = target->GetPos() - character->getPos();
	distance = VMath::mag(direction);

	if (distance < targetRadius) {
		return new SteeringOutput(Vec3(0, 0, 0), 0.0f);
		//return null;
	}

	if (distance > slowRadius)
		targetSpeed = maxSpeed;
	else
		targetSpeed = maxSpeed * distance / slowRadius;

	targetVelocity = direction;
	targetVelocity = VMath::normalize(targetVelocity);
	targetVelocity *= targetSpeed;

	result->linear = targetVelocity - character->getVel();
	result->linear /= timeToTarget;

	if (VMath::mag(result->linear) > maxAcceleration) {
		result->linear = VMath::normalize(result->linear);
		result->linear *= maxAcceleration;
	}

	result->angular = 0;

	//cout << "Target speed: " << targetSpeed << " || " << "Distance: " << distance << endl;
	//cout << "Position ghost: " << character->getPos().x << " || " << character->getPos().y << endl;

	return result;
}
