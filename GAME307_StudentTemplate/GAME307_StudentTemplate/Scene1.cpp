#include "Scene1.h"
#include "VMath.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

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

	//RenderImage("Assets/Background.png", Vec3(10.0f, 7.5f, 0.0f), 0.0f, 1.0f);

	background = new GameObject(renderer, "Assets/Background.png");

	GenerateLevel();

	// end of character set ups

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

	float radius = 1.0f;
	float timeToTarget = 0.5f;

	Body* player = game->getPlayer();
	KinematicArrive* steering_algorithm;
	steering_algorithm = new KinematicArrive(radius, timeToTarget, myNPC, player);
	KinematicSteeringOutput* steering;
	steering = steering_algorithm->getSteering();

	//myNPC->Update(deltaTime, steering);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//RenderImage("Assets/Background.png", Vec3(10.0f, 7.5f, 0.0f), 0.0f, 1.0f);

	for (GameObject* tile_ : backgroundTiles) {
		tile_->Render(projectionMatrix, renderer, 1.0f, 0.0f);
		//cout << "Position: " << tile_->GetPosition().x << " || " << tile_->GetPosition().y << endl;
	}

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

	//background->Render(projectionMatrix, Vec3(10.0f, 10.0f, 0.0f), renderer, 1.0f, 0.0f);
	//background->Render(projectionMatrix, renderer, 1.0f, 0.0f);
	//background->posX = 10.0f;
	//background->posY = 10.0f;

	// Render the player
	game->RenderPlayer(0.10f);

	// Render all things in the renderer
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

void Scene1::GenerateLevel()
{
	gridWidth = 20;
	gridHeight = 20;

	int levelData[20][20] = {
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
	{ 1, 1, 1, 2, 2, 3, 2, 2, 3, 3, 2, 1, 3, 2, 3, 1, 2, 3, 1, 2 },
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
}

void Scene1::AddTile(int column, int row, int id)
{
	GameObject* tile = NULL;
	cout << "ID: " << id << endl;

	switch (id)
	{
	case 1:
		tile = new GameObject(renderer, "Assets/Tiles/Grass.png");
		cout << "Case 1" << endl;
		break;
	case 2:
		tile = new GameObject(renderer, "Assets/Tiles/Water.png");
		break;
	case 3:
		tile = new GameObject(renderer, "Assets/Tiles/Brick.png");
		break;
	}

	if (tile != NULL)
	{
		tile->posX = column * TileWidth + (TileWidth * 0.5f);
		tile->posY = row * TileHeight + (TileHeight * 0.5f);

		cout << "Column: " << column << " || Row: " << row << endl;

		// Transverse the position from viewport to game
		Vec3 position = Vec3(tile->posX, tile->posY, 0.0f);
		position = MMath::inverse(game->getProjectionMatrix()) * position;

		// Set the position to the game coordinates
		tile->posX = position.x;
		tile->posY = position.y;

		backgroundTiles.insert(backgroundTiles.end(), tile);
	}
}

/**
void Scene1::RenderImage(string pathName_, Vec3 spawnPos_, float orientationDegrees_, float scale_)
{
	// Display some image in the scene that doesn't move
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load(pathName_.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr)
		std::cerr << "Can't open the image" << std::endl;

	Vec3 pos = Vec3(spawnPos_.x, spawnPos_.y, 0.0f);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * pos;
	//w = static_cast<int>(image->w * scale_);
	//h = static_cast<int>(image->h * scale_);

	w = static_cast<int>(w * scale_);
	h = static_cast<int>(h * scale_);

	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	//square.x = static_cast<int>(screenCoords.x);
	//square.y = static_cast<int>(screenCoords.y - h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees (degrees * 180.0f / M_PI).
	float orientationDegrees = orientationDegrees_ * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, texture, nullptr, &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);

	cout << "Image" << endl;
}
/**/
