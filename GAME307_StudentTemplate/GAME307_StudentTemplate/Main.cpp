#include <iostream>
#include "GameManager.h"
//#include <SDL_mixer.h>
#include <SDL_audio.h>


int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it

	//int init = Mix_Init(0);

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	//Mix_Music * music = Mix_LoadMUS("Audio/Shooting-Stars.wav");
	//if(!music){
	//	cout << "Music Error: " << Mix_GetError() << endl;
	//}


	//Mix_PlayMusic(music, -1);

	GameManager* ptr = new GameManager();
	bool status = ptr->OnCreate();

	if (status == true)
		ptr->Run();
	else if (status == false)
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;

	delete ptr;
	return 0;
}
