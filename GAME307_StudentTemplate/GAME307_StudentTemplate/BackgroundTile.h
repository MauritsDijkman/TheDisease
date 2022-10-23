#ifndef BACKGROUND_TILE_H
#define BACKGROUND_TILE_H

#include <Node.h>
#include <SDL.h>
#include <SDL_image.h>
#include <GameObject.h>

using namespace MATH;
using namespace std;

class BackgroundTile
{
private:
	GameObject* tileImage = nullptr;
	GameObject* nodeImage = nullptr;

	Node* node;
	bool hasNode = false;

	void AddNode(SDL_Renderer* renderer, int column, int row, int label, float tileWidth, float tileHeight, Matrix4 projectionMatrix);

public:
	BackgroundTile(Node* node_, bool hasNode_)
	{
		node = node_;
		hasNode = hasNode_;
	}

	void Render(SDL_Renderer* renderer, Matrix4 projectionMatrix);
	void AddTile(SDL_Renderer* renderer, int column, int row, int id, int label, float tileWidth, float tileHeight, Matrix4 projectionMatrix);

	Node* GetNode() { return node; }
	bool HasNode() { return hasNode; }
};

#endif // !BACKGROUND_TILE_H
