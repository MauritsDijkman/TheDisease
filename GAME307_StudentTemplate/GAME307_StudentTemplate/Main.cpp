#include <iostream>
#include "GameManager.h"
#include <SDL_mixer.h>
#include <SDL_audio.h>


int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	
	//SDL_Init(SDL_INIT_AUDIO);

	//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		//std::cout << "Error: " << Mix_GetError() << std::endl;

	//Mix_Music* bgm = Mix_LoadMUS("Zombie Game Main Menu Theme");
	//Mix_Chunk *SoundEffect = Mix_LoadWAV("");

	//Mix_FreeMusic(bgm);

	//bgm = nullptr;

	GameManager* ptr = new GameManager();
	bool status = ptr->OnCreate();

	if (status == true)
		ptr->Run();
	else if (status == false)
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;

	delete ptr;
	//Mix_Quit();
	return 0;
}
