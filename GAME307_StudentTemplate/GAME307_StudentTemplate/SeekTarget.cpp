#include "SeekTarget.h"

SeekTarget::SeekTarget(Body* character_, Node* target_)
{
	character = character_;
	target = target_;
}

SeekTarget::~SeekTarget() {}

SteeringOutput* SeekTarget::getSteering()
{
	// Get direction to target
	result->linear = target->GetPos() - character->getPos();

	// Accelerate along linear direction
	result->linear = VMath::normalize(result->linear) * character->getMaxAcceleration();

	result->angular = 0;
	return result;
}
