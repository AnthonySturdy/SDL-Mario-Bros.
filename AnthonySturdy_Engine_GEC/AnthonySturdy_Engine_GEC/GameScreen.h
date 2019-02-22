#pragma once
#include "SDL.h"

class GameScreen {
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:
	SDL_Renderer* mRenderer;
};