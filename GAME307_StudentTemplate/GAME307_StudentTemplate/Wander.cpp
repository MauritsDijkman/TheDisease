#include "Wander.h"

Wander::Wander(KinematicBody* character_)
{
	character = character_;
}

Wander::~Wander() {}

SteeringOutput* Wander::getSteering()
{
	result = new SteeringOutput;

	Vec3 velocity;
	velocity = maxSpeed * GetOrientationVector();
	// Calculate the difference between current velocity and the orientation velocity (will give the linear acceleration)
	Vec3 differenceVelocity = character->getVel() - velocity;
	result->linear = VMath::normalize(differenceVelocity) * character->getMaxAcceleration();

	float randomRotation;
	randomRotation = randomBinomial();
	// Calculate the difference between the current rotation and the new one (will give the angular acceleration)
	float differenceRotation = character->getRotation() - randomRotation;
	result->angular = differenceRotation > character->getMaxAcceleration() ? character->getMaxAcceleration() : differenceRotation;

	// Debug
	cout << "Wander velocity: ";
	result->linear.print();

	cout << "Wander rotation: " << result->angular << endl;

	return result;
}

Vec3 Wander::GetOrientationVector()
{
	Vec3 characterPos = character->getPos();
	Vec3 originPos = Vec3(0.0f, 0.0f, 0.0f);

	// sqrt((pX-qX)^2 + (pY-qY)^2)
	float unitlength = sqrt((characterPos.x - originPos.x) * (characterPos.x - originPos.x) +
		(characterPos.y - originPos.y) * (characterPos.y - originPos.y));

	// (x2 - x1, y2 - y1)
	Vec3 orientationVector;
	orientationVector = Vec3((characterPos.x - originPos.x) / unitlength, (characterPos.y - originPos.y) / unitlength, 0.0f);

	cout << "Orientation Vector: " << orientationVector << endl;

	return orientationVector;
}

float Wander::randomBinomial()
{
	// Includes max and min
	float randomNumber = rand() % (100 - 0 + 1) + 0;
	float randomInt = rand() % (1 - 0 + 1) + 0;

	if (randomInt == 0)
		randomNumber /= 100;
	else if (randomInt == 1)
		randomNumber /= -100;

	cout << "Random number: " << randomNumber << endl;

	return randomNumber;
}
