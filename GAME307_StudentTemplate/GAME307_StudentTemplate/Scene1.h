#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include "Character.h"
#include "StaticBody.h"
#include "KinematicSeek.h"
#include "KinematicArrive.h"
#include "Object.h"
#include "GameObject.h"
#include "Node.h"
#include "Enemy.h"
#include "Level.h"
#include "PlayerBody.h"
#include "EnemyCharacter.h"
#include <BackgroundTile.h>
#include <Graph.h>

using namespace MATH;

#define NUMWALL 9999

class Scene1 : public Scene
{
private:
	SDL_Window* window;

	float xAxis = 25.0f;
	float yAxis = 15.0f;

	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	// Surfaces and textures
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	SDL_Texture* health;
	SDL_Texture* itemhealth;
	SDL_Texture* pistolbullet;
	SDL_Texture* shotgunbullet;
	SDL_Texture* melee;
	SDL_Texture* ammo;
	SDL_Texture* knifes;

	// Lists for weapons
	vector<Ammunition*> pistol;
	vector<Ammunition*> shotgun;
	vector<Ammunition*> knife;

	// Background
	GameObject* background;

	// Enemies
	vector<EnemyCharacter*> enemies;
	vector<EnemyCharacter*> enemies1;
	vector<EnemyCharacter*> enemies2;
	vector<EnemyCharacter*> enemies3;

	// Npc
	Character* blinky;
	Enemy* enemy;

	// Pickups
	Object* weaponPickup;
	Object* healthPickup;
	Object* itemhealthpickup;
	Object* ammoPickup;

	// Level
	Level* level;
	Plane* wallLeft;
	Plane* wallRight;
	Plane* wallTop;
	Plane* wallBottom;

	// Variables for background tile placement
	const int tileWidth = 60;
	const int tileHeight = 60;
	int gridWidth = 30;
	int gridHeight = 15;

	// Scene generation
	void GenerateSceneLayout();
	void CalculateConnectionWeights();
	//void AddTile(int column, int row, int id, int label);
	//void AddNode(int column, int row, int label);

	// Lists for scene creation
	vector<vector<BackgroundTile*>> tiles;
	vector<Node*> nodes;

	Graph* graph;
	void CreateTiles(int rows_, int columns_);

	bool LoadImage(string pathName_);

public:
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();

	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);

	bool getDead();

	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }

	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }

	Vec3 getMousePosition();
};

#endif
