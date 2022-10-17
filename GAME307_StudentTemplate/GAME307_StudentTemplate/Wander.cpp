#include "Wander.h"

Wander::Wander(KinematicBody* character_)
{
	character = character_;
}

Wander::~Wander() {}

SteeringOutput* Wander::getSteering()
{
	result = new SteeringOutput;

	return result;
}
