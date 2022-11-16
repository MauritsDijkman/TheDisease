#ifndef ARRIVE_TARGET_H
#define ARRIVE_TARGET_H
#include "Vector.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Node.h"
using namespace MATH;
using namespace std;
class ArriveTarget :
	public SteeringBehaviour{
private:
	KinematicBody* character;
	Node* target;
	float maxAcceleration = 1.0f;
	float maxSpeed = 2.0f;
	float targetRadius = 0.2f;
	float slowRadius = 3.0f;
	float timeToTarget = 0.01f;
	Vec3 direction;
	float distance;
	float targetSpeed;
	Vec3 targetVelocity;
public:
	ArriveTarget(KinematicBody* character_, Node* target_);
	virtual ~ArriveTarget();
	SteeringOutput* getSteering();
};
#endif // !ARRIVE_TARGET_H