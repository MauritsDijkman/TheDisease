#ifndef WANDER_H
#define WANDER_H

#include "Vector.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Node.h"

using namespace MATH;
using namespace std;

class Wander :
	public SteeringBehaviour
{
private:
	KinematicBody* character;

	float maxSpeed = 3.0f;
	float maxRotationSpeed = 50.0f;

	Vec3 GetOrientationVector();
	float randomBinomial();

public:
	Wander(KinematicBody* character_);
	virtual ~Wander();

	SteeringOutput* getSteering();
};

#endif // !WANDER_H
