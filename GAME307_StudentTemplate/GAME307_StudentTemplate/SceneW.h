#ifndef SCENEW_H
#define SCENEW_H

#include <SDL.h>
#include <vector>
#include "Scene.h"
#include "GameManager.h"


using namespace MATH;
//struct MATH::Plane;

class SceneWin : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	int wait;
	bool pressed;


public:
	SceneWin(SDL_Window* sdlWindow);
	~SceneWin();
	bool OnCreate(float);
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool getDead();
	bool nextScene() { return false; }
	float getHealth() { return 0.0f; }
};

#endif
