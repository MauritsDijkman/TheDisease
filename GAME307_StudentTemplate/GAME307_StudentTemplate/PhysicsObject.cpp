#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() :pos(10000.0f), vel(0.0f), accel(0.0f), mass(0.0f), boundingSphere(0.0f)
{
	/// Another way to initialize within the constructor
	angle = angularVel = angularAccel = 0.0;
	rotationalI = 1.0f;
	fixedStatus = false;
}

PhysicsObject::~PhysicsObject() {}

void PhysicsObject::dead() {}
