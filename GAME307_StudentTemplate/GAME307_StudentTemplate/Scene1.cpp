#include "Scene1.h"
#include "VMath.h"
#include "Sphere.h"

//#include "Body.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;//25
	yAxis = 15.0f;//15

	// create a NPC
	blinky = nullptr;
	myNPC = NULL;
}

Scene1::~Scene1() {
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	//TODO: Calculate the ortho every frame and take the player's location as the middle point

	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;

	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;

	ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);

	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Tried to add a background image
	/**
	SDL_Surface* backgroundSurface;
	backgroundSurface = IMG_Load("Pinky.png");
	SDL_Texture* backgroundTexture;
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	**/

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Assets/humans/idle_human2.png");
	//image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);



	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this))
	{
		return false;
	}

	image = IMG_Load("Blinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		blinky->setTexture(texture);
		SDL_FreeSurface(image);
	}

	//myNPC = new StaticBody();

	Vec3 postion = Vec3();
	float orientation = 0.0f;
	float maxSpeed = 3.5f;
	float maxRotation = 100.0f;
	

	myNPC = new StaticBody(postion, orientation, maxSpeed, maxRotation);

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		myNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}


	surfacePtr = IMG_Load("Shotgun96.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "weapon does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}
	weaponPickup = new GameObject();

	SDL_FreeSurface(surfacePtr);

	weaponPickup->setPos(Vec3(3.0f, 13.0f, 0.0f));
	weaponPickup->setBoundingSphere(Sphere(0.5f));
	weaponPickup->setTexture(texture);


	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime)
{
	// Updates the location of the orthograpic each frame
	
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;

	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);

	projectionMatrix = ndc * ortho;
	

	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);

	float radius = 1.0f;//1.0f
	float timeToTarget = 0.5f;

	Body* player = game->getPlayer();
	KinematicArrive* steering_algorithm;
	steering_algorithm = new KinematicArrive(radius, timeToTarget, myNPC, player);
	KinematicSteeringOutput* steering;
	steering = steering_algorithm->getSteering();



	//Create physicobject from the kinematicbody for npc
	

	Sphere boundingSphere;
	boundingSphere.x = myNPC->getPos().x;// get pos.x of the sphere equal to npc
	boundingSphere.y = myNPC->getPos().y;// get pso.y of the sphere equal to npc
	boundingSphere.r = 2.5f;

	Sphere boundingSphere2;
	boundingSphere.x = player->getPos().x;// get pos.x of the sphere equal to player
	boundingSphere.y = player->getPos().y;// get pos.y of the sphere equal to player
	boundingSphere.r =2.5f;  

	PhysicsObject* AI = new PhysicsObject();
	AI->setPos(myNPC->getPos());
	AI->setVel(myNPC->getVel());
	AI->setAccel(myNPC->getAccel());
	AI->setAngle(myNPC->getOrientation());
	AI->setAngularVel(myNPC->getRotation());
	AI->setAngularAccel(myNPC->getAngular());
	AI->setMass(myNPC->getMass());
	AI->setBoundingSphere(boundingSphere);

	PhysicsObject* P1 = new PhysicsObject();
	P1->setPos(player->getPos());
	P1->setVel(player->getVel());
	P1->setAccel(player->getAccel());
	P1->setAngle(player->getOrientation());
	P1->setAngularVel(player->getRotation());
	P1->setAngularAccel(player->getAngular());
	P1->setMass(player->getMass());
	P1->setBoundingSphere(boundingSphere2);

	
	//Phy->setBoundingSphere()
	//myNPC->Update(deltaTime, steering);
	// Update player
	game->getPlayer()->Update(deltaTime);

	//enemy hit player
	if (Physics::SphereSphereCollision(*AI, *P1) == true)
	{
		std::cout << "collide " << std::endl;
	}
	
	if (weaponPickup) {
		if (Physics::SphereSphereCollision(*weaponPickup, *P1) == true) {
			P1->setAltWeaponAvailable(true);
			P1->setWeaponType(1);
			//delete weaponPickup;
			//weaponPickup = nullptr;
		}
	}


}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	blinky->render(0.15f);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	float scale = 0.1f;

	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);

	screenCoords = projectionMatrix * myNPC->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	float orientation = myNPC->getOrientation() * 180 / M_PI;
	
	SDL_QueryTexture(weaponPickup->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);

	screenCoords = projectionMatrix * weaponPickup->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;
	
	//SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &square, orientation, nullptr, SDL_FLIP_NONE);



	// render the player
	game->RenderPlayer(0.10f);	

	SDL_RenderCopyEx(renderer, texturePtr, nullptr, &square,
		0.0f, nullptr, SDL_FLIP_NONE);

	

	SDL_Rect collectibleRect;
	Vec3 weaponPickupScreenCoords;
	int collectibleW, collectibleH;

	

	SDL_RenderPresent(renderer);

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed



	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
