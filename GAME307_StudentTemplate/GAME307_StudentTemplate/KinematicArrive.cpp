#include "KinematicArrive.h"
#include <SteeringOutput.h>

KinematicArrive::KinematicArrive(float radius_, float timeToTarget_, Body* character_, Body* target_)
{
	radius = radius_;
	timeToTarget = timeToTarget_;

	result = new KinematicSteeringOutput();
	character = character_;
	target = target_;
}

//SteeringOutput* KinematicArrive::getSteering() {
KinematicSteeringOutput* KinematicArrive::getSteering() {
	// Get the direction to the target
	result->velocity = target->getPos() - character->getPos();

	float length = VMath::mag(character->getVel());

	//printf(length, "%f");

	if (length < radius)
		return result;

	// Slow down when near the target
	result->velocity /= timeToTarget;

	// Clamp the max speed
	if (length > character->getMaxSpeed()) {
		result->velocity = VMath::normalize(result->velocity);
		result->velocity *= character->getMaxSpeed();
	}

	// Set the orientation/rotation
	result->rotation = 0.0f;

	// Return result
	return result;
}
