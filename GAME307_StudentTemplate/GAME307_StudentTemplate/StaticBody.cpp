#include "StaticBody.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering) {
	Body::Update(deltaTime);
	newOrientation();

	// Deal with the steering
	if (steering) {
		vel = steering->velocity;
		rotation = steering->rotation;
	}

	// Clamp the max speed
	if (VMath::mag(vel) > maxSpeed)
		vel = VMath::normalize(vel) * maxSpeed;

	// Clamp to max rotation
	if (rotation > maxRotation)
		rotation = maxRotation;
}

void StaticBody::newOrientation() {
	if (VMath::mag(vel) > 0.0f)
		orientation = atan2(-vel.y, vel.x);
}
