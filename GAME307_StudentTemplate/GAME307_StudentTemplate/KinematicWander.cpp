#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_, float maxSpeed_, float maxRotation_)
{
	character = character_;

	maxSpeed = maxSpeed_;
	maxRotation = maxRotation_;
}

KinematicSteeringOutput* KinematicWander::getSteering()
{
	result = new KinematicSteeringOutput();

	result->velocity = maxSpeed * GetOrientationVector();
	result->rotation = randomBinomial() * maxRotation;

	return result;
}

float KinematicWander::randomBinomial()
{
	// Includes max and min
	float randomNumber = rand() % (100 - 0 + 1) + 0;
	float randomInt = rand() % (1 - 0 + 1) + 0;

	if (randomInt == 0)
		randomNumber /= 100;
	else if (randomInt == 1)
		randomNumber /= -100;

	return randomNumber;
}

Vec3 KinematicWander::GetOrientationVector()
{
	Vec3 characterPos = character->getPos();
	Vec3 originPos = Vec3(0.0f, 0.0f, 0.0f);

	// sqrt((pX-qX)^2 + (pY-qY)^2)
	float unitlength = sqrt((characterPos.x - originPos.x) * (characterPos.x - originPos.x) +
		(characterPos.y - originPos.y) * (characterPos.y - originPos.y));

	// (x2 - x1, y2 - y1)
	Vec3 orientationVector;
	orientationVector = Vec3((characterPos.x - originPos.x) / unitlength, (characterPos.y - originPos.y) / unitlength, 0.0f);

	return orientationVector;
}
