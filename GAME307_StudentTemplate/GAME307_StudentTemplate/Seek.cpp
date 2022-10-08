#include "Seek.h"

Seek::Seek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
}

Seek::~Seek() {}

SteeringOutput* Seek::getSteering()
{
	// Get direction to target
	result->linear = target->getPos() - character->getPos();

	// Accelerate along linear direction
	result->linear = VMath::normalize(result->linear) * character->getMaxAcceleration();

	float length = VMath::mag(target->getPos() - character->getPos());

	float radius = 3.0f;
	float timeToTarget = 0.5f;

	if (length < radius)
		return new SteeringOutput(Vec3(0, 0, 0), 0.0f);

	result->linear /= timeToTarget;

	result->angular = 0;
	return result;
}
