#include "PlayerBody.h"
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

bool PlayerBody::restoreshotgun(float shotgun_)//pick up shotgun
{
	bool destroyshotgunPickup;

	if (gun == onegun)
		destroyshotgunPickup = false;
	else
	{
		gun += shotgun_;

		if (gun > onegun)
			gun = onegun;

		destroyshotgunPickup = true;
	}

	return destroyshotgunPickup;
}


bool PlayerBody::restoreammo(float ammo_)
{
	bool destroyammoPickup;

	if (ammos == oneammos)
		destroyammoPickup = false;
	else
	{
		ammos += ammo_;

		if (ammos > oneammos)
			ammos = oneammos;

		destroyammoPickup = true;
	}
	return destroyammoPickup;
}

bool PlayerBody::restoreshotgunammo(float shotgunammo_)
{
	bool destroyshotgunammopickup;

	if (shotgun_ammo == shotgun_ammos)
		destroyshotgunammopickup = false;
	else
	{
		shotgun_ammo += shotgunammo_;

		if (shotgun_ammo > shotgun_ammos)
			shotgun_ammo = shotgun_ammos;

		destroyshotgunammopickup = true;
	}
	return destroyshotgunammopickup;
}

bool PlayerBody::restorevaccine(float vaccine_)
{
	bool destroyvaccinepickup;

	if (vaccine_bad == vaccine_good)
		destroyvaccinepickup = false;
	else
	{
		vaccine_bad += vaccine_;

		if (vaccine_bad > vaccine_good)
			vaccine_bad = vaccine_good;

		destroyvaccinepickup = true;
	}
	return destroyvaccinepickup;
}

bool PlayerBody::restoreHealth(float healingAmount_)
{
	bool destroyHealthPickup;	//if player full on health, keep health pickup on ground

	if (health >= maxHealth)
		destroyHealthPickup = false;
	else
	{
		health += healingAmount_;

		if (health > maxHealth)
			health = maxHealth;

		destroyHealthPickup = true;
	}

	return destroyHealthPickup;
}

bool PlayerBody::restoreItemHealth(float healingItemAmount_)
{
	bool destroyitemHealthPickup;	//if player full on health, keep health pickup on ground

	if (itemhealth >= maxitemhealth)
		destroyitemHealthPickup = false;
	else
	{
		itemhealth += healingItemAmount_;

		if (itemhealth > maxitemhealth)
			itemhealth = maxitemhealth;

		destroyitemHealthPickup = true;
	}

	return destroyitemHealthPickup;
}

void PlayerBody::takeDamage(float damageAmount_)
{
	if (health > 0)
		health -= damageAmount_;
	else if (health < 0) {
		dead();
		health = 0;
	}
}

bool PlayerBody::OnReload(float pistol_reload_)
{
	bool destroypistolammoPickup;
	//Do we have ammo in the ammoPool?
	if (ammoPool <= 0 && loadammo >= 100) {
		return pistol_reload_;
	}
	//Do we have enough to meet what the gun needs?
	if (ammoPool < (100 - loadammo))
	{
		loadammo += pistol_reload_;
		loadammo = loadammo + ammoPool;
		ammoPool = 0;
		destroypistolammoPickup = false;
	}
	else
	{
		ammoPool = ammoPool - (100 - loadammo);
		loadammo = 100;
		destroypistolammoPickup = true;
	}
}

bool PlayerBody::OnReload2(float shotgun_reload_)
{
	bool destroyshotgunammoPickup;
	//Do we have ammo in the ammoPool?
	if (ammoshotgunpool <= 0 && ammoshotgun >= 300)
		return shotgun_reload_;

	//Do we have enough to meet what the gun needs?
	if (ammoshotgunpool < (300 - ammoshotgun))
	{
		ammoshotgun += shotgun_reload_;
		ammoshotgun =  ammoshotgun + ammoshotgunpool;
		ammoshotgunpool = 0;
		destroyshotgunammoPickup = false;
	}
	else
	{
		ammoshotgunpool = ammoshotgunpool - (300 - ammoshotgun);
		ammoshotgun = 300;
		destroyshotgunammoPickup = true;
	}
}

void PlayerBody::dead()
{
	isDead = true;
	printf("You Died\n");
}

std::vector<Ammunition*> PlayerBody::firePistolBullet()
{
	Bullets.clear();

	// WeaponType 0 standard weapon
	if (weaponType == 0)
	{
		float velx = 10.0f * cos(angle * M_PI / 180);
		float vely = -10.0f * sin(angle * M_PI / 180);

		Bullets.push_back(new Ammunition);
		Bullets[0]->setBoundingSphere(Sphere(0.25f));

		float offsetx = 0.01 + (boundingSphere.r + Bullets[0]->getBoundingSphere().r) * cos(angle * M_PI / 180);
		float offsety = 0.01 + (boundingSphere.r + Bullets[0]->getBoundingSphere().r) * sin(angle * M_PI / 180);

		Bullets[0]->setPos(Vec3(pos.x, pos.y, 0.0f));
		Bullets[0]->setVel(Vec3(velx, vely, 0.0f));

		if (loadammo <= 0)
			return vector<Ammunition*>();

		loadammo = loadammo - 1;
		
	}
	return Bullets;
}

std::vector<Ammunition*> PlayerBody::fireshotgunBullet()
{
	Bullets.clear();

	// WeaponType 1 is shotgun
	if (weaponType == 1)
	{
		for (int i = 0; i < 3; ++i)
		{
			Bullets.push_back(new Ammunition);
			Bullets[i]->setBoundingSphere(Sphere(0.25f));

			if (i == 1)
				angle += 15;
			if (i == 2)
				angle -= 30;

			float velx = 10.0f * cos(angle * M_PI / 180);
			float vely = -10.0f * sin(angle * M_PI / 180);

			Bullets[i]->setPos(Vec3(pos.x, pos.y, 0.0f));
			Bullets[i]->setVel(Vec3(velx, vely, 0.0f));

			if (ammoshotgun <= 0)
				return vector<Ammunition*>();

			ammoshotgun = ammoshotgun - 1;
		}

		angle += 15;
	}

	return Bullets;
}

vector<Ammunition*> PlayerBody::stabbing()
{
	knife.clear();

	if (weaponType == 2)
	{
		float velx = 10.0f * cos(angle * M_PI / 180);//10.0f * cos(angle * M_PI / 180)
		float vely = -10.0f * sin(angle * M_PI / 180);//-10.0f * sin(angle * M_PI / 180)

		knife.push_back(new Ammunition);
		knife[0]->setBoundingSphere(Sphere(0.25f));

		float offsetx = 0.01 + (boundingSphere.r + knife[0]->getBoundingSphere().r) * cos(angle * M_PI / 180);
		float offsety = 0.01 + (boundingSphere.r + knife[0]->getBoundingSphere().r) * sin(angle * M_PI / 180);

		Vec3 facing = VMath::normalize(Vec3(velx, vely, 0.0f));

		Vec3 knifePos = pos + facing * 1.0f;

		knife[0]->setPos(Vec3(knifePos.x, knifePos.y, 0.0f));
		knife[0]->setVel(Vec3(0.0f, 0.0f, 0.0f));

	}

	return knife;
}

bool PlayerBody::OnCreate()
{
	loadammo = 10;
	ammoPool = 100;

	ammoshotgunpool = 20;
	ammoshotgun = 100;

	image = IMG_Load("Assets/humans/idle_human2.png");

	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (image == nullptr)
	{
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

	// WeaponSwitch
	if (event.key.keysym.scancode == SDL_SCANCODE_C)
		weaponType = 0;
	if (event.key.keysym.scancode == SDL_SCANCODE_V)
	{
		if (altWeaponAvailable == true)
			weaponType = 1;
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
		weaponType = 2;

	// Get mouse position
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

	float scalar = getOrientation();
	//cout << "Orientation/Scalar player: " << scalar << endl;

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
	//PrintVectorRotation();
}

void PlayerBody::resetToOrigin()
{
	pos = Vec3(0.0f + radius, 0.0f + radius, 0.0f);
}

void PlayerBody::PrintVectorRotation()
{
	Vec3 characterPos = pos;
	Vec3 originPos = Vec3(0.0f, 0.0f, 0.0f);

	// sqrt((pX-qX)^2 + (pY-qY)^2)
	float unitlength = sqrt((characterPos.x - originPos.x) * (characterPos.x - originPos.x) +
		(characterPos.y - originPos.y) * (characterPos.y - originPos.y));

	// (x2 - x1, y2 - y1)
	Vec3 orientationVector;
	orientationVector = Vec3((characterPos.x - originPos.x) / unitlength, (characterPos.y - originPos.y) / unitlength, 0.0f);

	//cout << "Orientation Vector: " << orientationVector.x << " || " << orientationVector.y << endl;

}
