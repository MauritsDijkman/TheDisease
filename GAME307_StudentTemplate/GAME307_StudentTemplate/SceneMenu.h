#ifndef SCENEMENU_H
#define SCENEMENU_H
#include "Scene.h"
#include "Plane.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

using namespace std;
using namespace MATH;

struct MATH::Plane;
class SceneMenu : public Scene {
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;
	bool play;
	class Window* windowPtr;
	SDL_Texture* PlayerScore;
public:
	SceneMenu(SDL_Window* sdlWindow_, GameManager* game_);
	~SceneMenu();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool nextScene() { return false; }
	bool getDead();
	//Game manager need this to get acces to SceneMenu
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};
#endif