#include "Wander.h"

Wander::Wander(KinematicBody* character_)
{
	character = character_;
}

Wander::~Wander() {}

SteeringOutput* Wander::getSteering()
{
	result = new SteeringOutput;

	Vec3 test = GetOrientationVector(character);

	/**
	// Update the wander orientation
	wanderOrientation += randomBinomial() * wanderRate;

	// Calculate the combined target orientation
	float targetOrientation = wanderOrientation + character->getOrientation();

	// Calculate the center of the wander circle
	Vec3 target = character->getPos() + wanderOffset * GetOrientationVector();

	// Calculate the target location
	//target += wanderRadius * targetOrientation;
	target += wanderRadius * Vec3(0, 0, 0);

	result->linear = maxAcceleration * GetOrientationVector();
	cout << "Result.Linear: ";
	result->linear.print();
	/**/


	/**
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
	/**/

	return result;
}

Vec3 Wander::GetOrientationVector(KinematicBody* actor_)
{
	-sin(actor_->getOrientation());
	cos(actor_->getOrientation());

	/**/
	Vec3 distance;
	distance.x = 3 * cos(actor_->getOrientation());
	distance.y = 0.0f;
	distance.z = 3 * sin(actor_->getOrientation());

	float directionVector = sqrt((distance.x * distance.x) + (distance.z * distance.z));

	cout << "DirectionVector: " << directionVector << endl;
	/**/


	/**
	Vec3 characterPos = character->getPos();
	Vec3 originPos = Vec3(0.0f, 0.0f, 0.0f);

	// sqrt((pX-qX)^2 + (pY-qY)^2)
	float unitlength = sqrt((characterPos.x - originPos.x) * (characterPos.x - originPos.x) +
		(characterPos.y - originPos.y) * (characterPos.y - originPos.y));

	// (x2 - x1, y2 - y1)
	Vec3 orientationVector;
	orientationVector = Vec3((characterPos.x - originPos.x) / unitlength, (characterPos.y - originPos.y) / unitlength, 0.0f);

	cout << "Orientation Vector: ";
	orientationVector.print();
	/**/

	return Vec3();
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
