#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include "Character.h"
#include "StaticBody.h"
#include "KinematicSeek.h"
#include "KinematicArrive.h"
#include "GameObject.h"
#include "Node.h"
#include "Object.h"
#include "Level.h"


using namespace MATH;

//Numbers of walss
#define NUMWALL 58
//struct MATH::Plane;


class Scene1 : public Scene {
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4     inverseProjection;

	//
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	
	
	//

	Character* blinky;
	StaticBody* myNPC;

	GameObject* background;

	Object* weaponPickup;

	Level* level;
	Plane* wallLeft;
	Plane* wallRight;
	Plane* wallTop;
	Plane* wallBottom;


	const int tileWidth = 77;
	const int tileHeight = 43;
	int gridWidth = 18;
	int gridHeight = 8;

	void GenerateLevel();
	void AddTile(int column, int row, int id);
	void AddNode(Vec3 pos);

	vector<GameObject*> backgroundTiles;
	vector<Node*> nodes;



	//Button* clyde;

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

	Vec3 getMousePosition();
	bool nextScene() { return false; }
};

#endif