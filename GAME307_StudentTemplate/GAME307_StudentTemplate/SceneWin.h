#ifndef SCENEWWIN_H
#define SCENEWIN_H
#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "PlayerBody.h"
#include "EnemyCharacter.h"
#include "Ammunition.h"
#include "Plane.h"
#include "Level.h"

using namespace MATH;
struct MATH::Plane;

class SceneWin : public Scene{

private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* background;
	Matrix4 inverseProjection;
	int wait;
	bool pressed;
	float xAxis = 25.0f;
	float yAxis = 15.0f;

public:
	SceneWin(SDL_Window* sdlWindow, GameManager* game_);
	~SceneWin();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead() { return pressed; };
	bool nextScene() { return false; }
	float getHealth() { return 0.0f; }
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};
#endif