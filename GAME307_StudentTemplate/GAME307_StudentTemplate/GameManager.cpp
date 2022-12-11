#include "GameManager.h"

// KEEP INCLUDE BELOW IN CPP FILE
#include "Scene1.h"
#include "SceneMenu.h"
#include "SceneCredit.h"
#include "SceneSetting.h"
#include "SceneDeath.h"
#include "SceneWin.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	player = nullptr;

	changeSceneEventType = 0;
	playerHealth = 3.0f;

	//This will keep track of wich scene it is -1 will be the menu 
	//and -2 will be option -3 will be the credit and -4 will be the win screen
	//sceneNum = -1;
}

bool GameManager::OnCreate() {
	
	// My display is 1920 x 1080 but the following seems to work best to fill the screen.
	// Newest: 1800x900
	const int SCREEN_WIDTH = 1540;
	const int SCREEN_HEIGHT = 860;

	// Use 1000x600 for less than full screen
	//const int SCREEN_WIDTH = 1000;
	//const int SCREEN_HEIGHT = 600;

	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr)
	{
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false)
	{
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr)
	{
		OnDestroy();
		return false;
	}

	// Select scene for specific assignment
	currentScene = new SceneMenu(windowPtr->GetSDL_Window(), this);

	// Create player
	float mass = 1.0f;
	float radius = 0.5f;
	float orientation = 0.0f;
	float rotation = 0.0f;
	float angular = 0.0f;

	// These are not very good defaults, but they will prevent compiler warnings.
	float maxSpeed = 5.0f;
	float maxAcceleration = 10.0f;
	float maxRotation = 1.0f;
	float maxAngular = 1.0f;
	Vec3 position(0.5f * currentScene->getxAxis(), 0.5f * currentScene->getyAxis(), 0.0f);
	Vec3 velocity(0.0f, 0.0f, 0.0f);
	Vec3 acceleration(0.0f, 0.0f, 0.0f);

	player = new PlayerBody
	(
		position,
		velocity,
		acceleration,
		mass,
		radius,
		orientation,
		rotation,
		angular,
		maxSpeed,
		maxAcceleration,
		maxRotation,
		maxAngular,
		this
	);

	if (player->OnCreate() == false)
	{
		OnDestroy();
		return false;
	}

	// Need to create Player before validating scene
	if (!ValidateCurrentScene())
	{
		OnDestroy();
		return false;
	}

	// create some user defined event
	changeSceneEventType = SDL_RegisterEvents(1);
	if (changeSceneEventType == ((Uint32)-1))
	{
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game loop
void GameManager::Run()
{
	SDL_Event event;
	timer->Start();

	// Control if current scene's update() is called each tick
	bool launched = true;

	while (isRunning) {

		// Let's add mouse movement and position
		// https://wiki.libsdl.org/SDL_GetMouseState

		 // Make sure we have the latest mouse state
		SDL_PumpEvents();

		//https://www.youtube.com/watch?v=SYrRMr4BaD4&list=PLM7LHX-clszBIGsrh7_3B2Pi74AhMpKhj&index=3
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
			else if (event.type == changeSceneEventType && event.user.code == 1)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new Scene1(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			else if (event.type == changeSceneEventType && event.user.code == 2)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneSetting(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			else if (event.type == changeSceneEventType && event.user.code == 3)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneCredit(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			else if (event.type == changeSceneEventType && event.user.code == 4)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneMenu(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			
             else if (event.type == changeSceneEventType && event.user.code == 5)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new Scene1(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			
			 else if (event.type == changeSceneEventType && event.user.code == 6)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneWin(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}
			 else if (event.type == changeSceneEventType && event.user.code == 7)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneMenu(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					isRunning = false;
			}

			// Check to see what happens when you die. The code decides your fate, worship the code, THE CODE!!!!
			else if (currentScene->getDead() && sceneNum >= 0)
			{
				currentScene->OnDestroy();
				delete currentScene;

				// Switch scenes
				currentScene = new SceneDeath(windowPtr->GetSDL_Window(), this);

				if (!currentScene->OnCreate())
					currentScene->OnCreate();
			}

			else if (currentScene->nextScene() && sceneNum == 1) {//Loads the win screen
				currentScene->OnDestroy();
				delete currentScene;
				currentScene = new SceneWin(windowPtr->GetSDL_Window(),this);
				currentScene->OnCreate();
				//sceneNum = -3;
			}

			// Switch scenes manually with the key buttons
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;

				case SDL_SCANCODE_Q:
					isRunning = false;
					break;

				case SDL_SCANCODE_DELETE:
					isRunning = false;
					break;

				case SDL_SCANCODE_P:
					//toggle launched with L key)
					launched = !launched;
					break;

				case SDL_SCANCODE_1:
					launched = false;
					LoadScene(1);
					break;

				case SDL_SCANCODE_2:
					launched = false;
					LoadScene(2);
					break;

				case SDL_SCANCODE_3:
					launched = false;
					LoadScene(3);
					break;

				case SDL_SCANCODE_4:
					launched = false;
					LoadScene(4);
					break;

				default:
					break;

				}
			}

			currentScene->HandleEvents(event);
		}

		timer->UpdateFrameTicks();

		if (launched)
			currentScene->Update(timer->GetDeltaTime());

		currentScene->Render();

		// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60));		//60 frames per sececond
	}
}

GameManager::~GameManager() {}

float GameManager::getSceneHeight()
{
	return currentScene->getyAxis();
};

float GameManager::getSceneWidth()
{
	return currentScene->getxAxis();
};

Matrix4 GameManager::getProjectionMatrix()
{
	return currentScene->getProjectionMatrix();
};

void GameManager::OnDestroy()
{
	if (windowPtr)
		delete windowPtr;

	if (timer)
		delete timer;

	if (currentScene)
		delete currentScene;
}
SDL_Renderer* GameManager::getRenderer()
{
	// [TODO] Might be missing some SDL error checking
	SDL_Window* window = currentScene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	return renderer;
}

void GameManager::RenderPlayer(float scale)
{
	player->Render(scale);
}

void GameManager::LoadScene(int i)
{
	// Cleanup of current scene before loading anothe one
	if (currentScene)
	{
		currentScene->OnDestroy();
		delete currentScene;
	}

	// Switch scene according to key
	switch (i)
	{
	case 1:
		currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
		break;

	case 2:
		currentScene = new SceneMenu(windowPtr->GetSDL_Window(), this);
		break;

	case 3:
		currentScene = new SceneSetting(windowPtr->GetSDL_Window(), this);
		break;

	case 4:
		currentScene = new SceneCredit(windowPtr->GetSDL_Window(), this);
		break;
	default:
		currentScene = new SceneMenu(windowPtr->GetSDL_Window(), this);
		break;
	}

	// Using ValidateCurrentScene() to safely run OnCreate
	if (!ValidateCurrentScene())
		isRunning = false;
}


bool GameManager::ValidateCurrentScene()
{
	if (currentScene == nullptr)
		return false;

	if (currentScene->OnCreate() == false)
		return false;

	return true;
}
