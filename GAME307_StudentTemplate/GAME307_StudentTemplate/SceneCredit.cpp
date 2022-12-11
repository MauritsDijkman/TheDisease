#include "SceneCredit.h"

SceneCredit::SceneCredit(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	xAxis = 25.0f;
	yAxis = 15.0f;
	renderer = SDL_GetRenderer(window);
}

SceneCredit::~SceneCredit(){
	OnDestroy();
}

bool SceneCredit::OnCreate(){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);//xAxis = 25 , yAxis = 15
	projectionMatrix = ndc * ortho;
	IMG_Init(IMG_INIT_PNG);
	surfacePtr = IMG_Load("Assets/Menu/Menu_Credits.png");
	texturePtr = SDL_CreateTextureFromSurface(renderer, surfacePtr);
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

void SceneCredit::OnDestroy()
{
	SDL_DestroyTexture(texturePtr);
}
void SceneCredit::Update(const float time){}

void SceneCredit::HandleEvents(const SDL_Event& sdlEvent)
{
	// Get the position of the mouse
	Vec3 mousePosView = Vec3(sdlEvent.button.x, sdlEvent.button.y, 0.0f);
	
	// Back button, loads the previous scene
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
		85 < mousePosView.x && mousePosView.x < 384
		&& 684 < mousePosView.y && mousePosView.y < 778)
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

bool SceneCredit::getDead(){return pressed;}

void SceneCredit::Render()
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