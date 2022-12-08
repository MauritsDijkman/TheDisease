#ifndef SCENESETTING_H
#define SCENESETTING_H
#include "Scene.h"
#include "Plane.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

using namespace std;
using namespace MATH;
struct MATH::Plane;

class SceneSetting : public Scene {
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;
	bool pressed;
public:
	SceneSetting(SDL_Window* sdlWindow_, GameManager* game_);
	~SceneSetting();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool nextScene() { return false; }
	bool getDead();
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};
#endif