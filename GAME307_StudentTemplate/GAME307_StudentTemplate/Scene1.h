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
class Scene1 : public Scene{
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
	
#pragma region SDL_Texture
	SDL_Texture* health;
	SDL_Texture* itemhealth;
	SDL_Texture* pistolbullet;
	SDL_Texture* shotgunbullet;
	SDL_Texture* melee;
	SDL_Texture* ammo;
	SDL_Texture* shotgunammo;
	SDL_Texture* knifes;
	SDL_Texture* key;
#pragma endregion

#pragma region Weapons
	// Lists for weapons
	vector<Ammunition*> pistol;
	vector<Ammunition*> shotgun;
	vector<Ammunition*> knife;
#pragma endregion

	// Background
	GameObject* background;

#pragma region Enemies
	// Enemies
	vector<EnemyCharacter*> enemies;
	vector<EnemyCharacter*> enemies1;
	vector<EnemyCharacter*> enemies2;
	vector<EnemyCharacter*> enemies3;
	vector<EnemyCharacter*> enemies4;
	vector<EnemyCharacter*> enemies5;
	vector<EnemyCharacter*> enemies6;
	vector<EnemyCharacter*> enemies7;
	vector<EnemyCharacter*> enemies8;
	vector<EnemyCharacter*> enemies9;
	vector<EnemyCharacter*> enemies10;
	vector<EnemyCharacter*> enemies11;
	vector<EnemyCharacter*> enemies12;
	vector<EnemyCharacter*> enemies13;
	vector<EnemyCharacter*> enemies14;
	vector<EnemyCharacter*> enemies15;
	vector<EnemyCharacter*> enemies16;
	vector<EnemyCharacter*> enemies17;
	vector<EnemyCharacter*> enemies18;
	vector<EnemyCharacter*> enemies19;
#pragma endregion

	// Npc
	Character* blinky;
	Enemy* enemy;

#pragma region Pickup
	// Pickups
	Object* weaponPickup;
	Object* healthPickup;
	Object* healthPickup2;
	Object* healthPickup3;
	Object* healthPickup4;
	Object* itemhealthpickup;
	Object* itemhealthpickup2;
	Object* itemhealthpickup3;
	Object* itemhealthpickup4;
	Object* ammoPickup;
	Object* ammo1Pickup;
	Object* ammo2Pickup;
	Object* ammo3Pickup;
	Object* ammo4Pickup;
	Object* shotgunammoPickup;
	Object* shotgunammoPickup1;
	Object* shotgunammoPickup2;
	Object* shotgunammoPickup3;
	Object* shotgunammoPickup4;
	Object* keyPickup;
	Object* keyPickup1;
	Object* keyPickup2;
	Object* keyPickup3;
	Object* keyPickup4;
#pragma endregion

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
	bool nextScene();
	bool pressed;
};
#endif