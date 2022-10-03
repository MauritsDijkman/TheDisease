#include "SceneMenu.h"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
//#include "GameManager.h"
//#include "Scene1.h"
//#include "SceneCredit.h"

using namespace MATH;

SceneMenu::SceneMenu(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	xAxis = 25.0f;
	yAxis = 15.0f;
	renderer = SDL_GetRenderer(window);
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
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);//xAxis = 25 , yAxis = 15
	projectionMatrix = ndc * ortho;

	IMG_Init(IMG_INIT_PNG);

	surfacePtr = IMG_Load("Main_menu.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);

	if (surfacePtr == nullptr) {
		std::cerr << "Image does not work" << std::endl;
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
	//SDL_DestroyRenderer(renderer);
}

void SceneMenu::Update(const float time)
{

}

void SceneMenu::HandleEvents(const SDL_Event& sdlEvent)
{

	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
	Vec3 mousePosWorld = MMath::inverse(projectionMatrix) * mousePosView;
	//This is the play button it'll load scene zero
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 3.3 < mousePosWorld.x && mousePosWorld.x < 7.3 && 11.5 < mousePosWorld.y && mousePosWorld.y < 13.1) {// 12 < mousePosWorld.x && mousePosWorld.x < 19 && 7 < mousePosWorld.y && mousePosWorld.y < 10
		play = true;
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = game->getChangeScene();
		event.user.code = 1;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);

		std::cout << mousePosWorld.x << "  Play Scene1  " << mousePosWorld.y << std::endl;
		
	}
	
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 3.3 < mousePosWorld.x && mousePosWorld.x < 11.3 && 8.9 < mousePosWorld.y && mousePosWorld.y < 10.5) {// 12 < mousePosWorld.x && mousePosWorld.x < 19 && 7 < mousePosWorld.y && mousePosWorld.y < 10
		play = true;
		std::cout << mousePosWorld.x << "  Play SceneSetting  " << mousePosWorld.y << std::endl;
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = game->getChangeScene();
		event.user.code = 2;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 3.2 < mousePosWorld.x && mousePosWorld.x < 9.3 && 6.9 < mousePosWorld.y && mousePosWorld.y < 8.5) {// 12 < mousePosWorld.x && mousePosWorld.x < 19 && 7 < mousePosWorld.y && mousePosWorld.y < 10
		play = true;
		std::cout << mousePosWorld.x << " Play SceneCredit  " << mousePosWorld.y << std::endl;
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = game->getChangeScene();
		event.user.code = 3;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
	

	//This is the exit button which will exit and quit the game
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && 3.1 < mousePosWorld.x && mousePosWorld.x < 6.9 && 5< mousePosWorld.y && mousePosWorld.y < 6.7) {//12 < mousePosWorld.x && mousePosWorld.x < 19 && 2.5 < mousePosWorld.y && mousePosWorld.y < 5)
		std::cout << mousePosWorld.x << "  Exit  " << mousePosWorld.y << std::endl;
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
}

void SceneMenu::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_Rect square;
	Vec3 screenCoords;
	float scale = 1.9f;//1.9f
	Vec3 Pos = Vec3(12.5f, 7.5f, 1.0f);//12.5f, 7.5f, 1.0f

	int    w, h;

	// Show our Menu screen
	SDL_QueryTexture(texturePtr, nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * Pos;
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	//Clear screen
	SDL_RenderClear(renderer);

	SDL_RenderCopyEx(renderer, texturePtr, nullptr, &square,
		0.0f, nullptr, SDL_FLIP_NONE);

	//Update screen
	SDL_RenderPresent(renderer);
}





