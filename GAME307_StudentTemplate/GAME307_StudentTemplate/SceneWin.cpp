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

	xAxis = 25.0f;
	yAxis = 15.0f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);

	projectionMatrix = ndc * ortho;

	//Makes loading PNGs easer so only use PNGs
	IMG_Init(IMG_INIT_PNG);

	surfacePtr = IMG_Load("Assets/Menu/Menu_Victory.png");
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

void SceneWin::OnDestroy()
{
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texturePtr);
}

void SceneWin::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Rect square;
	Vec3 screenCoords;

	float scale = 1.0f;
	Vec3 pos = Vec3(12.5f, 7.5f, 1.0f);	// To spawn in the middle
	int w, h;

	// Set up the info of the image
	SDL_QueryTexture(texturePtr, nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * pos;
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Clear screen
	SDL_RenderClear(renderer);

	// Copy for rotation and flipping
	SDL_RenderCopyEx(renderer, texturePtr, nullptr, &square,
		0.0f, nullptr, SDL_FLIP_NONE);

	// Render the screen
	SDL_RenderPresent(renderer);
}

void SceneWin::Update(const float time) {}

void SceneWin::HandleEvents(const SDL_Event& sdlEvent)
{
	// Get the position of the mouse
	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);

	// Restart button, restarts the level
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 325 < mousePosView.y && mousePosView.y < 419)
	{
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
	}
	// Menu button, loads the menu
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 462 < mousePosView.y && mousePosView.y < 556)
	{
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));

		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 4;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;

		// Push the event
		SDL_PushEvent(&event);
	}
}
