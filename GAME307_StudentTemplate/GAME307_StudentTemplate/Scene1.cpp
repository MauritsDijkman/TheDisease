#include "Scene1.h"
#include "VMath.h"
#include <Node.h>

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
	// Spawn to right
	for (int i = 0; i < 10; i++){
		// Create enemy and add in the list
		enemies.push_back(new EnemyCharacter());
		// Set stats of the current enemy
		enemies[i]->setPos(Vec3(30.0f - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies[i]->setBoundingSphere(Sphere(0.5f));
		enemies[i]->setTexture(texturePtr);
	}
	// Spawn to left
	for (int i = 0; i < 10; i++){
		// Create enemy and add in the list
		enemies1.push_back(new EnemyCharacter());
		// Set stats of the current enemy
		enemies1[i]->setPos(Vec3(-227.0f - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies1[i]->setBoundingSphere(Sphere(0.5f));
		enemies1[i]->setTexture(texturePtr);
	}
	// Spawn up
	for (int i = 0; i < 10; i++){
		// Create enemy and add in the list
		enemies2.push_back(new EnemyCharacter());
		// Set stats of the current enemy
		enemies2[i]->setPos(Vec3(xAxis - 3.0f, 230 - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies2[i]->setBoundingSphere(Sphere(0.5f));
		enemies2[i]->setTexture(texturePtr);
	}
	// Spawn down
	for (int i = 0; i < 10; i++){
		// Create enemy and add in the list
		enemies3.push_back(new EnemyCharacter());
		// Set stats of the current enemy
		enemies3[i]->setPos(Vec3(xAxis - 3.0f, -226 - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies3[i]->setBoundingSphere(Sphere(0.5f));
		enemies3[i]->setTexture(texturePtr);
	}
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
	// Load health image
	LoadImage("Assets/Ethan/medicine.png");
	// Create health pickup
	itemhealthpickup = new Object();
	itemhealthpickup->setTexture(texturePtr);
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
	// Load shotgun picked up icon and set the texture
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

	// Load shotgun picked up icon and set the texture
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
	shotgunammoPickup->setPos(Vec3(5.0f, 10.0f, 0.0f));
	shotgunammoPickup->setBoundingSphere(Sphere(0.25f));
	shotgunammoPickup->setTexture(shotgunammo);
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
	// Set player image to PacMan
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
#pragma endregion
	// End of character set ups
	return true;
}

void Scene1::OnDestroy()
{
	
	for (EnemyCharacter* EnemyCharacter : enemies,enemies,enemies2,enemies3) {
		SDL_DestroyTexture(EnemyCharacter->getTexture());
		delete EnemyCharacter;
	}
	
	//for (EnemyCharacter* EnemyCharacter : enemies1){
	//	delete EnemyCharacter;
	//}
	//SDL_DestroyRenderer(renderer);
	//for (EnemyCharacter* EnemyCharacter : enemies2)
	//	delete EnemyCharacter; SDL_DestroyRenderer(renderer);
	//for (EnemyCharacter* EnemyCharacter : enemies3)
	//	delete EnemyCharacter; SDL_DestroyRenderer(renderer);
	//SDL_DestroyRenderer(renderer);
	
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
	blinky->Update(deltaTime); enemy->Update(deltaTime);
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
	PhysicsObject* AI = new PhysicsObject();
	AI->setPos(blinky->getBody()->getPos());//
	AI->setVel(blinky->getBody()->getVel());
	AI->setAccel(blinky->getBody()->getAccel());
	AI->setAngle(blinky->getBody()->getOrientation());
	AI->setAngularVel(blinky->getBody()->getRotation());
	AI->setAngularAccel(blinky->getBody()->getAngular());
	AI->setMass(blinky->getBody()->getMass());
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

	Physics::SimpleNewtonMotion(*P1, deltaTime);
	Physics::SimpleNewtonMotion(*AI, deltaTime);

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
	// Player hits collectibles
	if (healthPickup){
		if (Physics::SphereSphereCollision(*P1, *healthPickup) == true)
			game->getPlayer()->Update(-deltaTime);
	}
	if (weaponPickup){
		if (Physics::SphereSphereCollision(*weaponPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}
	if (ammoPickup){
		if (Physics::SphereSphereCollision(*ammoPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}

	if (shotgunammoPickup) {
		if (Physics::SphereSphereCollision(*shotgunammoPickup, *P1) == true)
			game->getPlayer()->Update(-deltaTime);
	}
#pragma endregion

#pragma region Enemy & Bullet movement
	// Bullets movement
	for (int i = 0; i < pistol.size(); i++)
		Physics::SimpleNewtonMotion(*pistol[i], deltaTime);
	// Bullets movement
	for (int i = 0; i < shotgun.size(); i++)
		Physics::SimpleNewtonMotion(*shotgun[i], deltaTime);
	
	//vector <int> ToBeDelete;

	// Enemy hits player
	for (int i = 0; i < enemies.size(); i++){
		if (Physics::SphereSphereCollision(*enemies[i], *P1) == true){
			game->getPlayer()->takeDamage(1.0f);
			enemies.erase(enemies.begin() + i);
			//ToBeDelete.push_back(i);
		}
	}
	//for (auto item : ToBeDelete) {
	//	enemies.erase(enemies.begin() + item);
	//}
	//ToBeDelete.clear();

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
	//vector <int> ToBeDelete;

	// Bullet hits enemy
	for (int i = 0; i < pistol.size(); i++){
		for (int j = 0; j < enemies.size(); j++){
			if (Physics::SphereSphereCollision(*pistol[i], *enemies[j]) == true){
				pistol.erase(pistol.begin() + i);
				enemies[j]->EnemytakeDamage(0.5f);
				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);
					//ToBeDelete.push_back(j);
				break;
			}
		}
	}
	//for (auto item : ToBeDelete) {
	//	enemies.erase(enemies.begin() + item);
	//}
	//ToBeDelete.clear();
#pragma endregion

#pragma region Ammo, collide and enemies
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

	for (int i = 0; i < knife.size(); i++){
		for (int j = 0; j < enemies.size(); j++){
			if (Physics::SphereSphereCollision(*knife[i], *enemies[j]) == true){
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

#pragma region Location, height and length
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

	if (game->getPlayer()->getammo() > 0){
		SDL_Rect ammoRect;
		ammoRect.x = 80;
		ammoRect.y = 450;
		ammoRect.w = 50;
		ammoRect.h = 50;
		SDL_RenderCopy(renderer, ammo, nullptr, &ammoRect);
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

	if (game->getPlayer()->getshotgunammo() > 0) {
		SDL_Rect shotgunammoRect;
		shotgunammoRect.x = 80;
		shotgunammoRect.y = 300;
		shotgunammoRect.w = 50;
		shotgunammoRect.h = 50;
		SDL_RenderCopy(renderer, shotgunammo, nullptr, &shotgunammoRect);
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

	if (game->getPlayer()->getitemhealth() > 0){
		SDL_Rect itemRect;
		itemRect.x = 80;
		itemRect.y = 500;
		itemRect.w = 50;
		itemRect.h = 50;
		SDL_RenderCopy(renderer, itemhealth, nullptr, &itemRect);
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

#pragma region Buttons
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

		if ((ammoPickup && Physics::SphereSphereCollision(*ammoPickup, *P1) == true)){
			game->getPlayer()->restoreammo(1.0f) == true;
			delete ammoPickup;
			ammoPickup = nullptr;
		}

		if ((shotgunammoPickup && Physics::SphereSphereCollision(*shotgunammoPickup, *P1) == true)) {
			game->getPlayer()->restoreshotgunammo(1.0f) == true;
			delete shotgunammoPickup;
			shotgunammoPickup = nullptr;
		}
	}

	if (event.key.keysym.scancode == SDL_SCANCODE_F){
		if (game->getPlayer()->getitemhealth()){// if item health in the inventory
			game->getPlayer()->restoreHealth(0.5f) == true;
			game->getPlayer()->setitemhealth(0.0f);//make it destroy when press f

		}
		
	}

	if (event.key.keysym.scancode == SDL_SCANCODE_R) {

		if (game->getPlayer()->getammo()) {
			game->getPlayer()->OnReload(100) == true;
			game->getPlayer()->setammo(0.0f);
		}

	}

	if (event.key.keysym.scancode == SDL_SCANCODE_R) {
		
			if(game->getPlayer()->getshotgunammo()){
				game->getPlayer()->OnReload2(100) == true;
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
