#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_, float maxSpeed_, float maxRotation_) {
	result = new KinematicSteeringOutput();

	character = character_;
	maxSpeed = maxSpeed_;
	maxRotation = maxRotation_;
}

KinematicSteeringOutput* KinematicWander::getSteering() {
	result->velocity = maxSpeed * GetOrientationVector();

	result->rotation = randomBinomial() * maxRotation;

	return result;
}

float KinematicWander::randomBinomial() {

	// Includes max and min
	float randomNumber = rand() % (100 - 0 + 1) + 0;
	float randomInt = rand() % (1 - 0 + 1) + 0;

	if (randomInt == 0)
		randomNumber /= 100;
	else if (randomInt == 1)
		randomNumber /= -100;

	return randomNumber;
}

Vec3 KinematicWander::GetOrientationVector() {
	float orientation = character->getOrientation();



	return Vec3();
}
