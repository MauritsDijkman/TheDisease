#include "PhysicsObject.h"

void PhysicsObject::dead()
{
}

PhysicsObject::PhysicsObject() :pos(10000.0f), vel(0.0f), accel(0.0f), mass(0.0f), boundingSphere(0.0f) {
	/// Another way to initialize within the constructor
	angle = angularVel = angularAccel = 0.0;
	rotationalI = 1.0f;
	fixedStatus = false;

}

PhysicsObject::~PhysicsObject() {

}

bool PhysicsObject::restoreHealth(float healingAmount_)
{
    bool destroyHealthPickup;	//if player full on health, keep health pickup on ground
    
    if (health == maxHealth) {
        destroyHealthPickup = false;//false
    }
    else {
        health += healingAmount_;
        if (health > maxHealth) {
            health = maxHealth;
        }
        destroyHealthPickup = true;//true
    }

    return destroyHealthPickup;
}

void PhysicsObject::takeDamage(float damageAmount_)
{
    health -= damageAmount_;
    if (health <= 0) {
        dead();
    }
}
