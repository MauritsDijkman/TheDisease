//
//  PlayerBody.h
//  DemoAIw
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
#include "Body.h"
#include "Character.h"
#include "GameManager.h"
#include "CharacterHealth.h"
#include "Ammunition.h"


#include <vector>

class PlayerBody : public Body
{
private:
	Vec3 mousePosWorld;
	bool isDead;
	int weaponType;
	bool altWeaponAvailable;

	Vec3 lookDirection;
	//void dead();

	std::vector<Ammunition*> Bullets;

protected:
	class GameManager* game;
	float health;
	float maxHealth= 3.0f;

	float gun;
	float onegun = 1.0f;

	//
	Sphere boundingSphere;
	double angle, angularVel, angularAccel, rotationalI;
	//
public:
	PlayerBody() : Body{}
	{
		game = nullptr;
	}

	PlayerBody(
		Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_,
		float radius_,
		float orientation_,
		float rotation_,
		float angular_,
		float maxSpeed_,
		float maxAcceleration_,
		float maxRotation_,
		float maxAngular_,
		GameManager* game_
	) : Body{
		  pos_
		, vel_
		, accel_
		, mass_
		, radius_
		, orientation_
		, rotation_
		, angular_
		, maxSpeed_
		, maxAcceleration_
		, maxRotation_
		, maxAngular_
	}
		, game{ game_ }
	{}
	

	// use the base class versions of getters

	
	std::vector<Ammunition*> fireBullet();

	bool OnCreate();
	void Render(float scale = 1.0f);
	void HandleEvents(const SDL_Event& event);
	void Update(float deltaTime);
	void resetToOrigin();
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	void FollowMouse(float mousePosX, float mousPosY);
	
	void dropammo();
	void dead();

	void setshotgun(float s) { gun = s; }
	float getshotgun() { return gun; }
	bool restoreshotgun(float shotgun_);

	void setHealth(float h) { health = h; }
    float getHealth() { return health ; }
	bool restoreHealth(float healingAmount_);
	void takeDamage(float damageAmount_);

	void setAltWeaponAvailable(bool altWeaponAvailable_) { altWeaponAvailable = altWeaponAvailable_; }
	void setWeaponType(int weaponType_) { weaponType = weaponType_; }
	
	//const Vec3 getLookDirection() const { return lookDirection; }
};

#endif /* PLAYERBODY_H */
