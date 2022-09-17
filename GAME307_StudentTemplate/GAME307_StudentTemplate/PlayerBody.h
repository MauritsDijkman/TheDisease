//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include "Vector"

class PlayerBody : public Body
{

private:
	bool mouseDown;// true or flase using mouse
	Vec3 lookDirection;// Direction that the mouse is looking

	Vec3 LookDirection(float x, float y);// adding th eequation
	Matrix4 projectionMatrix;

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
	//PlayerBody();
	//~PlayerBody();
	bool OnCreate();
	void Render(float scale = 1.0f);
	void HandleEvents(const SDL_Event& event);
	void Update(float deltaTime);
	void resetToOrigin();
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	const bool getMouseDown() const { return mouseDown; }
	const Vec3 getLookDirection() const { return lookDirection; }
};

#endif /* PLAYERBODY_H */