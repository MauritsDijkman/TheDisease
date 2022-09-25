#include "SceneMenu.h"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

using namespace MATH;

SceneMenu::SceneMenu(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 32.0f;
	yAxis = 18.0f;
	play = false;
}

SceneMenu::~SceneMenu()
{
	OnDestroy();
}

bool SceneMenu::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	IMG_Init(IMG_INIT_PNG);

	surfacePtr = IMG_Load("Main_menu.png");
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

void SceneMenu::OnDestroy()
{
	SDL_DestroyRenderer(renderer);
}

void SceneMenu::Update(const float time)
{

}

void SceneMenu::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	//Clear screen
	SDL_RenderClear(renderer);
	//Update screen
	SDL_RenderPresent(renderer);
}

void SceneMenu::HandleEvents(const SDL_Event& sdlEvent)
{
	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
	Vec3 mousePosWorld = MMath::inverse(projectionMatrix) * mousePosView;
	//This is the play button it'll load scene zero
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 12 < mousePosWorld.x && mousePosWorld.x < 19 && 7 < mousePosWorld.y && mousePosWorld.y < 10) {
		play = true;

	}
	//This is the exit button which will exit and quit the game
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 12 < mousePosWorld.x && mousePosWorld.x < 19 && 2.5 < mousePosWorld.y && mousePosWorld.y < 5) {
		std::cout << mousePosWorld.x << "  ,  " << mousePosWorld.y << std::endl;
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
}


