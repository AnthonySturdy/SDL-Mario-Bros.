#pragma once
#include "SDL.h"
#include "GameScreenManager.h"

class GameScreen {
public:
	GameScreen(SDL_Renderer* renderer, GameScreenManager* _manager);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:
	SDL_Renderer* mRenderer;
	GameScreenManager* manager;
};