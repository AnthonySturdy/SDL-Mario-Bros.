#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<iostream>
#include<string>

#include"Constants.h"
#include"Texture2D.h"
#include"GameScreenManager.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;

Uint32 gOldTime;

Mix_Music* gMusic = NULL;

bool InitSDL();
void CloseSDL();

bool Update();

void LoadMusic(std::string path);

int main(int argc, char* args[]) {
	if (InitSDL()) {
		bool quit = false;

		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MAIN_MENU);

		gOldTime = SDL_GetTicks();

		LoadMusic("Music/ThemeSong.wav");
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(gMusic, -1);
		}

		while (!quit) {
			quit = Update();
			//Clear the screen to black
			SDL_SetRenderDrawColor(gRenderer, 0x33, 0x33, 0x33, 0xFF);
			SDL_RenderClear(gRenderer);

			gameScreenManager->Render();

			//Update the screen
			SDL_RenderPresent(gRenderer);
		}
	}

	CloseSDL();

	return 0;
}

bool InitSDL() {
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL did not initialise. Error: " << SDL_GetError() << std::endl;
		return false;
	} else {
		//Attempt Window Creation
		gWindow = SDL_CreateWindow("SDL Mario Bros. // Anthony Sturdy // Staffordshire University // Game Engine Creation Semester 2",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH * SCREEN_SCALE,
									SCREEN_HEIGHT * SCREEN_SCALE,
									SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			std::cout << "Window was not created. Error: " << SDL_GetError() << std::endl;
			return false;
		}

		//Attempt Renderer Creation
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL) {
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) {
				std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError() << std::endl;
				return false;
			}

			//Scale screen up for pixel effect
			//Divide WIDTH and HEIGHT in window create / 2. Uncomment line of code below.
			//To avoid mouse position weirdness, divide every mouse pos by SCREEN_SCALE
			SDL_RenderSetScale(gRenderer, SCREEN_SCALE, SCREEN_SCALE);

		} else {
			std::cout << "Renderer could not intitialise. Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Mixer could not initialise. Error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void CloseSDL() {
	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Destroy game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Clean up music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool Update() {
	SDL_Event e;
	SDL_PollEvent(&e);
	Uint32 newTime = SDL_GetTicks();
	
	switch (e.type) {
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_q:
			return true;
			break;
		}
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;

	return false;
}

void LoadMusic(std::string path) {
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL) {
		std::cout << "Failed to load background music. Error: " << Mix_GetError() << std::endl;
	}

	
}