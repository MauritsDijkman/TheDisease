#include "SceneWin.h"
#include <SDL.h>
#include "SDL_image.h"
#include "Randomizer.h"
#include "Physics.h"
#include <iostream>

SceneWin::SceneWin(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	renderer = SDL_GetRenderer(window);
	game = game_;
	pressed = false;
	
}

SceneWin::~SceneWin()
{
	// Rember to delete every pointer NO MEMORY LEAKS!!!!!!
	OnDestroy();
}

bool SceneWin::OnCreate()
{
	int w, h;
	float xAxis = 32.0f;
	float yAxis = 18.0f;
	float zAxis = 1.0f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, zAxis);
	projectionMatrix = ndc * ortho;

	// Make loading PNGs easer so only use PNGs
	IMG_Init(IMG_INIT_PNG);

	// Load the Back ground image and set the texture as well
	surfacePtr = IMG_Load("win.jpg");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr)
	{
		std::cerr << "Imgage does not work" << std::endl;
		return false;
	}
	if (texturePtr == nullptr)
	{
		printf("%s\n", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surfacePtr);

	return true;
}

void SceneWin::OnDestroy()
{
	SDL_DestroyTexture(texturePtr);
}

void SceneWin::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	// Clear screen
	SDL_RenderClear(renderer);

	SDL_Rect youWin;
	youWin.x = 310;
	youWin.y = 0;
	youWin.w = 720;
	youWin.h = 720;
	SDL_RenderCopy(renderer, texturePtr, nullptr, &youWin);

	// Update screen
	SDL_RenderPresent(renderer);
}

void SceneWin::Update(const float time) {}

void SceneWin::HandleEvents(const SDL_Event& sdlEvent)
{
		if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
		{
		
			// Create event
			SDL_Event event;
			SDL_memset(&event, 0, sizeof(event));

			// Set event information
			event.type = game->getChangeScene();
			event.user.code = 7;
			event.user.data1 = nullptr;
			event.user.data2 = nullptr;

			// Push the event
			SDL_PushEvent(&event);
			// Move you to the menu when you press any key 
			
		}
}
