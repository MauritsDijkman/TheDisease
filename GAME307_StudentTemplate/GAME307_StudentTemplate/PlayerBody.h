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
#include "Ammunition.h"


#include <vector>

class PlayerBody : public Body
{
private:
	Vec3 mousePosWorld;
	bool isDead;
	int weaponType;
	bool altWeaponAvailable;
	//void dead();

	std::vector<Ammunition> Bullets;

protected:
	class GameManager* game;

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

	void setAltWeaponAvailable(bool altWeaponAvailable_) { altWeaponAvailable = altWeaponAvailable_; }
	void setWeaponType(int weaponType_) { weaponType = weaponType_; }
	
};

#endif /* PLAYERBODY_H */
