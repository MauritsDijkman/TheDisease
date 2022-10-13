//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"
//#include "PhysicsObject.h"
#include <SDL.h>

void PlayerBody::FollowMouse(float mousePosX, float mousPosY)
{
	orientation = atan2(pos.y - mousPosY, mousePosX - pos.x);

	lookDirection = Vec3(mousePosX, mousePosX, 0.0f);
	if (mousePosX > pos.x) {
		angle = -atan((mousPosY - pos.y) / (mousePosX - pos.x)) * 180 / M_PI;
	}
	else {
		angle = 180 - atan((mousPosY - pos.y) / (mousePosX - pos.x)) * 180 / M_PI;
	}
	//std::cout << "MousePosWorld: " << mousePosWorld.x << ' ' << mousePosWorld.y << " || PlayerPos: " << pos.x << ' ' << pos.y << " || Orientation: " << orientation << ' ' << std::endl;
}

bool PlayerBody::restoreshotgun(float shotgun_)
{
	bool destroyshotgunPickup;
	if (gun == onegun) {
		destroyshotgunPickup = false;//
	}
	else {
		gun += shotgun_;
		if (gun > onegun) {
			gun = onegun;
		}
		destroyshotgunPickup = true;
	}

	return destroyshotgunPickup;
}


bool PlayerBody::restoreHealth(float healingAmount_)
{
	bool destroyHealthPickup;	//if player full on health, keep health pickup on ground
	if (health == maxHealth) {
		destroyHealthPickup = false;//
	}
	else {
		health += healingAmount_;
		if (health > maxHealth) {
			health = maxHealth;
		}
		destroyHealthPickup = true;
	}

	return destroyHealthPickup;
}

void PlayerBody::takeDamage(float damageAmount_)
{
	health -= damageAmount_;
	if (health <= 0) {
		dead();
	}
}

void PlayerBody::dropammo()
{
	int ammo = 10;

}

void PlayerBody::dead()
{
	isDead = true;
	printf("You Died\n");
}

std::vector<Ammunition*> PlayerBody::fireBullet()
{

	Bullets.clear();

	//weaponType 0 standard weapon

	if (weaponType == 0) {
		float velx = 10.0f * cos(angle * M_PI / 180);
		float vely = -10.0f * sin(angle * M_PI / 180);

		Bullets.push_back(new Ammunition);
		Bullets[0]->setBoundingSphere(Sphere(0.25f));

		float offsetx = 0.01 + (boundingSphere.r + Bullets[0]->getBoundingSphere().r) * cos(angle * M_PI / 180);
		float offsety = 0.01 + (boundingSphere.r + Bullets[0]->getBoundingSphere().r) * sin(angle * M_PI / 180);


		Bullets[0]->setPos(Vec3(pos.x, pos.y, 0.0f));
		Bullets[0]->setVel(Vec3(velx, vely, 0.0f));


		//angle = -atan((offsety - pos.y) / (offsetx - pos.x)) * 180 / M_PI;
		//angle = 180 - atan((offsety - pos.y) / (offsetx - pos.x)) * 180 / M_PI;

	//Bullets[0]->setRemainingBounces(3);
	}
	//weaponType 1 is shotgun

	if (weaponType == 1) {
		for (int i = 0; i < 3; ++i) {
			Bullets.push_back(new Ammunition);
			Bullets[i]->setBoundingSphere(Sphere(0.25f));

			if (i == 1) { angle += 15; }
			if (i == 2) { angle -= 30; }

			float velx = 10.0f * cos(angle * M_PI / 180);
			float vely = -10.0f * sin(angle * M_PI / 180);

			Bullets[i]->setPos(Vec3(pos.x, pos.y, 0.0f));
			Bullets[i]->setVel(Vec3(velx, vely, 0.0f));

			//Bullets[i]->setRemainingBounces(0);
		}

		angle += 15;
	}

	return Bullets;
}


bool PlayerBody::OnCreate()
{
	//image = IMG_Load("Pacman.png");
	image = IMG_Load("Assets/humans/idle_human2.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return true;
}

void PlayerBody::Render(float scale)
{
	SDL_Renderer* renderer = game->getRenderer();
	Matrix4 projectionMatrix = game->getProjectionMatrix();
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * pos;
	w = static_cast<int>(image->w * scale);
	h = static_cast<int>(image->h * scale);

	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientationDegrees = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, texture, nullptr, &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);
}

void PlayerBody::HandleEvents(const SDL_Event& event)
{
	// If key pressed, set velocity or acceleration
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
			// This section demonstrates using velocity for player movement
			//
			// Need to always normalize speed, otherwise having two keys down
			// results in velocity magnitude being sqrt(2) x maxSpeed.
			// However, this is being done in Update()
		case SDL_SCANCODE_W:
			vel.y = maxSpeed * 1.0f;
			break;
		case SDL_SCANCODE_A:
			vel.x = maxSpeed * -1.0f;
			break;
		case SDL_SCANCODE_S:
			vel.y = maxSpeed * -1.0f;
			break;
		case SDL_SCANCODE_D:
			vel.x = maxSpeed * 1.0f;
			break;

		case SDL_SCANCODE_LSHIFT:
			maxSpeed *= 2.0f;
			break;


			// This section is for seeing how to use acceleration rather than velocity
			// for player movement.
			// Note: look at Update() to see that velocity is clipped, since
			// continuous acceleration means continually increasing velocity.
		case SDL_SCANCODE_DOWN:
			accel.y = maxAcceleration * -1.0f;
			break;
		case SDL_SCANCODE_UP:
			accel.y = maxAcceleration * 1.0f;
			break;
		case SDL_SCANCODE_LEFT:
			accel.x = maxAcceleration * -1.0f;
			break;
		case SDL_SCANCODE_RIGHT:
			accel.x = maxAcceleration * 1.0f;
			break;
		default:
			break;
		}
	}

	// If key is released, stop applying movement
	if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
			// This section demonstrates using velocity for player movement
			//
			// Need to always normalize velocity, otherwise if player
			// releases one of two pressed keys, then speed remains at sqrt(0.5) of maxSpeed
		case SDL_SCANCODE_W:
			vel.y = 0.0f;
			if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * maxSpeed;
			break;
		case SDL_SCANCODE_A:
			vel.x = -0.0f;
			if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * maxSpeed;
			break;
		case SDL_SCANCODE_S:
			vel.y = -0.0f;
			if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * maxSpeed;
			break;
		case SDL_SCANCODE_D:
			vel.x = 0.0f;
			if (VMath::mag(vel) > VERY_SMALL) vel = VMath::normalize(vel) * maxSpeed;
			break;

		case SDL_SCANCODE_LSHIFT:
			maxSpeed /= 2.0f;
			break;

			// This section is for seeing how to use acceleration rather than velocity
			// for player movement.
		case SDL_SCANCODE_DOWN:
			accel.y = 0.0;
			break;
		case SDL_SCANCODE_UP:
			accel.y = 0.0;
			break;
		case SDL_SCANCODE_LEFT:
			accel.x = 0.0;
			break;
		case SDL_SCANCODE_RIGHT:
			accel.x = 0.0;
			break;
		default:
			break;
		}
	}

	//WeaponSwitch
	if (event.key.keysym.scancode == SDL_SCANCODE_E)
		weaponType = 0;
	if (event.key.keysym.scancode == SDL_SCANCODE_R)
	{
		//if (altWeaponAvailable == true) {
		//	weaponType = 1;
		//}
		weaponType = 1;
	}

	if (event.type == SDL_EventType::SDL_MOUSEMOTION)
	{
		Vec3 mousePosView = Vec3(event.button.x, event.button.y, 0);
		mousePosWorld = MMath::inverse(game->getProjectionMatrix()) * mousePosView;

	}
}

void PlayerBody::Update(float deltaTime)
{
	// Update position, call Update from base class
	// Note that would update velocity too, and rotation motion

	Body::Update(deltaTime);

	// This will ensure player body stops at edges
	float height, width;
	height = game->getSceneHeight();
	width = game->getSceneWidth();

	// [TODO] Border for the game
	/**
	if (pos.x < radius)
	{
		pos.x = radius;
		vel.x = 0.0f;
	}
	if (pos.y < radius)
	{
		pos.y = radius;
		vel.y = 0.0f;
	}
	if (pos.x > width - radius)
	{
		pos.x = width - radius;
		vel.x = 0.0f;
	}
	if (pos.y > height - radius)
	{
		pos.y = height - radius;
		vel.y = 0.0f;
	}
	/**/

	FollowMouse(mousePosWorld.x, mousePosWorld.y);	// mousePosWorld.x, mousePosWorld.y
}

void PlayerBody::resetToOrigin()
{
	pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}
