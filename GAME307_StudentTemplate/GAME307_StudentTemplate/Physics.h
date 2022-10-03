#ifndef PHYSICS_H
#define PHYSICS_H
#include "Plane.h"
#include "PhysicsObject.h"

class Physics
{
public:

	static bool SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2);
	static void SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);
	
};
#endif
