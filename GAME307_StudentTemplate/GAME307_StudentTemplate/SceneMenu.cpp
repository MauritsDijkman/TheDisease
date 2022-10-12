#include "SceneMenu.h"

SceneMenu::SceneMenu(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;

	xAxis = 25.0f;
	yAxis = 15.0f;

	renderer = SDL_GetRenderer(window);
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

	surfacePtr = IMG_Load("Assets/Menu/Menu_Main.png");
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
	// Get the position of the mouse
	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);

	// Play button, will load the game level
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 306 < mousePosView.y && mousePosView.y < 400)
	{
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));

		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 1;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;

		// Push the event
		SDL_PushEvent(&event);
	}

	// Settings buttons, will load the settings scene
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 430 < mousePosView.y && mousePosView.y < 524)
	{
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));

		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 2;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;

		// Push the event
		SDL_PushEvent(&event);
	}

	// Credits button, will load the credits scene
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 558 < mousePosView.y && mousePosView.y < 652)
	{
		// Create event
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));

		// Set event information
		event.type = game->getChangeScene();
		event.user.code = 3;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;

		// Push the event
		SDL_PushEvent(&event);
	}

	// Quit button, closes the game
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		84 < mousePosView.x && mousePosView.x < 383
		&& 684 < mousePosView.y && mousePosView.y < 778)
	{
		// Create event
		SDL_Event sdlevent;

		// Set event information
		sdlevent.type = SDL_QUIT;

		// Push the event
		SDL_PushEvent(&sdlevent);
	}
}

void SceneMenu::Render()
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
