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

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Assets/humans/idle_human2.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

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

	// Generate the layout of the scene
	GenerateSceneLayout();

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

	// Calculate the matrixes
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(minX, maxX, minY, maxY, 0.0f, 1.0f);

	// Calculate the projections
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	// Update the npc's
	blinky->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Render all the background tiles
	for (GameObject* tile_ : backgroundTiles)
		tile_->Render(projectionMatrix, renderer, 1.0f, 0.0f);

	// Render any npc's
	blinky->render(0.15f);

	// Render the player
	game->RenderPlayer(0.10f);

	// Render all things in the renderer
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);
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

	// Place the tiles for the amount of columns and rows
	for (int row = 0; row < gridHeight; row++)
	{
		for (int column = 0; column < gridWidth; column++)
		{
			int id = levelData[row][column];
			AddTile(column, row, id);
		}
	}

	// For every node in the node list, place the visual
	for (Node* node : nodes)
	{
		GameObject* nodeTile = new GameObject(renderer, "Assets/Node.png");
		nodeTile->posX = node->GetPos().x;
		nodeTile->posY = node->GetPos().y;

		// Add the node visuals to the background tiles
		backgroundTiles.push_back(nodeTile);
	}

	// TODO
	// Set all the nodes from this list to the one used in the A* class
}

void Scene1::AddTile(int column, int row, int id)
{
	// Create tile for later use
	GameObject* tile = NULL;

	// Load the tile according to the id
	switch (id)
	{
	case 1:
		tile = new GameObject(renderer, "Assets/Tiles/Tile_Grass.png");
		break;
	case 2:
		tile = new GameObject(renderer, "Assets/Tiles/Tile_Water.png");
		break;
	case 3:
		tile = new GameObject(renderer, "Assets/Tiles/Tile_Stone.png");
		break;
	}

	if (tile)	// (if(tile != NULL))
	{
		// Position in pixels
		//Vec3 startPos = Vec3(-100.0f, -100.0f, 0.0f);
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

	// Set the position of the node
	node->SetPosition(pos);

	// Debug for position of the node in the game view
	cout << "Node pos: " << node->GetPos().x << " || " << node->GetPos().y << endl;

	// Add the node to the list with nodes
	nodes.push_back(node);
}
