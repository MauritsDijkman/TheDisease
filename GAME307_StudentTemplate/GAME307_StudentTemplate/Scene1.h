#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include "Character.h"
#include "StaticBody.h"
#include "KinematicSeek.h"
#include "KinematicArrive.h"
#include "GameObject.h"
#include "PlayerBody.h"
//
#include "Body.h";


using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	//
	Vec3 vel;
	//
	SDL_Renderer* renderer;

	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	Character* blinky;
	StaticBody* myNPC;

	GameObject* weaponPickup;

public:
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
    bool nextScene() { return false; }
};

#endif
