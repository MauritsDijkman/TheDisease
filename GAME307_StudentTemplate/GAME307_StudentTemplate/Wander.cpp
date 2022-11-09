#include "Wander.h"

Wander::Wander(KinematicBody* character_)
{
	character = character_;
	angle = character->getOrientation();
}

Wander::~Wander() {}

SteeringOutput* Wander::getSteering()
{
	result = new SteeringOutput;

#pragma region Velocity
	Vec3 velocity;
	velocity = maxSpeed * GetOrientationVector(character);

	// Calculate the difference between current velocity and the orientation velocity (will give the linear acceleration)
	Vec3 differenceVelocity = character->getVel() - velocity;
	result->linear = VMath::normalize(differenceVelocity) * character->getMaxAcceleration();
#pragma endregion

#pragma region Orientation
	float diff = randomBinomial() * (M_PI / 4.0f);
	angle += diff;

	result->angular = (diff / abs(diff)) * character->getMaxAngular();
#pragma endregion

	// Debug
	cout << "Wander velocity: ";
	result->linear.print();

	cout << "Wander rotation: " << result->angular << endl;

	return result;
}

Vec3 Wander::GetOrientationVector(KinematicBody* actor_)
{
	return Vec3(cos(actor_->getOrientation()), sin(actor_->getOrientation()), 0.0f);
}

float Wander::randomBinomial()
{
	// Includes max and min
	float randomNumber = 0;

	while (randomNumber <= 0.0000001f)
	{
		randomNumber = rand() % (100 - 0 + 1) + 0;
		float randomInt = rand() % (1 - 0 + 1) + 0;

		if (randomInt == 0)
			randomNumber /= 100;
		else if (randomInt == 1)
			randomNumber /= -100;
	}

	cout << "Random number: " << randomNumber << endl;
	return randomNumber;
}
