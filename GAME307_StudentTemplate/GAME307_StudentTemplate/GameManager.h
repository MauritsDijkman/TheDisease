#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "PlayerBody.h"

class GameManager {
private:
	class Window* windowPtr;
	class Timer* timer;
	bool isRunning;
	int sceneNum;
	float playerHealth;
	// Class
	class Scene* currentScene;
	class PlayerBody* player;
	Uint32 changeSceneEventType;	// Event type number for user defined events
public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();
	float getSceneHeight();
	float getSceneWidth();
	Matrix4 getProjectionMatrix();
	PlayerBody* getPlayer() { return player; }
	Uint32 getChangeScene() { return changeSceneEventType; }
	SDL_Renderer* getRenderer();
	void RenderPlayer(float scale = 1.0f);
	void Run();
	void LoadScene(int i);
	bool ValidateCurrentScene();
};
#endif