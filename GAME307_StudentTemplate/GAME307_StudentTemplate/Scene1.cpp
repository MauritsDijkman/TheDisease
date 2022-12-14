#include "Scene1.h"
#include "VMath.h"
#include <Node.h>
#include "SDL_audio.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	
	// Create a NPC
	blinky = nullptr;
	enemy = nullptr;
	enemy1 = nullptr;
}

Scene1::~Scene1()
{
	// Following enemy
	if (blinky){
		blinky->OnDestroy();
		delete blinky;
	}

	// Enemy follows given targetss
	if (enemy){
		enemy->OnDestroy();
		delete enemy;
	}
	if (enemy1) {
		enemy1->OnDestroy();
		delete enemy1;
	}
}

bool Scene1::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);

	// Calculates the ortho matrix with the player's position as middle point
	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;
	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;
	ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Load background
	background = new GameObject(renderer, "Assets/Background.png");

#pragma region Bullet

	// Load the crouton image and set the texture
	surfacePtr = IMG_Load("bullet.2.png");
	pistolbullet = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (pistolbullet == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	// Load the crouton image and set the texture
	surfacePtr = IMG_Load("bullet.2.png");
	shotgunbullet = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (shotgunbullet == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}
	SDL_FreeSurface(surfacePtr);
#pragma endregion

#pragma region Enemies

	// Load enemy characters
	surfacePtr = IMG_Load("The Unbread.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);


#pragma region Enemies_spawn	
	// Spawn to right
	for (int i = 0; i < 250; i++) {

		// Create enemy and add in the list
		enemies.push_back(new EnemyCharacter());

		// Set stats of the current enemy
		enemies[i]->setPos(Vec3(100.0f - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies[i]->setBoundingSphere(Sphere(0.5f));
		enemies[i]->setTexture(texturePtr);
	}

	// Spawn to left

	for (int i = 0; i < 250; i++) {
		// Create enemy and add in the list
		enemies1.push_back(new EnemyCharacter());
		
		// Set stats of the current enemy
		enemies1[i]->setPos(Vec3(-300.0f - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies1[i]->setBoundingSphere(Sphere(0.5f));
		enemies1[i]->setTexture(texturePtr);
	}

	// Spawn up

	for (int i = 0; i < 250; i++) {
		// Create enemy and add in the list
		enemies2.push_back(new EnemyCharacter());
		
		// Set stats of the current enemy
		enemies2[i]->setPos(Vec3(xAxis - 3.0f, 600 - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies2[i]->setBoundingSphere(Sphere(0.5f));
		enemies2[i]->setTexture(texturePtr);
	}
	
	// Spawn down
	for (int i = 0; i < 250; i++) {
		// Create enemy and add in the list
		enemies3.push_back(new EnemyCharacter());
		
		// Set stats of the current enemy
		enemies3[i]->setPos(Vec3(xAxis - 3.0f, -1200 - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies3[i]->setBoundingSphere(Sphere(0.5f));
		enemies3[i]->setTexture(texturePtr);
	}
#pragma endregion

#pragma endregion

#pragma region Player health
	// Set the health of the player
	game->getPlayer()->setHealth(3.0f);

	// Load health icon and set the texture
	surfacePtr = IMG_Load("Assets/Ethan/medicine.png");
	health = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	
	// Null pointer checks
	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (health == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}
	SDL_FreeSurface(surfacePtr);
#pragma endregion

#pragma region Health location
	LoadImage("Assets/Ethan/medicine.png");
	// Create health pickup
	healthPickup = new Object();
	
	// Set stats
	healthPickup->setPos(Vec3(10.0f, 9.0f, 0.0f));
	healthPickup->setBoundingSphere(Sphere(0.5f));
	healthPickup->setTexture(texturePtr);

	healthPickup2 = new Object();
	healthPickup2->setPos(Vec3(20.0f, 9.0f, 0.0f));
	healthPickup2->setBoundingSphere(Sphere(0.5f));
	healthPickup2->setTexture(texturePtr);

	healthPickup3 = new Object();
	healthPickup3->setPos(Vec3(-20.0f, -10.0f, 0.0f));
	healthPickup3->setBoundingSphere(Sphere(0.5f));
	healthPickup3->setTexture(texturePtr);

	healthPickup4 = new Object();
	healthPickup4->setPos(Vec3(-30.0f, 39.0f, 0.0f));
	healthPickup4->setBoundingSphere(Sphere(0.5f));
	healthPickup4->setTexture(texturePtr);

#pragma endregion

#pragma region Shotgun
	// Load shotgun picked up icon and set the texture
	surfacePtr = IMG_Load("Shotgun96.png");
	melee = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	
	// Null pointer checks
	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (melee == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}
SDL_FreeSurface(surfacePtr);
#pragma endregion

#pragma region Health image
	// Load health icon and set the texture
	surfacePtr = IMG_Load("Assets/Ethan/medicine.png");
	itemhealth = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (itemhealth == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}
	SDL_FreeSurface(surfacePtr);

	// Create health pickup
	itemhealthpickup = new Object();
	itemhealthpickup->setTexture(texturePtr);

	itemhealthpickup2 = new Object();
	itemhealthpickup2->setTexture(texturePtr);

	itemhealthpickup3 = new Object();
	itemhealthpickup3->setTexture(texturePtr);

	itemhealthpickup4 = new Object();
	itemhealthpickup4->setTexture(texturePtr);
#pragma endregion

#pragma region Shotgun
	LoadImage("Shotgun96.png");

	// Create weapon pickup
	weaponPickup = new Object();

	// Set stats
	weaponPickup->setPos(Vec3(3.0f, 13.0f, 0.0f));
	weaponPickup->setBoundingSphere(Sphere(0.25f));
	weaponPickup->setTexture(texturePtr);
#pragma endregion

#pragma region Vaccine
	game->getPlayer()->setvaccine(0.0f);
	surfacePtr = IMG_Load("Assets/Ethan/key.png");
	key = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr) {
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (key == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}
	SDL_FreeSurface(surfacePtr);
	
	LoadImage("Assets/Ethan/key.png");
	keyPickup = new Object();
	keyPickup->setPos(Vec3(1.0f, 2.0f, 0.0f));
    keyPickup->setBoundingSphere(Sphere(0.25f));
	keyPickup->setTexture(texturePtr);

	keyPickup1 = new Object();
	keyPickup1->setPos(Vec3(20.0f, 24.0f, 0.0f));
	keyPickup1->setBoundingSphere(Sphere(0.25f));
	keyPickup1->setTexture(texturePtr);

	keyPickup2 = new Object();
	keyPickup2->setPos(Vec3(45.0f, 30.0f, 0.0f));
	keyPickup2->setBoundingSphere(Sphere(0.25f));
	keyPickup2->setTexture(texturePtr);
	
	keyPickup3 = new Object();
	keyPickup3->setPos(Vec3(-20.0f, -24.0f, 0.0f));
	keyPickup3->setBoundingSphere(Sphere(0.25f));
	keyPickup3->setTexture(texturePtr);

	keyPickup4 = new Object();
	keyPickup4->setPos(Vec3(-45.0f, -48.0f, 0.0f));
	keyPickup4->setBoundingSphere(Sphere(0.25f));
	keyPickup4->setTexture(texturePtr);
#pragma endregion

#pragma region Wall
	// Loads in the wall image and set the texture to the walls
	surfacePtr = IMG_Load("Assets/Ethan/wall.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}

	if (texturePtr == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}

SDL_FreeSurface(surfacePtr);
#pragma endregion

#pragma region Knife
	surfacePtr = IMG_Load("knife.png");
	knifes = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr){
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (knifes == nullptr){
		printf("%s\n", SDL_GetError());
		return false;
	}
SDL_FreeSurface(surfacePtr);
#pragma endregion

#pragma region Ammo
// Load pistol ammo picked up icon and set the texture
	surfacePtr = IMG_Load("Assets/Ethan/ammo_1.png");
	ammo = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr) {
		std::cerr << "Image does not work" << std::endl;
		return false;
	}
	if (ammo == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	// Create ammo
	ammoPickup = new Object();

	// Set stats
	ammoPickup->setPos(Vec3(0.0f, 13.0f, 0.0f));
	ammoPickup->setBoundingSphere(Sphere(0.25f));
	ammoPickup->setTexture(ammo);

	// Create ammo
	ammo1Pickup = new Object();

	// Set stats
	ammo1Pickup->setPos(Vec3(25.0f, 25.0f, 0.0f));
	ammo1Pickup->setBoundingSphere(Sphere(0.25f));
	ammo1Pickup->setTexture(ammo);

	// Create ammo
	ammo2Pickup = new Object();

	// Set stats
	ammo2Pickup->setPos(Vec3(-25.0f, -25.0f, 0.0f));
	ammo2Pickup->setBoundingSphere(Sphere(0.25f));
	ammo2Pickup->setTexture(ammo);

	// Create ammo
	ammo3Pickup = new Object();

	// Set stats
	ammo3Pickup->setPos(Vec3(-30.0f, 40.0f, 0.0f));
	ammo3Pickup->setBoundingSphere(Sphere(0.25f));
	ammo3Pickup->setTexture(ammo);

	// Create ammo
	ammo4Pickup = new Object();

	// Set stats
	ammo4Pickup->setPos(Vec3(30.0f, -40.0f, 0.0f));
	ammo4Pickup->setBoundingSphere(Sphere(0.25f));
	ammo4Pickup->setTexture(ammo);

	// Load shotgunammo picked up icon and set the texture
	surfacePtr = IMG_Load("Assets/Ethan/ammo_2.png");
	shotgunammo = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	// Null pointer checks
	if (surfacePtr == nullptr) {
		std::cerr << "Image does not work" << std::endl;
		return false;
	}

	if (shotgunammo == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	// Create ammo
	shotgunammoPickup = new Object();

	// Set stats
	shotgunammoPickup->setPos(Vec3(15.0f, 20.0f, 0.0f));
	shotgunammoPickup->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup->setTexture(shotgunammo);

	// Create ammo
	shotgunammoPickup1 = new Object();
	// Set stats
	shotgunammoPickup1->setPos(Vec3(-15.0f, 20.0f, 0.0f));
	shotgunammoPickup1->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup1->setTexture(shotgunammo);

	// Create ammo
	shotgunammoPickup2 = new Object();
	// Set stats
	shotgunammoPickup2->setPos(Vec3(5.0f, 10.0f, 0.0f));
	shotgunammoPickup2->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup2->setTexture(shotgunammo);

	// Create ammo
	shotgunammoPickup3 = new Object();

	// Set stats
	shotgunammoPickup3->setPos(Vec3(40.0f, -33.0f, 0.0f));
	shotgunammoPickup3->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup3->setTexture(shotgunammo);

	// Create ammo
	shotgunammoPickup4 = new Object();

	// Set stats
	shotgunammoPickup4->setPos(Vec3(-40.0f, 33.0f, 0.0f));
	shotgunammoPickup4->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup4->setTexture(shotgunammo);
#pragma endregion

	// Making the level
	level = new Level(NUMWALL);
	level->makeLevel(1); //pos of wall
	level->setWallTextures(texturePtr);

	// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

#pragma region Level & A* algorithm

// Generate the layout of the scene
GenerateSceneLayout();

// Create the graph, an empty graph
graph = new Graph();
if (!graph->OnCreate(nodes)) {
		cout << "Graph OnCreate false!" << endl;
		return false;
}

// Calculate the weight of the connections
CalculateConnectionWeights();

// Print the neighbours of give node
printf("Neighbours of 93: \n");
int nodeLabel;

for (auto nodeLabel : graph->GetNeighbours(93))
	printf("Node %i, ", nodeLabel);

	// Get shortest path from node to give node
	vector<int> path = graph->AStar(0, 449);

	cout << "Path size: " << path.size() << endl;

	if (path.size() > 0){
		for (int i = 0; i < path.size(); i++)
			cout << "Path " << i << ": " << path[i] << endl;
	}
	else if (path.size() <= 0)

	cout << "You can't get there from here!" << endl;
#pragma endregion

#pragma region Player

	// Set player image
	SDL_Surface* image;
	SDL_Texture* texture;
	image = IMG_Load("Assets/humans/idle_human2.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);
#pragma endregion

#pragma region Blinky

	// Set up characters, choose good values for the constructor or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this))
		return false;

	image = IMG_Load("Blinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (image == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else{
		blinky->setTexture(texture);
		SDL_FreeSurface(image);
	}
#pragma endregion

#pragma region Enemy

	// Set up characters, choose good values for the constructor or use the defaults, like this
	enemy = new Enemy(game->getPlayer());
	vector<Node*> targetList = vector<Node*>();
	for (int node : path)
		targetList.push_back(graph->GetNode(node));

	enemy->SetTargetNodes(targetList);

	for (Node* node : targetList)
		cout << "Enemy target: " << node->GetLabel() << endl;

	if (!enemy->OnCreate(this))
		return false;

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (image == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else{
		enemy->setTexture(texture);
		SDL_FreeSurface(image);
	}

	enemy1 = new Enemy(game->getPlayer());
	if (!enemy1->OnCreate(this))
		return false;
	image = IMG_Load("Inky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		enemy1->setTexture(texture);
		SDL_FreeSurface(image);
	}
#pragma endregion
	
	return true;
}

void Scene1::OnDestroy()
{
	for (EnemyCharacter* EnemyCharacter : enemies,enemies1,enemies2,enemies3) {
		SDL_DestroyTexture(EnemyCharacter->getTexture());
		delete EnemyCharacter;
	}
}


void Scene1::Update(const float deltaTime)
{
	// Updates the location of the orthograpic each frame
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	
	// For moving camera view
	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;
	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;
	
	// Calculate the matrixes
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);
	
	// Calculate the projections
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);
	Body* player = game->getPlayer();
	float radius = 1.0f;
	float timeToTarget = 0.5f;
	
	// Update the npc's
	blinky->Update(deltaTime);
	enemy->Update(deltaTime);
	enemy1->Update(deltaTime);

	// Create physicobject from the kinematicbody for npc
	Sphere boundingSphere;
	boundingSphere.x = blinky->getBody()->getPos().x;	// Get pos.x of the sphere equal to npc //myNPC->getPos().x
	boundingSphere.y = blinky->getBody()->getPos().y;	// Get pos.y of the sphere equal to npc //myNPC->getPos().y
	boundingSphere.r = 0.4f;
	Sphere boundingSphere2;
	boundingSphere2.x = player->getPos().x;				// Get pos.x of the sphere equal to player
	boundingSphere2.y = player->getPos().y;				// Get pos.y of the sphere equal to player
	boundingSphere2.r = 0.4f;

#pragma region Ethan

//Set the object	
	PhysicsObject* P1 = new PhysicsObject();
	P1->setPos(player->getPos());
	P1->setVel(player->getVel());
	P1->setAccel(player->getAccel());
	P1->setAngle(player->getOrientation());
	P1->setAngularVel(player->getRotation());
	P1->setAngularAccel(player->getAngular());
	P1->setMass(player->getMass());
	P1->setBoundingSphere(boundingSphere2);

#pragma region Player collides with wall

	// Player hits walls
	for (int i = 0; i < level->getWallNum(); i++)
	{
		if (Physics::CircleRectCollision(*P1, *level->getWall(i)) == true)
		{
			game->getPlayer()->Update(-deltaTime);
			Physics::SimpleNewtonMotion(*P1, -deltaTime);
		}
	}
#pragma endregion

#pragma region player collide to item

	// if Player collide on item
	if (healthPickup){
		if (Physics::SphereSphereCollision(*P1, *healthPickup) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (healthPickup2) {
		if (Physics::SphereSphereCollision(*P1, *healthPickup2) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (healthPickup3) {
		if (Physics::SphereSphereCollision(*P1, *healthPickup3) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (healthPickup4) {
		if (Physics::SphereSphereCollision(*P1, *healthPickup4) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (weaponPickup){
		if (Physics::SphereSphereCollision(*weaponPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (keyPickup) {
		if (Physics::SphereSphereCollision(*keyPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (keyPickup1) {
		if (Physics::SphereSphereCollision(*keyPickup1, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (keyPickup2) {
		if (Physics::SphereSphereCollision(*keyPickup2, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (keyPickup3) {
		if (Physics::SphereSphereCollision(*keyPickup3, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (keyPickup4) {
		if (Physics::SphereSphereCollision(*keyPickup4, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (ammoPickup){
		if (Physics::SphereSphereCollision(*ammoPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (ammo1Pickup) {
		if (Physics::SphereSphereCollision(*ammo1Pickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (ammo2Pickup) {
		if (Physics::SphereSphereCollision(*ammo2Pickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (ammo3Pickup) {
		if (Physics::SphereSphereCollision(*ammo3Pickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (ammo4Pickup) {
		if (Physics::SphereSphereCollision(*ammo4Pickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup1) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup1, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup2) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup2, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup3) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup3, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup4) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup4, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}
#pragma endregion

#pragma region Enemy & Bullet

#pragma region bullet momevent

	// Pistol bullets movement
	for (int i = 0; i < pistol.size(); i++)
		Physics::SimpleNewtonMotion(*pistol[i], deltaTime);

	//Shotgun bullets movement
	for (int i = 0; i < shotgun.size(); i++)
		Physics::SimpleNewtonMotion(*shotgun[i], deltaTime);
#pragma endregion

#pragma region damage player

	// Enemy hits player
	for (int i = 0; i < enemies.size(); i++){
		if (Physics::SphereSphereCollision(*enemies[i], *P1) == true){
			game->getPlayer()->takeDamage(1.0f);
			enemies.erase(enemies.begin() + i);
		}
	}

	for (int i = 0; i < enemies1.size(); i++){
		if (Physics::SphereSphereCollision(*enemies1[i], *P1) == true){
			game->getPlayer()->takeDamage(1.0f);
			enemies1.erase(enemies1.begin() + i);
		}
	}

	for (int i = 0; i < enemies2.size(); i++){
		if (Physics::SphereSphereCollision(*enemies2[i], *P1) == true){
			game->getPlayer()->takeDamage(1.0f);
			enemies2.erase(enemies2.begin() + i);
		}
	}

	for (int i = 0; i < enemies3.size(); i++){
		if (Physics::SphereSphereCollision(*enemies3[i], *P1) == true){
			game->getPlayer()->takeDamage(1.0f);
			enemies3.erase(enemies3.begin() + i);
		}
	}

#pragma endregion

#pragma region momevent enemy

	// Enemy movement
	for (int i = 0; i < enemies.size(); i++){
		enemies[i]->SeekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies[i], deltaTime);
	}
	for (int i = 0; i < enemies1.size(); i++){
		enemies1[i]->SeekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies1[i], deltaTime);
	}
	for (int i = 0; i < enemies2.size(); i++){
		enemies2[i]->SeekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies2[i], deltaTime);
	}
	for (int i = 0; i < enemies3.size(); i++){
		enemies3[i]->SeekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies3[i], deltaTime);
	}

#pragma endregion
#pragma endregion

#pragma region player_damage_enemy

	// Bullet hits enemy
	for (int i = 0; i < pistol.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (Physics::SphereSphereCollision(*pistol[i], *enemies[j]) == true) {
				pistol.erase(pistol.begin() + i);
				enemies[j]->EnemytakeDamage(0.5f);
				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < pistol.size(); i++){
		for (int j = 0; j < enemies1.size(); j++){
			if (Physics::SphereSphereCollision(*pistol[i], *enemies1[j]) == true){
				pistol.erase(pistol.begin() + i);
				enemies1[j]->EnemytakeDamage(1.0f);
				if (enemies1[j]->getHealth() <= 0)
					enemies1.erase(enemies1.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < pistol.size(); i++){
		for (int j = 0; j < enemies2.size(); j++){
			if (Physics::SphereSphereCollision(*pistol[i], *enemies2[j]) == true){
				pistol.erase(pistol.begin() + i);
				enemies2[j]->EnemytakeDamage(1.0f);
				if (enemies2[j]->getHealth() <= 0)
					enemies2.erase(enemies2.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < pistol.size(); i++){
		for (int j = 0; j < enemies3.size(); j++){
			if (Physics::SphereSphereCollision(*pistol[i], *enemies3[j]) == true){
				pistol.erase(pistol.begin() + i);
				enemies3[j]->EnemytakeDamage(1.0f);
				if (enemies3[j]->getHealth() <= 0)
					enemies3.erase(enemies3.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++){
		for (int j = 0; j < enemies.size(); j++){
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies[j]) == true){
				shotgun.erase(shotgun.begin() + i);
				enemies[j]->EnemytakeDamage(1.5f);
				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++){
		for (int j = 0; j < enemies1.size(); j++){
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies1[j]) == true){
				shotgun.erase(shotgun.begin() + i);
				enemies1[j]->EnemytakeDamage(1.5f);
				if (enemies1[j]->getHealth() <= 0)
					enemies1.erase(enemies1.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++){
		for (int j = 0; j < enemies2.size(); j++){
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies2[j]) == true){
				shotgun.erase(shotgun.begin() + i);
				enemies2[j]->EnemytakeDamage(1.5f);
				if (enemies2[j]->getHealth() <= 0)
					enemies2.erase(enemies2.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++){
		for (int j = 0; j < enemies3.size(); j++){
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies3[j]) == true){
				shotgun.erase(shotgun.begin() + i);
				enemies3[j]->EnemytakeDamage(1.5f);
				if (enemies3[j]->getHealth() <= 0)
					enemies3.erase(enemies3.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies[j]) == true) {
				shotgun.erase(shotgun.begin() + i);
				enemies[j]->EnemytakeDamage(1.5f);
				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++) {
		for (int j = 0; j < enemies1.size(); j++) {
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies1[j]) == true) {
				shotgun.erase(shotgun.begin() + i);
				enemies1[j]->EnemytakeDamage(1.5f);
				if (enemies1[j]->getHealth() <= 0)
					enemies1.erase(enemies1.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++) {
		for (int j = 0; j < enemies2.size(); j++) {
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies2[j]) == true) {
				shotgun.erase(shotgun.begin() + i);
				enemies2[j]->EnemytakeDamage(1.5f);
				if (enemies2[j]->getHealth() <= 0)
					enemies2.erase(enemies2.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < shotgun.size(); i++) {
		for (int j = 0; j < enemies3.size(); j++) {
			if (Physics::SphereSphereCollision(*shotgun[i], *enemies3[j]) == true) {
				shotgun.erase(shotgun.begin() + i);
				enemies3[j]->EnemytakeDamage(1.5f);
				if (enemies3[j]->getHealth() <= 0)
					enemies3.erase(enemies3.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < knife.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (Physics::SphereSphereCollision(*knife[i], *enemies[j]) == true) {
				knife.erase(knife.begin() + i);
				enemies[j]->EnemytakeDamage(0.5f);
				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < knife.size(); i++){
		for (int j = 0; j < enemies1.size(); j++){
			if (Physics::SphereSphereCollision(*knife[i], *enemies1[j]) == true){
				knife.erase(knife.begin() + i);
				enemies1[j]->EnemytakeDamage(0.5f);
				if (enemies1[j]->getHealth() <= 0)
					enemies1.erase(enemies1.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < knife.size(); i++){
		for (int j = 0; j < enemies2.size(); j++){
			if (Physics::SphereSphereCollision(*knife[i], *enemies2[j]) == true){
				knife.erase(knife.begin() + i);
				enemies2[j]->EnemytakeDamage(0.5f);
				if (enemies2[j]->getHealth() <= 0)
					enemies2.erase(enemies2.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < knife.size(); i++){
		for (int j = 0; j < enemies3.size(); j++){
			if (Physics::SphereSphereCollision(*knife[i], *enemies3[j]) == true){
				knife.erase(knife.begin() + i);
				enemies3[j]->EnemytakeDamage(0.5f);
				if (enemies3[j]->getHealth() <= 0)
					enemies3.erase(enemies3.begin() + j);
				break;
			}
		}
	}

#pragma endregion

#pragma endregion
	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Render all the background tiles (including their nodes)
	// Place the tiles for the amount of columns and rows
	for (int row = 0; row < gridHeight; row++){
		for (int column = 0; column < gridWidth; column++)
			tiles[row][column]->Render(renderer, game->getProjectionMatrix(), true);
	}
	// Render any npc's
	//blinky->render(0.15f);
	enemy->render(0.15f);
	enemy1->render(0.15f);

#pragma region Render_location, height and length

	// Draws all the walls
	SDL_Rect WallRect;
	Vec3 wallScreenCoords;
	int WallW, WallH;

	for (int i = 0; i < NUMWALL; ++i){
		SDL_QueryTexture(level->getWall(i)->getTexture(), nullptr, nullptr, &WallW, &WallH);
		wallScreenCoords = projectionMatrix * level->getWall(i)->getPos();
		WallRect.x = static_cast<int> (wallScreenCoords.x) - 30;
		WallRect.y = static_cast<int> (wallScreenCoords.y) - 30;
		WallRect.w = 80;
		WallRect.h = 80;
		SDL_RenderCopy(renderer, level->getWall(i)->getTexture(), nullptr, &WallRect);
	}

	// draw
	SDL_Rect weaponcollectibleRect;
	Vec3 weaponPickupScreenCoords;
	int weaponcollectibleW, weaponcollectibleH;

	if (weaponPickup){
		SDL_QueryTexture(weaponPickup->getTexture(), nullptr, nullptr, &weaponcollectibleW, &weaponcollectibleH);
		weaponPickupScreenCoords = projectionMatrix * weaponPickup->getPos();
		weaponcollectibleRect.x = static_cast<int>(weaponPickupScreenCoords.x) - weaponcollectibleW / 4;
		weaponcollectibleRect.y = static_cast<int>(weaponPickupScreenCoords.y) - weaponcollectibleH / 4;
		weaponcollectibleRect.w = weaponcollectibleW / 2;
		weaponcollectibleRect.h = weaponcollectibleH / 2;
		SDL_RenderCopy(renderer, weaponPickup->getTexture(), nullptr, &weaponcollectibleRect);
	}
	
// draw
	SDL_Rect vaccinecollectibleRect;
	Vec3 vaccineScreenCoords;
	int vaccineW, vaccineH;

	if (keyPickup){
		SDL_QueryTexture(keyPickup->getTexture(), nullptr, nullptr, &vaccineW, &vaccineH);
		vaccineScreenCoords = projectionMatrix * keyPickup->getPos();
		vaccinecollectibleRect.x = static_cast<int>(vaccineScreenCoords.x) - vaccineW / 4;
		vaccinecollectibleRect.y = static_cast<int>(vaccineScreenCoords.y) - vaccineH / 4;
		vaccinecollectibleRect.w = vaccineW / 2;
		vaccinecollectibleRect.h = vaccineH / 2;
		SDL_RenderCopy(renderer, keyPickup->getTexture(), nullptr, &vaccinecollectibleRect);
	}

	if (keyPickup1) {
		SDL_QueryTexture(keyPickup1->getTexture(), nullptr, nullptr, &vaccineW, &vaccineH);
		vaccineScreenCoords = projectionMatrix * keyPickup1->getPos();
		vaccinecollectibleRect.x = static_cast<int>(vaccineScreenCoords.x) - vaccineW / 4;
		vaccinecollectibleRect.y = static_cast<int>(vaccineScreenCoords.y) - vaccineH / 4;
		vaccinecollectibleRect.w = vaccineW / 2;
		vaccinecollectibleRect.h = vaccineH / 2;
		SDL_RenderCopy(renderer, keyPickup1->getTexture(), nullptr, &vaccinecollectibleRect);
	}

	if (keyPickup2) {
		SDL_QueryTexture(keyPickup2->getTexture(), nullptr, nullptr, &vaccineW, &vaccineH);
		vaccineScreenCoords = projectionMatrix * keyPickup2->getPos();
		vaccinecollectibleRect.x = static_cast<int>(vaccineScreenCoords.x) - vaccineW / 4;
		vaccinecollectibleRect.y = static_cast<int>(vaccineScreenCoords.y) - vaccineH / 4;
		vaccinecollectibleRect.w = vaccineW / 2;
		vaccinecollectibleRect.h = vaccineH / 2;
		SDL_RenderCopy(renderer, keyPickup2->getTexture(), nullptr, &vaccinecollectibleRect);
	}

	if (keyPickup3) {
		SDL_QueryTexture(keyPickup3->getTexture(), nullptr, nullptr, &vaccineW, &vaccineH);
		vaccineScreenCoords = projectionMatrix * keyPickup3->getPos();
		vaccinecollectibleRect.x = static_cast<int>(vaccineScreenCoords.x) - vaccineW / 4;
		vaccinecollectibleRect.y = static_cast<int>(vaccineScreenCoords.y) - vaccineH / 4;
		vaccinecollectibleRect.w = vaccineW / 2;
		vaccinecollectibleRect.h = vaccineH / 2;
		SDL_RenderCopy(renderer, keyPickup3->getTexture(), nullptr, &vaccinecollectibleRect);
	}

	if (keyPickup4) {
		SDL_QueryTexture(keyPickup4->getTexture(), nullptr, nullptr, &vaccineW, &vaccineH);
		vaccineScreenCoords = projectionMatrix * keyPickup4->getPos();
		vaccinecollectibleRect.x = static_cast<int>(vaccineScreenCoords.x) - vaccineW / 4;
		vaccinecollectibleRect.y = static_cast<int>(vaccineScreenCoords.y) - vaccineH / 4;
		vaccinecollectibleRect.w = vaccineW / 2;
		vaccinecollectibleRect.h = vaccineH / 2;
		SDL_RenderCopy(renderer, keyPickup4->getTexture(), nullptr, &vaccinecollectibleRect);
	}

	if (game->getPlayer()->getvaccine() > 0) {
		SDL_Rect vaxRect;
		vaxRect.x = 20;
		vaxRect.y = 200;
		vaxRect.w = 50;
		vaxRect.h = 50;
		SDL_RenderCopy(renderer, key, nullptr, &vaxRect);

		if (game->getPlayer()->getvaccine() > 1) {
			SDL_Rect vaxRect1;
			vaxRect1.x = 40;
			vaxRect1.y = 200;
			vaxRect1.w = 50;
			vaxRect1.h = 50;
			SDL_RenderCopy(renderer, key, nullptr, &vaxRect1);

			if (game->getPlayer()->getvaccine() > 2) {
				SDL_Rect vaxRect2;
				vaxRect2.x = 60;
				vaxRect2.y = 200;
				vaxRect2.w = 50;
				vaxRect2.h = 50;
				SDL_RenderCopy(renderer, key, nullptr, &vaxRect2);

				if (game->getPlayer()->getvaccine() > 3) {
					SDL_Rect vaxRect3;
					vaxRect3.x = 80;
					vaxRect3.y = 200;
					vaxRect3.w = 50;
					vaxRect3.h = 50;
					SDL_RenderCopy(renderer, key, nullptr, &vaxRect3);

					if (game->getPlayer()->getvaccine() > 4) {
						SDL_Rect vaxRect4;
						vaxRect4.x = 100;
						vaxRect4.y = 200;
						vaxRect4.w = 50;
						vaxRect4.h = 50;
						SDL_RenderCopy(renderer, key, nullptr, &vaxRect4);

						if (game->getPlayer()->getvaccine() > 5) {
							SDL_Rect vaxRect5;
							vaxRect5.x = 120;
							vaxRect5.y = 200;
							vaxRect5.w = 50;
							vaxRect5.h = 50;
							SDL_RenderCopy(renderer, key, nullptr, &vaxRect5);
						}
					}

				}
			}
		}
	}


	//draw
	SDL_Rect ammocollectibleRect;
	Vec3 ammoPickupScreenCoords;
	int ammocollectibleW, ammocollectibleH;

	if (ammoPickup){
		SDL_QueryTexture(ammoPickup->getTexture(), nullptr, nullptr, &ammocollectibleW, &ammocollectibleH);
		ammoPickupScreenCoords = projectionMatrix * ammoPickup->getPos();
		ammocollectibleRect.x = static_cast<int>(ammoPickupScreenCoords.x) - ammocollectibleW / 4;
		ammocollectibleRect.y = static_cast<int>(ammoPickupScreenCoords.y) - ammocollectibleH / 4;
		ammocollectibleRect.w = ammocollectibleW / 2;
		ammocollectibleRect.h = ammocollectibleH / 2;
		SDL_RenderCopy(renderer, ammoPickup->getTexture(), nullptr, &ammocollectibleRect);
	}

	if (ammo1Pickup) {
		SDL_QueryTexture(ammo1Pickup->getTexture(), nullptr, nullptr, &ammocollectibleW, &ammocollectibleH);
		ammoPickupScreenCoords = projectionMatrix * ammo1Pickup->getPos();
		ammocollectibleRect.x = static_cast<int>(ammoPickupScreenCoords.x) - ammocollectibleW / 4;
		ammocollectibleRect.y = static_cast<int>(ammoPickupScreenCoords.y) - ammocollectibleH / 4;
		ammocollectibleRect.w = ammocollectibleW / 2;
		ammocollectibleRect.h = ammocollectibleH / 2;
		SDL_RenderCopy(renderer, ammo1Pickup->getTexture(), nullptr, &ammocollectibleRect);
	}

	if (ammo2Pickup) {
		SDL_QueryTexture(ammo2Pickup->getTexture(), nullptr, nullptr, &ammocollectibleW, &ammocollectibleH);
		ammoPickupScreenCoords = projectionMatrix * ammo2Pickup->getPos();
		ammocollectibleRect.x = static_cast<int>(ammoPickupScreenCoords.x) - ammocollectibleW / 4;
		ammocollectibleRect.y = static_cast<int>(ammoPickupScreenCoords.y) - ammocollectibleH / 4;
		ammocollectibleRect.w = ammocollectibleW / 2;
		ammocollectibleRect.h = ammocollectibleH / 2;
		SDL_RenderCopy(renderer, ammo2Pickup->getTexture(), nullptr, &ammocollectibleRect);
	}

	if (ammo3Pickup) {
		SDL_QueryTexture(ammo3Pickup->getTexture(), nullptr, nullptr, &ammocollectibleW, &ammocollectibleH);
		ammoPickupScreenCoords = projectionMatrix * ammo3Pickup->getPos();
		ammocollectibleRect.x = static_cast<int>(ammoPickupScreenCoords.x) - ammocollectibleW / 4;
		ammocollectibleRect.y = static_cast<int>(ammoPickupScreenCoords.y) - ammocollectibleH / 4;
		ammocollectibleRect.w = ammocollectibleW / 2;
		ammocollectibleRect.h = ammocollectibleH / 2;
		SDL_RenderCopy(renderer, ammo3Pickup->getTexture(), nullptr, &ammocollectibleRect);
	}

	if (ammo4Pickup) {
		SDL_QueryTexture(ammo4Pickup->getTexture(), nullptr, nullptr, &ammocollectibleW, &ammocollectibleH);
		ammoPickupScreenCoords = projectionMatrix * ammo4Pickup->getPos();
		ammocollectibleRect.x = static_cast<int>(ammoPickupScreenCoords.x) - ammocollectibleW / 4;
		ammocollectibleRect.y = static_cast<int>(ammoPickupScreenCoords.y) - ammocollectibleH / 4;
		ammocollectibleRect.w = ammocollectibleW / 2;
		ammocollectibleRect.h = ammocollectibleH / 2;
		SDL_RenderCopy(renderer, ammo4Pickup->getTexture(), nullptr, &ammocollectibleRect);
	}

	if (game->getPlayer()->getammo() > 0){
		SDL_Rect ammoRect;
		ammoRect.x = 20;
		ammoRect.y = 450;
		ammoRect.w = 50;
		ammoRect.h = 50;
		SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect);

		if (game->getPlayer()->getammo() > 1) {
			SDL_Rect ammoRect1;
			ammoRect1.x = 40;
			ammoRect1.y = 450;
			ammoRect1.w = 50;
			ammoRect1.h = 50;
			SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect1);

			if (game->getPlayer()->getammo() > 2) {
				SDL_Rect ammoRect2;
				ammoRect2.x = 60;
				ammoRect2.y = 450;
				ammoRect2.w = 50;
				ammoRect2.h = 50;
				SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect2);

				if (game->getPlayer()->getammo() > 3) {
					SDL_Rect ammoRect3;
					ammoRect3.x = 80;
					ammoRect3.y = 450;
					ammoRect3.w = 50;
					ammoRect3.h = 50;
					SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect3);

					if (game->getPlayer()->getammo() > 4) {
						SDL_Rect ammoRect4;
						ammoRect4.x = 100;
						ammoRect4.y = 450;
						ammoRect4.w = 50;
						ammoRect4.h = 50;
						SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect4);
					}
				}
			}
		}
	}

	//draw
	SDL_Rect shotgunammoRect;
	Vec3 shotgunammoScreenCoords;
	int shotgunammoW, shotgunammoH;

	if (shotgunammoPickup) {
		SDL_QueryTexture(shotgunammoPickup->getTexture(), nullptr, nullptr, &shotgunammoW, &shotgunammoH);
		shotgunammoScreenCoords = projectionMatrix * shotgunammoPickup->getPos();
		shotgunammoRect.x = static_cast<int>(shotgunammoScreenCoords.x) - shotgunammoW / 4;
		shotgunammoRect.y = static_cast<int>(shotgunammoScreenCoords.y) - shotgunammoH / 4;
		shotgunammoRect.w = shotgunammoW / 2;
		shotgunammoRect.h = shotgunammoH / 2;
		SDL_RenderCopy(renderer, shotgunammoPickup->getTexture(), nullptr, &shotgunammoRect);
	}

	if (shotgunammoPickup1) {
		SDL_QueryTexture(shotgunammoPickup1->getTexture(), nullptr, nullptr, &shotgunammoW, &shotgunammoH);
		shotgunammoScreenCoords = projectionMatrix * shotgunammoPickup1->getPos();
		shotgunammoRect.x = static_cast<int>(shotgunammoScreenCoords.x) - shotgunammoW / 4;
		shotgunammoRect.y = static_cast<int>(shotgunammoScreenCoords.y) - shotgunammoH / 4;
		shotgunammoRect.w = shotgunammoW / 2;
		shotgunammoRect.h = shotgunammoH / 2;
		SDL_RenderCopy(renderer, shotgunammoPickup1->getTexture(), nullptr, &shotgunammoRect);
	}

	if (shotgunammoPickup2) {
		SDL_QueryTexture(shotgunammoPickup->getTexture(), nullptr, nullptr, &shotgunammoW, &shotgunammoH);
		shotgunammoScreenCoords = projectionMatrix * shotgunammoPickup2->getPos();
		shotgunammoRect.x = static_cast<int>(shotgunammoScreenCoords.x) - shotgunammoW / 4;
		shotgunammoRect.y = static_cast<int>(shotgunammoScreenCoords.y) - shotgunammoH / 4;
		shotgunammoRect.w = shotgunammoW / 2;
		shotgunammoRect.h = shotgunammoH / 2;
		SDL_RenderCopy(renderer, shotgunammoPickup2->getTexture(), nullptr, &shotgunammoRect);
	}

	if (shotgunammoPickup3) {
		SDL_QueryTexture(shotgunammoPickup3->getTexture(), nullptr, nullptr, &shotgunammoW, &shotgunammoH);
		shotgunammoScreenCoords = projectionMatrix * shotgunammoPickup3->getPos();
		shotgunammoRect.x = static_cast<int>(shotgunammoScreenCoords.x) - shotgunammoW / 4;
		shotgunammoRect.y = static_cast<int>(shotgunammoScreenCoords.y) - shotgunammoH / 4;
		shotgunammoRect.w = shotgunammoW / 2;
		shotgunammoRect.h = shotgunammoH / 2;
		SDL_RenderCopy(renderer, shotgunammoPickup3->getTexture(), nullptr, &shotgunammoRect);
	}

	if (shotgunammoPickup4) {
		SDL_QueryTexture(shotgunammoPickup4->getTexture(), nullptr, nullptr, &shotgunammoW, &shotgunammoH);
		shotgunammoScreenCoords = projectionMatrix * shotgunammoPickup4->getPos();
		shotgunammoRect.x = static_cast<int>(shotgunammoScreenCoords.x) - shotgunammoW / 4;
		shotgunammoRect.y = static_cast<int>(shotgunammoScreenCoords.y) - shotgunammoH / 4;
		shotgunammoRect.w = shotgunammoW / 2;
		shotgunammoRect.h = shotgunammoH / 2;
		SDL_RenderCopy(renderer, shotgunammoPickup4->getTexture(), nullptr, &shotgunammoRect);
	}

	if (game->getPlayer()->getshotgunammo() > 0) {
		SDL_Rect shotgunammoRect;
		shotgunammoRect.x = 20;
		shotgunammoRect.y = 300;
		shotgunammoRect.w = 50;
		shotgunammoRect.h = 50;
		SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect);

		if (game->getPlayer()->getshotgunammo() > 1) {
			SDL_Rect shotgunammoRect1;
			shotgunammoRect1.x = 40;
			shotgunammoRect1.y = 300;
			shotgunammoRect1.w = 50;
			shotgunammoRect1.h = 50;
			SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect1);

			if (game->getPlayer()->getshotgunammo() > 2) {
				SDL_Rect shotgunammoRect2;
				shotgunammoRect2.x = 60;
				shotgunammoRect2.y = 300;
				shotgunammoRect2.w = 50;
				shotgunammoRect2.h = 50;
				SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect2);

				if (game->getPlayer()->getshotgunammo() > 3) {
					SDL_Rect shotgunammoRect3;
					shotgunammoRect3.x = 80;
					shotgunammoRect3.y = 300;
					shotgunammoRect3.w = 50;
					shotgunammoRect3.h = 50;
					SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect3);
				
					if (game->getPlayer()->getshotgunammo() > 4) {
						SDL_Rect shotgunammoRect4;
						shotgunammoRect4.x = 100;
						shotgunammoRect4.y = 300;
						shotgunammoRect4.w = 50;
						shotgunammoRect4.h = 50;
						SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect4);
					}
				}
			}
		}
	}

	// Draw pistol bullets
	SDL_Rect pistolRect;
	Vec3 pistolScreenCoords;
	int pistolW, pistolH;

	for (int i = 0; i < pistol.size(); i++){
		pistolScreenCoords = projectionMatrix * pistol[i]->getPos();
		SDL_QueryTexture(pistol[i]->getTexture(), nullptr, nullptr, &pistolW, &pistolH);
		pistolRect.x = static_cast<int>(pistolScreenCoords.x - pistolW / 20);
		pistolRect.y = static_cast<int>(pistolScreenCoords.y - pistolH / 20);
		pistolRect.w = pistolW / 10;
		pistolRect.h = pistolH / 10;
		SDL_RenderCopy(renderer, pistol[i]->getTexture(), nullptr, &pistolRect);
	}

	// Draw shotgun bullets
	SDL_Rect shotgunRect;
	Vec3 shotgunScreenCoords;
	int shotgunW, shotgunH;

	for (int i = 0; i < shotgun.size(); i++){
		shotgunScreenCoords = projectionMatrix * shotgun[i]->getPos();
		SDL_QueryTexture(shotgun[i]->getTexture(), nullptr, nullptr, &shotgunW, &shotgunH);
		shotgunRect.x = static_cast<int>(shotgunScreenCoords.x - shotgunW / 20);
		shotgunRect.y = static_cast<int>(shotgunScreenCoords.y - shotgunH / 20);
		shotgunRect.w = shotgunW / 10;
		shotgunRect.h = shotgunH / 10;

		SDL_RenderCopy(renderer, shotgun[i]->getTexture(), nullptr, &shotgunRect);
	}

	if (game->getPlayer()->getshotgun() > 0) {
		SDL_Rect gunRect;
		gunRect.x = 80;
		gunRect.y = 400;
		gunRect.w = 50;
		gunRect.h = 50;
		SDL_RenderCopy(renderer, melee, nullptr, &gunRect);
	}

	// Draw knife
	SDL_Rect knifeRect;
	Vec3 knifeScreenCoords;
	int knifeW, knifeH;

	for (int i = 0; i < knife.size(); i++){
		if (knife[i]->getvisible() > 0){
			knifeScreenCoords = projectionMatrix * knife[i]->getPos();
			SDL_QueryTexture(knife[i]->getTexture(), nullptr, nullptr, &knifeW, &knifeH);
			knifeRect.x = static_cast<int>(knifeScreenCoords.x - knifeW / 20);
			knifeRect.y = static_cast<int>(knifeScreenCoords.y - knifeH / 20);
			knifeRect.w = knifeW / 10;
			knifeRect.h = knifeH / 10;
			SDL_RenderCopy(renderer, knife[i]->getTexture(), nullptr, &knifeRect);
		}
		knife[i]->decrementVisible();
	}

	if (game->getPlayer()->getHealth() > 0){
		SDL_Rect healthRect;
		healthRect.x = 10;
		healthRect.y = 13;
		healthRect.w = 100;
		healthRect.h = 100;
		SDL_RenderCopy(renderer, health, nullptr, &healthRect);

		if (game->getPlayer()->getHealth() > 1){
			SDL_Rect health1Rect;
			health1Rect.x = 40;
			health1Rect.y = 13;
			health1Rect.w = 100;
			health1Rect.h = 100;
			SDL_RenderCopy(renderer, health, nullptr, &health1Rect);

			if (game->getPlayer()->getHealth() > 2){
				SDL_Rect health2Rect;
				health2Rect.x = 70;
				health2Rect.y = 13;
				health2Rect.w = 100;
				health2Rect.h = 100;
				SDL_RenderCopy(renderer, health, nullptr, &health2Rect);
			}
		}
	}

	// Draw collectibles
	SDL_Rect healthcollectibleRect;
	Vec3 healthPickupScreenCoords;
	int healthcollectibleW, healthcollectibleH;

	if (healthPickup){
		SDL_QueryTexture(healthPickup->getTexture(), nullptr, nullptr, &healthcollectibleW, &healthcollectibleH);
		healthPickupScreenCoords = projectionMatrix * healthPickup->getPos();
		healthcollectibleRect.x = static_cast<int>(healthPickupScreenCoords.x) - healthcollectibleW / 8;
		healthcollectibleRect.y = static_cast<int>(healthPickupScreenCoords.y) - healthcollectibleH / 8;
		healthcollectibleRect.w = healthcollectibleW / 4;
		healthcollectibleRect.h = healthcollectibleH / 4;
		SDL_RenderCopy(renderer, healthPickup->getTexture(), nullptr, &healthcollectibleRect);
	}

	if (healthPickup2) {
		SDL_QueryTexture(healthPickup2->getTexture(), nullptr, nullptr, &healthcollectibleW, &healthcollectibleH);
		healthPickupScreenCoords = projectionMatrix * healthPickup2->getPos();
		healthcollectibleRect.x = static_cast<int>(healthPickupScreenCoords.x) - healthcollectibleW / 8;
		healthcollectibleRect.y = static_cast<int>(healthPickupScreenCoords.y) - healthcollectibleH / 8;
		healthcollectibleRect.w = healthcollectibleW / 4;
		healthcollectibleRect.h = healthcollectibleH / 4;
		SDL_RenderCopy(renderer, healthPickup2->getTexture(), nullptr, &healthcollectibleRect);
	}

	if (healthPickup3) {
		SDL_QueryTexture(healthPickup3->getTexture(), nullptr, nullptr, &healthcollectibleW, &healthcollectibleH);
		healthPickupScreenCoords = projectionMatrix * healthPickup3->getPos();
		healthcollectibleRect.x = static_cast<int>(healthPickupScreenCoords.x) - healthcollectibleW / 8;
		healthcollectibleRect.y = static_cast<int>(healthPickupScreenCoords.y) - healthcollectibleH / 8;
		healthcollectibleRect.w = healthcollectibleW / 4;
		healthcollectibleRect.h = healthcollectibleH / 4;
		SDL_RenderCopy(renderer, healthPickup3->getTexture(), nullptr, &healthcollectibleRect);
	}

	if (healthPickup4) {
		SDL_QueryTexture(healthPickup4->getTexture(), nullptr, nullptr, &healthcollectibleW, &healthcollectibleH);
		healthPickupScreenCoords = projectionMatrix * healthPickup4->getPos();
		healthcollectibleRect.x = static_cast<int>(healthPickupScreenCoords.x) - healthcollectibleW / 8;
		healthcollectibleRect.y = static_cast<int>(healthPickupScreenCoords.y) - healthcollectibleH / 8;
		healthcollectibleRect.w = healthcollectibleW / 4;
		healthcollectibleRect.h = healthcollectibleH / 4;
		SDL_RenderCopy(renderer, healthPickup4->getTexture(), nullptr, &healthcollectibleRect);
	}

	// Draw collectibles
	SDL_Rect itemhealthcollectibleRect;
	Vec3 itemhealthPickupScreenCoords;
	int itemhealthcollectibleW, itemhealthcollectibleH;
	if (itemhealthpickup){
		SDL_QueryTexture(itemhealthpickup->getTexture(), nullptr, nullptr, &itemhealthcollectibleW, &itemhealthcollectibleH);
		Vec3 itemhealthPickupScreenCoords = projectionMatrix * itemhealthpickup->getPos();
		itemhealthcollectibleRect.x = static_cast<int>(itemhealthPickupScreenCoords.x) - itemhealthcollectibleW / 8;
		itemhealthcollectibleRect.y = static_cast<int>(itemhealthPickupScreenCoords.y) - itemhealthcollectibleH / 8;
		itemhealthcollectibleRect.w = itemhealthcollectibleW / 4;
		itemhealthcollectibleRect.h = itemhealthcollectibleH / 4;
		SDL_RenderCopy(renderer, itemhealthpickup->getTexture(), nullptr, &itemhealthcollectibleRect);
	}

	if (itemhealthpickup2) {
		SDL_QueryTexture(itemhealthpickup2->getTexture(), nullptr, nullptr, &itemhealthcollectibleW, &itemhealthcollectibleH);
		Vec3 itemhealthPickupScreenCoords = projectionMatrix * itemhealthpickup2->getPos();
		itemhealthcollectibleRect.x = static_cast<int>(itemhealthPickupScreenCoords.x) - itemhealthcollectibleW / 8;
		itemhealthcollectibleRect.y = static_cast<int>(itemhealthPickupScreenCoords.y) - itemhealthcollectibleH / 8;
		itemhealthcollectibleRect.w = itemhealthcollectibleW / 4;
		itemhealthcollectibleRect.h = itemhealthcollectibleH / 4;
		SDL_RenderCopy(renderer, itemhealthpickup2->getTexture(), nullptr, &itemhealthcollectibleRect);
	}

	if (itemhealthpickup3) {
		SDL_QueryTexture(itemhealthpickup3->getTexture(), nullptr, nullptr, &itemhealthcollectibleW, &itemhealthcollectibleH);
		Vec3 itemhealthPickupScreenCoords = projectionMatrix * itemhealthpickup3->getPos();
		itemhealthcollectibleRect.x = static_cast<int>(itemhealthPickupScreenCoords.x) - itemhealthcollectibleW / 8;
		itemhealthcollectibleRect.y = static_cast<int>(itemhealthPickupScreenCoords.y) - itemhealthcollectibleH / 8;
		itemhealthcollectibleRect.w = itemhealthcollectibleW / 4;
		itemhealthcollectibleRect.h = itemhealthcollectibleH / 4;
		SDL_RenderCopy(renderer, itemhealthpickup3->getTexture(), nullptr, &itemhealthcollectibleRect);
	}

	if (itemhealthpickup4) {
		SDL_QueryTexture(itemhealthpickup4->getTexture(), nullptr, nullptr, &itemhealthcollectibleW, &itemhealthcollectibleH);
		Vec3 itemhealthPickupScreenCoords = projectionMatrix * itemhealthpickup4->getPos();
		itemhealthcollectibleRect.x = static_cast<int>(itemhealthPickupScreenCoords.x) - itemhealthcollectibleW / 8;
		itemhealthcollectibleRect.y = static_cast<int>(itemhealthPickupScreenCoords.y) - itemhealthcollectibleH / 8;
		itemhealthcollectibleRect.w = itemhealthcollectibleW / 4;
		itemhealthcollectibleRect.h = itemhealthcollectibleH / 4;
		SDL_RenderCopy(renderer, itemhealthpickup4->getTexture(), nullptr, &itemhealthcollectibleRect);
	}

	if (game->getPlayer()->getitemhealth() > 0){
		SDL_Rect itemRect;
		itemRect.x = 40;
		itemRect.y = 500;
		itemRect.w = 50;
		itemRect.h = 50;
		SDL_RenderCopy(renderer, itemhealth, nullptr, &itemRect);

		if (game->getPlayer()->getitemhealth() > 1) {
			SDL_Rect itemRect1;
			itemRect1.x = 60;
			itemRect1.y = 500;
			itemRect1.w = 50;
			itemRect1.h = 50;
			SDL_RenderCopy(renderer, itemhealth, nullptr, &itemRect1);

			if (game->getPlayer()->getitemhealth() > 2) {
				SDL_Rect itemRect2;
				itemRect2.x = 80;
				itemRect2.y = 500;
				itemRect2.w = 50;
				itemRect2.h = 50;
				SDL_RenderCopy(renderer, itemhealth, nullptr, &itemRect2);

				if (game->getPlayer()->getitemhealth() > 3) {
					SDL_Rect itemRect3;
					itemRect3.x = 60;
					itemRect3.y = 500;
					itemRect3.w = 50;
					itemRect3.h = 50;
					SDL_RenderCopy(renderer, itemhealth, nullptr, &itemRect3);
				}
			}
		}
	}

	// Draw enemies
	SDL_Rect enemyRect;
	Vec3 enemyScreenCoords;
	int enemyW, enemyH;

	for (int i = 0; i < enemies.size(); i++){
		enemyScreenCoords = projectionMatrix * enemies[i]->getPos();
		SDL_QueryTexture(enemies[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);
		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;
		SDL_RenderCopy(renderer, enemies[i]->getTexture(), nullptr, &enemyRect);
	}

	for (int i = 0; i < enemies1.size(); i++){
		enemyScreenCoords = projectionMatrix * enemies1[i]->getPos();
		SDL_QueryTexture(enemies1[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);
		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;
		SDL_RenderCopy(renderer, enemies1[i]->getTexture(), nullptr, &enemyRect);
	}

	for (int i = 0; i < enemies2.size(); i++){
		enemyScreenCoords = projectionMatrix * enemies2[i]->getPos();
		SDL_QueryTexture(enemies2[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);
		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;
		SDL_RenderCopy(renderer, enemies2[i]->getTexture(), nullptr, &enemyRect);
	}

	for (int i = 0; i < enemies3.size(); i++){
		enemyScreenCoords = projectionMatrix * enemies3[i]->getPos();
		SDL_QueryTexture(enemies3[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);
		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;
		SDL_RenderCopy(renderer, enemies3[i]->getTexture(), nullptr, &enemyRect);
	}
#pragma endregion

	// Render the player
	game->RenderPlayer(0.10f);
	// Render all things in the renderer
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event){

	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);
	
	// Player
	Body* player = game->getPlayer();
	
	// Sphere
	Sphere boundingSphere2;
	boundingSphere2.x = player->getPos().x;	// get pos.x of the sphere equal to player
	boundingSphere2.y = player->getPos().y;	// get pos.y of the sphere equal to player
	boundingSphere2.r = 1.0f;
	
	// Player object
	PhysicsObject* P1 = new PhysicsObject();
	P1->setPos(player->getPos());
	P1->setVel(player->getVel());
	P1->setAccel(player->getAccel());
	P1->setAngle(player->getOrientation());
	P1->setAngularVel(player->getRotation());
	P1->setAngularAccel(player->getAngular());
	P1->setMass(player->getMass());
	P1->setBoundingSphere(boundingSphere2);

#pragma region Buttons_and_Events

	if (event.button.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
		std::vector<Ammunition*> newpistol;
		newpistol = game->getPlayer()->firePistolBullet();

		for (int i = 0; i < newpistol.size(); ++i){
			newpistol[i]->setTexture(pistolbullet);
			pistol.push_back(newpistol[i]);
		}
	}

	if (event.button.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
		std::vector<Ammunition*> newknife;
		newknife = game->getPlayer()->stabbing();

		for (int i = 0; i < newknife.size(); ++i){
			newknife[i]->setTexture(knifes);
			knife.push_back(newknife[i]);
		}
	}

	if (event.button.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
		std::vector<Ammunition*> newshotgun;
		newshotgun = game->getPlayer()->fireshotgunBullet();

		for (int i = 0; i < newshotgun.size(); ++i){
			newshotgun[i]->setTexture(shotgunbullet);
			shotgun.push_back(newshotgun[i]);
		}
	}

	if (event.key.keysym.scancode == SDL_SCANCODE_E){

		if (weaponPickup && Physics::SphereSphereCollision(*weaponPickup, *P1) == true){
			game->getPlayer()->restoreshotgun(1.0f) == true;
			delete weaponPickup;
			weaponPickup = nullptr;
			game->getPlayer()->setAltWeaponAvailable(true);
			game->getPlayer()->setWeaponType(1);
		}

		if (healthPickup && Physics::SphereSphereCollision(*healthPickup, *P1) == true){
			delete healthPickup;
			healthPickup = nullptr;
			game->getPlayer()->restoreItemHealth(1.0f) == true;
			delete itemhealthpickup;
			itemhealthpickup = nullptr;
		}

		if (healthPickup2 && Physics::SphereSphereCollision(*healthPickup2, *P1) == true) {
			delete healthPickup2;
			healthPickup2 = nullptr;
			game->getPlayer()->restoreItemHealth(1.0f) == true;
			delete itemhealthpickup2;
			itemhealthpickup2 = nullptr;
		}

		if (healthPickup3 && Physics::SphereSphereCollision(*healthPickup3, *P1) == true) {
			delete healthPickup3;
			healthPickup3 = nullptr;
			game->getPlayer()->restoreItemHealth(1.0f) == true;
			delete itemhealthpickup3;
			itemhealthpickup3 = nullptr;
		}

		if (healthPickup4 && Physics::SphereSphereCollision(*healthPickup4, *P1) == true) {
			delete healthPickup4;
			healthPickup4 = nullptr;
			game->getPlayer()->restoreItemHealth(1.0f) == true;
			delete itemhealthpickup4;
			itemhealthpickup4 = nullptr;
		}

		if ((ammoPickup && Physics::SphereSphereCollision(*ammoPickup, *P1) == true)){
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammoPickup;
			ammoPickup = nullptr;
		}

		if ((ammo1Pickup && Physics::SphereSphereCollision(*ammo1Pickup, *P1) == true)) {
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammo1Pickup;
			ammo1Pickup = nullptr;
		}

		if ((ammo2Pickup && Physics::SphereSphereCollision(*ammo2Pickup, *P1) == true)) {
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammo2Pickup;
			ammo2Pickup = nullptr;
		}

		if ((ammo3Pickup && Physics::SphereSphereCollision(*ammo3Pickup, *P1) == true)) {
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammo3Pickup;
			ammo3Pickup = nullptr;
		}

		if ((ammo4Pickup && Physics::SphereSphereCollision(*ammo4Pickup, *P1) == true)) {
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammo4Pickup;
			ammo4Pickup = nullptr;
		}

		if ((shotgunammoPickup && Physics::SphereSphereCollision(*shotgunammoPickup, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup;
			shotgunammoPickup = nullptr;
		}

		if ((shotgunammoPickup1 && Physics::SphereSphereCollision(*shotgunammoPickup1, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup1;
			shotgunammoPickup1 = nullptr;
		}

		if ((shotgunammoPickup2 && Physics::SphereSphereCollision(*shotgunammoPickup2, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup2;
			shotgunammoPickup2 = nullptr;
		}

		if ((shotgunammoPickup3 && Physics::SphereSphereCollision(*shotgunammoPickup3, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup3;
			shotgunammoPickup3 = nullptr;
		}

		if ((shotgunammoPickup4 && Physics::SphereSphereCollision(*shotgunammoPickup4, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup4;
			shotgunammoPickup4 = nullptr;
		}

		if (keyPickup && Physics::SphereSphereCollision(*keyPickup, *P1) == true) {
			game->getPlayer()->restorevaccine(1.0f) == true;
			delete keyPickup;
			keyPickup = nullptr;
		}

		if (keyPickup1 && Physics::SphereSphereCollision(*keyPickup1, *P1) == true) {
			game->getPlayer()->restorevaccine(1.0f) == true;
			delete keyPickup1;
			keyPickup1 = nullptr;
		}

		if (keyPickup2 && Physics::SphereSphereCollision(*keyPickup2, *P1) == true) {
			game->getPlayer()->restorevaccine(1.0f) == true;
			delete keyPickup2;
			keyPickup2 = nullptr;
		}

		if (keyPickup3 && Physics::SphereSphereCollision(*keyPickup3, *P1) == true) {
			game->getPlayer()->restorevaccine(1.0f) == true;
			delete keyPickup3;
			keyPickup3 = nullptr;
		}

		if (keyPickup4 && Physics::SphereSphereCollision(*keyPickup4, *P1) == true) {
			game->getPlayer()->restorevaccine(1.0f) == true;
			delete keyPickup4;
			keyPickup4 = nullptr;
		}
	}



	if (event.key.keysym.scancode == SDL_SCANCODE_F) {
		if (game->getPlayer()->getvaccine()) {// if item in the inventory
			game->getPlayer()->restorevaccine(1.0f);
			game->getPlayer()->setvaccine(0.0f);//make it destroy when press f
		}

		if (game->getPlayer()->getvaccine()) {// if item in the inventory
			game->getPlayer()->restorevaccine(1.0f);
			game->getPlayer()->setvaccine(0.0f);//make it destroy when press f

		}
	}

	if (event.key.keysym.scancode == SDL_SCANCODE_R) {
		// reload weapon
		if (game->getPlayer()->getammo()) {
			game->getPlayer()->OnReload(100) == true;
			game->getPlayer()->setammo(0.0f);
		}
	}

	if (event.key.keysym.scancode == SDL_SCANCODE_R) {

		//reload weapon
			if(game->getPlayer()->getshotgunammo()){
				game->getPlayer()->OnReload2(600) == true;
				game->getPlayer()->setshotgunammo(0.0f);
			}

		//reload weapon
		if (game->getPlayer()->getshotgunammo()) {
			game->getPlayer()->OnReload2(600) == true;
			game->getPlayer()->setshotgunammo(0.0f);
		}

	}

#pragma endregion
}

bool Scene1::getDead(){

	if (game->getPlayer()->getHealth() <= 0)
		return true;
	
	return false;
}

Vec3 Scene1::getMousePosition()
{
	Uint32 buttons;
	int x, y; // Mouse position in screen coords
	buttons = SDL_GetMouseState(&x, &y);
	Vec3 mouseScreenCoords(Vec3(float(x), float(y), 0.0f));
	Vec3 mouseWorldCoords = inverseProjection * (mouseScreenCoords);
	return mouseWorldCoords;
}

void Scene1::GenerateSceneLayout()
{
	// Amount of tiles on the width and height
	gridWidth = 30;
	gridHeight = 15;
	// Level layout (x value = gridWidth and y value = gridHeight) (first number = y, second number = x)
	// rows = x & columns = y
	int levelData[15][30] = {
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, },
	{ 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, },
	{ 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 1, 3, },
	{ 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 3, },
	{ 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, },
	{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, }
	};

	tiles.resize(gridHeight);

	for (int i = 0; i < gridHeight; i++)
		tiles[i].resize(gridWidth);

	Node* n;
	BackgroundTile* t;
	int i, j, label;
	i = 0;
	j = 0;
	label = 0;

	for (int row = 0; row < gridHeight; row++){

		for (int column = 0; column < gridWidth; column++){

			int id = levelData[row][column];

			// Position in pixels
			Vec3 startPos = Vec3(0.0f, 0.0f, 0.0f);
			Vec3 endPos = Vec3(0.0f, 0.0f, 0.0f);

			// Set the position to have the origin top left
			endPos.x = (startPos.x + column * tileWidth + (tileWidth * 0.5f));
			endPos.y = (startPos.y + row * tileHeight + (tileHeight * 0.5f));
			
			// Transverse the position from viewport to game
			Vec3 position = Vec3(endPos.x, endPos.y, 0.0f);
			position = MMath::inverse(projectionMatrix) * position;
			
			// Set the position to the game coordinates
			endPos.x = (position.x);
			endPos.y = (position.y);
			
			// Set node
			n = new Node(label, endPos);
			nodes.push_back(n);
			
			// Set the background tile
			if (id == 1 || id == 3)
				t = new BackgroundTile(n, true);
			else
				t = new BackgroundTile(n, false);
			
			// Set the tile
			t->AddTile(renderer, column, row, id, label, tileWidth, tileHeight, game->getProjectionMatrix());
			tiles[row][column] = t;
			label++;
		}
	}
}

void Scene1::CalculateConnectionWeights(){
	int rows = tiles.size();
	int columns = tiles[0].size();

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			//						i+1, j
			//		i, j-1			  i, j			 i, j+1
			//						i-1, j

			int from = tiles[i][j]->GetNode()->GetLabel();
			// Left is i, j-1
			if (j > 0 && tiles[i][j - 1]->HasNode()) {
				int to = tiles[i][j - 1]->GetNode()->GetLabel();
				graph->AddWeightConnection(from, to, tileWidth);
			}

			// Right is i, j+1
			if (j < columns - 1 && tiles[i][j + 1]->HasNode()) {
				int to = tiles[i][j + 1]->GetNode()->GetLabel();
				graph->AddWeightConnection(from, to, tileWidth);
			}

			// Above is i+1, j
			if (i < rows - 1 && tiles[i + 1][j]->HasNode()) {
				int to = tiles[i + 1][j]->GetNode()->GetLabel();
				graph->AddWeightConnection(from, to, tileWidth);
			}

			// Below is i-1, j
			if (i > 0 && tiles[i - 1][j]->HasNode()) {
				int to = tiles[i - 1][j]->GetNode()->GetLabel();
				graph->AddWeightConnection(from, to, tileWidth);
			}
		}
	}
}

bool Scene1::LoadImage(string pathName_)
{
	// Loads in the wall image and set the texture to the walls
	surfacePtr = IMG_Load(pathName_.c_str());
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	
	// Null pointer checks
	if (surfacePtr == nullptr) {
		cerr << "Image cannot be loaded!" << endl;
		return false;
	}
	
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}
	
	SDL_FreeSurface(surfacePtr);
	return true;
}

bool Scene1::nextScene() { //win condition to change scene
	
	if (game->getPlayer()->getvaccine() > 4) {
		
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));

		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 6;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		
		// Push the event
		SDL_PushEvent(&event);
		pressed = true;
	}
	return true;
}