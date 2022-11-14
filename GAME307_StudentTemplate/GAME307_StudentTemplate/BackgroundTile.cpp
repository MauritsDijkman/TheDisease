#include "BackgroundTile.h"
#include <GameObject.h>

void BackgroundTile::Render(SDL_Renderer* renderer, Matrix4 projectionMatrix)
{
	tileImage->Render(projectionMatrix, renderer, 1.0f, 0.0f);

	if (hasNode)
		nodeImage->Render(projectionMatrix, renderer, 1.0f, 1.0f);
}

void BackgroundTile::AddTile(SDL_Renderer* renderer, int column, int row, int id, int label, float tileWidth, float tileHeight, Matrix4 projectionMatrix)
{
	bool placeNode = false;

	cout << "Tile with label: " << label << " has been created!" << endl;

	// Load the tile according to the id
	switch (id)
	{
	case 1:
		tileImage = new GameObject(renderer, "Assets/Tiles/Tile_Grass.png");
		placeNode = true;
		break;
	case 2:
		tileImage = new GameObject(renderer, "Assets/Tiles/Tile_Water.png");
		break;
	case 3:
		tileImage = new GameObject(renderer, "Assets/Tiles/Tile_Stone.png");
		placeNode = true;
		break;
	}

	if (tileImage)
	{
		// Position in pixels
		Vec3 startPos = Vec3(0.0f, 0.0f, 0.0f);

		// Set the position to have the origin top left
		tileImage->posX = startPos.x + column * tileWidth + (tileWidth * 0.5f);
		tileImage->posY = startPos.y + row * tileHeight + (tileHeight * 0.5f);

		// Print ID (with pathname), column and row
		cout << "ID: " << id << " " << "(" << tileImage->GetPathName() << ")"
			<< " || " << "Column: " << column << " || " << "Row : " << row
			<< " Label: " << label << endl;

		// Transverse the position from viewport to game
		Vec3 position = Vec3(tileImage->posX, tileImage->posY, 0.0f);
		position = MMath::inverse(projectionMatrix) * position;

		// Set the position to the game coordinates
		tileImage->posX = position.x;
		tileImage->posY = position.y;

		if (placeNode)
			AddNode(renderer, column, row, label, tileWidth, tileHeight, projectionMatrix);
	}
}

void BackgroundTile::AddNode(SDL_Renderer* renderer, int column, int row, int label, float tileWidth, float tileHeight, Matrix4 projectionMatrix)
{
	Node* n = new Node(label);

	// Position in pixels
	Vec3 startPos = Vec3(0.0f, 0.0f, 0.0f);

	// Set the position to have the origin top left
	n->SetPosX(startPos.x + column * tileWidth + (tileWidth * 0.5f));
	n->SetPosY(startPos.y + row * tileHeight + (tileHeight * 0.5f));

	// Transverse the position from viewport to game
	Vec3 position = Vec3(n->GetPos().x, n->GetPos().y, 0.0f);
	position = MMath::inverse(projectionMatrix) * position;

	// Set the position to the game coordinates
	n->SetPosX(position.x);
	n->SetPosY(position.y);

	node = n;

	//cout << "NodePos from node " << label << ":";
	//node->GetPos().print();

	nodeImage = new GameObject(renderer, "Assets/Node.png");
	nodeImage->posX = node->GetPos().x;
	nodeImage->posY = node->GetPos().y;
}
