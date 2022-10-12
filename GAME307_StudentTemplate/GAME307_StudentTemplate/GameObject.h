#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "MMath.h"
#include "PhysicsObject.h"

using namespace MATH;
using namespace std;

class GameObject : public PhysicsObject {
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	string pathName;

public:
	GameObject(SDL_Renderer* render_, string pathName_);

	void Render(Matrix4 projectionMatrix_, SDL_Renderer* renderer_,
		float scale_, float orientationDegrees_);

	// Get functions
	SDL_Surface* GetSurface();
	SDL_Texture* GetTexture();
	Vec3 GetPosition();
	string GetPathName();

	// Spawnposition
	float posX;
	float posY;
};

#endif
