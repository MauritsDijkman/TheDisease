#include "SceneDeath.h"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

#include "Randomizer.h"
#include "Physics.h"

SceneDeath::SceneDeath(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	renderer = SDL_GetRenderer(window);
	game = game_;
	pressed = false;
}

SceneDeath::~SceneDeath()
{
	// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	OnDestroy();
}

bool SceneDeath::OnCreate()
{
	int w, h;
	float xAxis = 32.0f;
	float yAxis = 18.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, zAxis);
	projectionMatrix = ndc * ortho;

	//Makes loading PNGs easer so only use PNGs
	IMG_Init(IMG_INIT_PNG);

	surfacePtr = IMG_Load("death.jpg");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	return true;
}

void SceneDeath::OnDestroy()
{
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texturePtr);
}

void SceneDeath::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	// Clear screen
	SDL_RenderClear(renderer);

	SDL_Rect youDied;
	youDied.x = 310;
	youDied.y = 0;
	youDied.w = 720;
	youDied.h = 720;
	SDL_RenderCopy(renderer, texturePtr, nullptr, &youDied);

	// Update screen
	SDL_RenderPresent(renderer);
}

void SceneDeath::Update(const float time) {}

void SceneDeath::HandleEvents(const SDL_Event& sdlEvent)
{
	//Make stuff happen here with the clickety clack
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
	{
		//Move you to the menu when you press any key 
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 5;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		// Push the event
		SDL_PushEvent(&event);
		pressed = true;
	}
}
