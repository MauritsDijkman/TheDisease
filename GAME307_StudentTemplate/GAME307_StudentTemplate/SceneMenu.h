#ifndef SCENEMENU_H
#define SCENEMENU_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
//#include "GameObject.h"
//#include "PlayerBody.h"
//#include "Character.h"
//#include "Plane.h"


using namespace MATH;
//struct MATH::Plane;

class SceneMenu : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	Matrix4 inverseProjection;
	//GameObject* player; //Not the player just a a guy jumping around the screen 

	bool play;
	float xAxis = 25.0f;
	float yAxis = 15.0f;


public:
	SceneMenu(SDL_Window* sdlWindow, GameManager* game_);
	~SceneMenu();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool nextScene() { return false; }\
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif