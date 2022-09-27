#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "MMath.h"

using namespace MATH;
using namespace std;

class GameObject {
private:
	SDL_Surface* surface;
	SDL_Texture* texture;

	void AddTile(int column, int row, int id);

	int gridWidth = 10;
	int gridHeight = 10;

	Vec3 spawnPosition = Vec3(0.0f, 0.0f, 0.0f);

public:
	GameObject(SDL_Renderer* render_, string pathName_);

	void Render(Matrix4 projectionMatrix_, SDL_Renderer* renderer_,
		float scale_, float orientationDegrees_);

	//void Render(Matrix4 projectionMatrix_, Vec3 spawnPos_, SDL_Renderer* renderer_,
	//	float scale_, float orientationDegrees_);

	// Get functions
	SDL_Surface* GetSurface();
	SDL_Texture* GetTexture();
	Vec3 GetPosition();

	// Spawnposition
	float posX;
	float posY;
};

#endif
