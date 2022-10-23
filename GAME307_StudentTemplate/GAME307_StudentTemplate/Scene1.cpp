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
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}

	// Enemy follows given targetss
	if (enemy)
	{
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

	// Load the crouton image and set the texture
	surfacePtr = IMG_Load("bullet.2.png");
	bullet = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	LoadImage("The Unbread.png");

	// Spawn 10 enemies
	for (int i = 0; i < 10; i++)
	{
		// Create enemy and add in the list
		enemies.push_back(new EnemyCharacter());

		// Set stats of the current enemy
		enemies[i]->setPos(Vec3(xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f));//xAxis - 3.0f, yAxis - 4.0f - 3.0f * i, 0.0f
		enemies[i]->setBoundingSphere(Sphere(0.5f));
		enemies[i]->setTexture(texturePtr);
	}

	// Set the health of the player
	game->getPlayer()->setHealth(1.0f);

	// Load health icon and set the texture
	surfacePtr = IMG_Load("Assets/Ethan/medicine.png");
	health = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (health == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	LoadImage("Assets/Ethan/medicine.png");


	// Create health pickup
	healthPickup = new Object();

	// Set stats
	healthPickup->setPos(Vec3(10.0f, 9.0f, 0.0f));
	healthPickup->setBoundingSphere(Sphere(0.5f));
	healthPickup->setTexture(texturePtr);


	// Load shotgun picked up icon and set the texture
	surfacePtr = IMG_Load("Shotgun96.png");
	melee = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	// Null pointer checks
	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (melee == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	LoadImage("Shotgun96.png");

	// Create weapon pickup
	weaponPickup = new Object();

	// Set stats
	weaponPickup->setPos(Vec3(3.0f, 13.0f, 0.0f));
	weaponPickup->setBoundingSphere(Sphere(0.25f));
	weaponPickup->setTexture(texturePtr);


	// Temporary border walls
	wallLeft = new Plane(Vec3(1.0f, 0.0f, 0.0f), 0.0f);
	wallRight = new Plane(Vec3(-1.0f, 0.0f, 0.0f), xAxis);
	wallTop = new Plane(Vec3(0.0f, -1.0f, 0.0f), yAxis);
	wallBottom = new Plane(Vec3(0.0f, 1.0f, 0.0f), 0.0f);

	LoadImage("Assets/Ethan/wall.png");

	// Load background
	background = new GameObject(renderer, "Assets/Background.png");

	// Making the level
	level = new Level(NUMWALL);
	level->makeLevel(1); //pos of wall
	level->setWallTextures(texturePtr);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);




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

	printf("Neighbours of 93: \n");
	int nodeLabel;
	for (auto nodeLabel : graph->GetNeighbours(93))
		printf("Node %i, ", nodeLabel);



	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Assets/humans/idle_human2.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

#pragma region Blinky
	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this))
		return false;

	image = IMG_Load("Blinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{
		blinky->setTexture(texture);
		SDL_FreeSurface(image);
	}
#pragma endregion

#pragma region Enemy
	// Set up characters, choose good values for the constructor
		// or use the defaults, like this
	enemy = new Enemy(game->getPlayer());
	if (!enemy->OnCreate(this))
		return false;

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{
		enemy->setTexture(texture);
		SDL_FreeSurface(image);
	}
#pragma endregion

	// End of character set ups
	return true;
}

void Scene1::OnDestroy()
{
	for (EnemyCharacter* EnemyCharacter : enemies)
		delete EnemyCharacter;

	SDL_DestroyRenderer(renderer);
}

void Scene1::Update(const float deltaTime)
{
	// Updates the location of the orthograpic each frame
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	// For moving camera view
	/**/
	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;

	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;
	/**/

	// For static view
	/**
	float minX = 0;
	float maxX = xAxis;

	float minY = 0;
	float maxY = yAxis;
	/**/

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

	//Create physicobject from the kinematicbody for npc
	Sphere boundingSphere;
	boundingSphere.x = blinky->getBody()->getPos().x;// get pos.x of the sphere equal to npc //myNPC->getPos().x
	boundingSphere.y = blinky->getBody()->getPos().y;// get pos.y of the sphere equal to npc //myNPC->getPos().y
	boundingSphere.r = 0.4f;

	Sphere boundingSphere2;
	boundingSphere2.x = player->getPos().x;// get pos.x of the sphere equal to player
	boundingSphere2.y = player->getPos().y;// get pos.y of the sphere equal to player
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

	// Player hits walls
	for (int i = 0; i < level->getWallNum(); i++)
	{
		if (Physics::CircleRectCollision(*P1, *level->getWall(i)) == true)
		{
			game->getPlayer()->Update(-deltaTime);
			Physics::SimpleNewtonMotion(*P1, -deltaTime);
		}
	}

	// Player hits collectibles
	if (healthPickup)
	{
		if (Physics::SphereSphereCollision(*P1, *healthPickup) == true)
		{
			if (game->getPlayer()->restoreHealth(1.0f) == true)
			{
				delete healthPickup;
				healthPickup = nullptr;
			}
		}
	}

	if (weaponPickup)
	{
		if (Physics::SphereSphereCollision(*weaponPickup, *P1) == true)
		{
			P1->setAltWeaponAvailable(true);
			P1->setWeaponType(1);

			game->getPlayer()->Update(-deltaTime);
			game->getPlayer()->restoreshotgun(1.0f) == true;

			delete weaponPickup;
			weaponPickup = nullptr;
		}
	}

	// Bullets movement
	for (int i = 0; i < Bullets.size(); i++)
		Physics::SimpleNewtonMotion(*Bullets[i], deltaTime);

	// Enemy hits player
	for (int i = 0; i < enemies.size(); i++)
	{
		if (Physics::SphereSphereCollision(*enemies[i], *P1) == true)
		{
			game->getPlayer()->takeDamage(1.0f);
			enemies.erase(enemies.begin() + i);
		}
	}

	// Enemy movement
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->SeekPlayer(player->getPos());
		Physics::SimpleNewtonMotion(*enemies[i], deltaTime);
	}

	// Bullet hits enemy
	for (int i = 0; i < Bullets.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			if (Physics::SphereSphereCollision(*Bullets[i], *AI) == true)
			{
				Bullets.erase(Bullets.begin() + i);
				enemies[j]->takeDamage(1.0f);

				if (enemies[j]->getHealth() <= 0)
					enemies.erase(enemies.begin() + j);

				break;
			}
		}
	}
#pragma endregion

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Render all the background tiles (including their nodes)
	/**/
	// Place the tiles for the amount of columns and rows
	for (int row = 0; row < gridHeight; row++)
	{
		for (int column = 0; column < gridWidth; column++)
		{
			tiles[row][column]->Render(renderer, game->getProjectionMatrix());
		}
	}
	/**/


	// Render any npc's
	blinky->render(0.15f);
	enemy->render(0.15f);

	//Draws all the walls
	SDL_Rect WallRect;
	Vec3 wallScreenCoords;
	int WallW, WallH;

	for (int i = 0; i < NUMWALL; ++i) {
		SDL_QueryTexture(level->getWall(i)->getTexture(), nullptr, nullptr, &WallW, &WallH);
		wallScreenCoords = projectionMatrix * level->getWall(i)->getPos();
		WallRect.x = static_cast<int> (wallScreenCoords.x) - 30;//30
		WallRect.y = static_cast<int> (wallScreenCoords.y) - 30;
		WallRect.w = 70;//80
		WallRect.h = 70;
		SDL_RenderCopy(renderer, level->getWall(i)->getTexture(), nullptr, &WallRect);
	}

	if (weaponPickup)
	{
		SDL_Rect collectibleRect;
		Vec3 weaponPickupScreenCoords;
		int collectibleW, collectibleH;

		SDL_QueryTexture(weaponPickup->getTexture(), nullptr, nullptr, &collectibleW, &collectibleH);

		weaponPickupScreenCoords = projectionMatrix * weaponPickup->getPos();
		collectibleRect.x = static_cast<int>(weaponPickupScreenCoords.x) - collectibleW / 4;
		collectibleRect.y = static_cast<int>(weaponPickupScreenCoords.y) - collectibleH / 4;
		collectibleRect.w = collectibleW / 2;
		collectibleRect.h = collectibleH / 2;

		SDL_RenderCopy(renderer, weaponPickup->getTexture(), nullptr, &collectibleRect);
	}

	//Draw Bullets
	SDL_Rect bulletRect;
	Vec3 bulletScreenCoords;
	int bulletW, bulletH;

	for (int i = 0; i < Bullets.size(); i++)
	{
		bulletScreenCoords = projectionMatrix * Bullets[i]->getPos();
		SDL_QueryTexture(Bullets[i]->getTexture(), nullptr, nullptr, &bulletW, &bulletH);

		bulletRect.x = static_cast<int>(bulletScreenCoords.x - bulletW / 20);
		bulletRect.y = static_cast<int>(bulletScreenCoords.y - bulletH / 20);
		bulletRect.w = bulletW / 10;
		bulletRect.h = bulletH / 10;

		SDL_RenderCopy(renderer, Bullets[i]->getTexture(), nullptr, &bulletRect);
	}

	if (game->getPlayer()->getshotgun() > 0)
	{
		SDL_Rect gunRect;

		gunRect.x = 70;
		gunRect.y = 500;
		gunRect.w = 50;
		gunRect.h = 50;
		SDL_RenderCopy(renderer, melee, nullptr, &gunRect);
	}

	if (game->getPlayer()->getHealth() > 0)
	{
		SDL_Rect healthRect;

		healthRect.x = 10;
		healthRect.y = 13;
		healthRect.w = 100;
		healthRect.h = 100;

		SDL_RenderCopy(renderer, health, nullptr, &healthRect);

		if (game->getPlayer()->getHealth() > 1)
		{
			SDL_Rect health1Rect;

			health1Rect.x = 40;
			health1Rect.y = 13;
			health1Rect.w = 100;
			health1Rect.h = 100;

			SDL_RenderCopy(renderer, health, nullptr, &health1Rect);

			if (game->getPlayer()->getHealth() > 2)
			{
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
	SDL_Rect collectibleRect;
	Vec3 healthPickupScreenCoords;
	int collectibleW, collectibleH;

	if (healthPickup)
	{
		SDL_QueryTexture(healthPickup->getTexture(), nullptr, nullptr, &collectibleW, &collectibleH);
		healthPickupScreenCoords = projectionMatrix * healthPickup->getPos();

		collectibleRect.x = static_cast<int>(healthPickupScreenCoords.x) - collectibleW / 8;
		collectibleRect.y = static_cast<int>(healthPickupScreenCoords.y) - collectibleH / 8;
		collectibleRect.w = collectibleW / 4;
		collectibleRect.h = collectibleH / 4;

		SDL_RenderCopy(renderer, healthPickup->getTexture(), nullptr, &collectibleRect);
	}

	// Draw enemies
	SDL_Rect enemyRect;
	Vec3 enemyScreenCoords;
	int enemyW, enemyH;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemyScreenCoords = projectionMatrix * enemies[i]->getPos();
		SDL_QueryTexture(enemies[i]->getTexture(), nullptr, nullptr, &enemyW, &enemyH);

		enemyRect.x = static_cast<int>(enemyScreenCoords.x - enemyW / 2);//1
		enemyRect.y = static_cast<int>(enemyScreenCoords.y - enemyH / 2);
		enemyRect.w = enemyW;
		enemyRect.h = enemyH;

		SDL_RenderCopy(renderer, enemies[i]->getTexture(), nullptr, &enemyRect);
	}

	// Render the player
	game->RenderPlayer(0.10f);

	// Render all things in the renderer
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);

	Vec3 mousePos = getMousePosition();

	if (event.button.type == SDL_MOUSEBUTTONUP
		&& event.button.button == SDL_BUTTON_LEFT)
	{
		//if (clyde->clicked(mousePos))
		//	printf("Mouse clicked inside clyde!");
	}

	if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		std::vector<Ammunition*> newBullets;
		newBullets = game->getPlayer()->fireBullet();
		for (int i = 0; i < newBullets.size(); ++i) {
			newBullets[i]->setTexture(bullet);
			Bullets.push_back(newBullets[i]);
			//get bullet to update with player

		}
	}
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

	for (int row = 0; row < gridHeight; row++)
	{
		for (int column = 0; column < gridWidth; column++)
		{
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

			n = new Node(label, endPos);
			nodes.push_back(n);

			if (id == 1 || id == 3)
				t = new BackgroundTile(n, true);
			else
				t = new BackgroundTile(n, false);

			t->AddTile(renderer, column, row, id, label, tileWidth, tileHeight, game->getProjectionMatrix());


			tiles[row][column] = t;

			label++;
		}
	}
}



//CreateTiles(30, 15);

/**
int label = 0;
Node* n;
BackgroundTile* bgT;

tiles.resize(15);
for (int i = 0; i < 15; i++)
	tiles[i].resize(30);

// Place the tiles for the amount of columns and rows
for (int row = 0; row < gridHeight; row++)
{
	for (int column = 0; column < gridWidth; column++)
	{

		int id = levelData[row][column];

		bgT = new BackgroundTile(n);
		bgT->AddTile(renderer, row, column, id, label, tileWidth, tileHeight, game->getProjectionMatrix());

		//tiles[row][column] = bgT;
		tiles[row][column] = bgT;

		label++;
	}
}
/**/


void Scene1::CreateTiles(int rows_, int columns_)
{
	/**
	tiles.resize(columns_);

	for (int i = 0; i < columns_; i++)
		tiles[i].resize(rows_);

	Node* n;
	BackgroundTile* t;
	int i, j, label;
	i = 0;
	j = 0;
	label = 0;

	for (int row = 0; row < gridHeight; row++)
	{
		for (int column = 0; column < gridWidth; column++)
		{
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


			n = new Node(label, endPos);
			t = new BackgroundTile(n);
			//n->SetTile(t);

			nodes.push_back(n);
			tiles[row][column] = t;

			label++;
		}
	}
	/**/


	/**
	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		// Do stuff for row, where y stays constant
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			n = new Node(label, Vec3(x, y, 0.0f));
			t = new BackgroundTile(n);
			//n->SetTile(t);

			nodes.push_back(n);
			tiles[i][j] = t;

			label++;
			j++;
		}

		j = 0;
		i++;
	}
	/**/

}

void Scene1::CalculateConnectionWeights()
{
	int rows = tiles.size();
	int columns = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
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
