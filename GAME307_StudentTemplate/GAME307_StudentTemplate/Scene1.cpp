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
	myNPC = NULL;
}

Scene1::~Scene1()
{
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

bool Scene1::OnCreate()
{
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

	//temporary border walls
	wallLeft = new Plane(Vec3(1.0f, 0.0f, 0.0f), 0.0f);//1.0f, 0.0f, 0.0f), 0.0f
	wallRight = new Plane(Vec3(-1.0f, 0.0f, 0.0f), xAxis);
	wallTop = new Plane(Vec3(0.0f, -1.0f, 0.0f), yAxis);
	wallBottom = new Plane(Vec3(0.0f, 1.0f, 0.0f), 0.0f);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

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
		std::cerr << "Can't open the image Blinky" << std::endl;
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

	if (image == nullptr)
	{
		std::cerr << "Can't open the image Clyde" << std::endl;
		return false;
	}
	else
	{
		myNPC->setTexture(texture);
		SDL_FreeSurface(image);
	}

	background = new GameObject(renderer, "Assets/Background.png");
	std::cout << " baground image can't open " << background << endl;
	//Button class
	//clyde = new Button("clyde.png", this);
	//if (!clyde->onCreate())
	//	return false;

	
	//weapon pickup
	surfacePtr = IMG_Load("Shotgun96.png");//surfacePtr
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);
	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}
	weaponPickup = new Object();

	SDL_FreeSurface(surfacePtr);


	weaponPickup->setPos(Vec3(3.0f, 13.0f, 0.0f));
	weaponPickup->setBoundingSphere(Sphere(0.25f));
	weaponPickup->setTexture(texturePtr);

	//Loads in the wall image and set the texture to the walls
	surfacePtr = IMG_Load("Assets/Ethan/wall.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	//Making the level
	level = new Level(NUMWALL);
	level->makeLevel(1); //pos of wall
	level->setWallTextures(texturePtr);

	GenerateLevel();

	
	// End of character set ups
	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime)
{
	
	
	
	// Updates the location of the orthograpic each frame
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	/**/
	float minX = game->getPlayer()->getPos().x - xAxis / 2;
	float maxX = game->getPlayer()->getPos().x + xAxis / 2;

	float minY = game->getPlayer()->getPos().y - yAxis / 2;
	float maxY = game->getPlayer()->getPos().y + yAxis / 2;
	/**/

	/**
	float minX = 0;
	float maxX = xAxis;
	float minY = 0;
	float maxY = yAxis;
	/**/

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);//1.0f

	projectionMatrix = ndc * ortho;

	inverseProjection = MMath::inverse(projectionMatrix);

	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);

	float radius = 1.0f;
	float timeToTarget = 0.5f;

	Body* player = game->getPlayer();
	KinematicArrive* steering_algorithm;
	steering_algorithm = new KinematicArrive(radius, timeToTarget, myNPC, player);
	KinematicSteeringOutput* steering;
	steering = steering_algorithm->getSteering();

	//Create physicobject from the kinematicbody for npc
	Sphere boundingSphere;
	boundingSphere.x = blinky->getBody()->getPos().x;// get pos.x of the sphere equal to npc //myNPC->getPos().x
	boundingSphere.y = blinky->getBody()->getPos().y;// get pos.y of the sphere equal to npc //myNPC->getPos().y
	boundingSphere.r = 0.4f;

	Sphere boundingSphere2;
	boundingSphere2.x = player->getPos().x;// get pos.x of the sphere equal to player
	boundingSphere2.y = player->getPos().y;// get pos.y of the sphere equal to player
	boundingSphere2.r = 0.4f;

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
	//myNPC->Update(deltaTime, steering);

	// Update player
	game->getPlayer()->Update(deltaTime);

	//myNPC latch on to player
	if (Physics::SphereSphereCollision(*AI, *P1) == true)
	{
		//blinky->Update(-deltaTime);
		//game->getPlayer()->Update(-deltaTime);
		//std::cout << "collide " << std::endl;
	}

	Physics::SimpleNewtonMotion(*P1, deltaTime);
	Physics::SimpleNewtonMotion(*AI, deltaTime);
	//Physics::SimpleNewtonMotion(*blinky, deltaTime);

	if (weaponPickup) {
		if (Physics::SphereSphereCollision(*weaponPickup, *P1) == true) {
			P1->setAltWeaponAvailable(true);
			P1->setWeaponType(1);
			game->getPlayer()->Update(-deltaTime);
			std::cout << "collide " << std::endl;
			delete weaponPickup;
			weaponPickup = nullptr;
		}
	}


	//Player Hits Walls
	for (int i = 0; i < level->getWallNum(); ++i) {
		//if (Physics::SphereSphereCollision(*level->getWall(i)), *P1) == true)
		if (Physics::CircleRectCollision(*P1, *level->getWall(i)) == true) {
			game->getPlayer()->Update(-deltaTime);
			//Physics::SimpleNewtonMotion(*P1, -deltaTime);
		}

	}
	//myNPC Hits Walls
	for (int i = 0; i < level->getWallNum(); ++i) {
		if (Physics::CircleRectCollision(*AI, *level->getWall(i)) == true) {
			blinky->Update(-2 * deltaTime);	
		
		}
	}
}

void Scene1::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (GameObject* tile_ : backgroundTiles) {
		tile_->Render(projectionMatrix, renderer, 1.0f, 0.0f);
		//cout << "Position: " << tile_->GetPosition().x << " || " << tile_->GetPosition().y << endl;
	}

	// Render any npc's
	blinky->render(0.15f);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	float scale = 0.5f;

	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);

	screenCoords = projectionMatrix * myNPC->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	float orientation = myNPC->getOrientation() * 180 / M_PI;

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
	//clyde->Render();
	
	// Render the player
	game->RenderPlayer(0.10f);

	// Render all things in the renderer
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// Send events to npc's as needed

	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);

	Vec3 mousePos = getMousePosition();

	if (event.button.type == SDL_MOUSEBUTTONUP
		&& event.button.button == SDL_BUTTON_LEFT)
	{
		//if (clyde->clicked(mousePos))
		//	printf("Mouse clicked inside clyde!");
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

void Scene1::GenerateLevel()
{
	// Amount of tiles on the width and height
	gridWidth = 20;
	gridHeight = 20;

	// Level layout (x value = gridWidth and y value = gridHeight)
	int levelData[20][20] = {
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 1, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 2, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 2, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 3, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 1, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 }
	};

	// Place the tiles for the amount of columns and rows
	for (int row = 0; row < gridHeight; row++)
	{
		for (int column = 0; column < gridWidth; column++)
		{
			int id = levelData[row][column];
			AddTile(column, row, id);
		}
	}

	for (Node* node : nodes)
	{
		GameObject* nodeTile = new GameObject(renderer, "Assets/Node.png");
		nodeTile->posX = node->GetPos().x;
		nodeTile->posY = node->GetPos().y;
		backgroundTiles.insert(backgroundTiles.end(), nodeTile);
	}
}

void Scene1::AddTile(int column, int row, int id)
{
	GameObject* tile = NULL;

	// Load the tile according to the id
	switch (id)
	{
	case 1:
		tile = new GameObject(renderer, "Assets/Tiles/Grass.png");
		std::cout << " grass image can't open " << endl;
		break;
	case 2:
		tile = new GameObject(renderer, "Assets/Tiles/Water.png");
		std::cout << " Water image can't open " << endl;
		break;
	case 3:
		tile = new GameObject(renderer, "Assets/Tiles/Brick.png");
		std::cout << " Brick image can't open" << endl;
		break;
	}

	if (tile != NULL)
	{
		// Position in pixels
		Vec3 startPos = Vec3(0.0f, 0.0f, 0.0f);

		// Set the position to have the origin top left
		tile->posX = startPos.x + column * tileWidth + (tileWidth * 0.5f);
		tile->posY = startPos.y + row * tileHeight + (tileHeight * 0.5f);

		// Print ID (with pathname), column and row
		cout << "ID: " << id << " " << "(" << tile->GetPathName() << ")"
			<< " || " << "Column: " << column << " || " << "Row : " << row << endl;

		// Transverse the position from viewport to game
		Vec3 position = Vec3(tile->posX, tile->posY, 0.0f);
		position = MMath::inverse(game->getProjectionMatrix()) * position;

		// Set the position to the game coordinates
		tile->posX = position.x;
		tile->posY = position.y;

		// Add the tile to the list
		backgroundTiles.insert(backgroundTiles.end(), tile);

		if (id == 1)
			AddNode(tile->GetPosition());
	}
}

void Scene1::AddNode(Vec3 pos)
{
	// Create new node
	Node* node = new Node();

	Vec3 position;
	position.x = pos.x + (tileWidth / 2);
	position.y = pos.y + (tileHeight / 2);

	// Set the position of the node
	node->SetPosition(pos);

	cout << "Node pos: " << node->GetPos().x << " " << node->GetPos().y << endl;

	nodes.insert(nodes.end(), node);
}