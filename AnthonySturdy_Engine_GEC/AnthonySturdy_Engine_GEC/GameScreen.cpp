#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer, GameScreenManager* _manager) {
	mRenderer = renderer;
	manager = _manager;
}

GameScreen::~GameScreen() {
	mRenderer = NULL;
}

void GameScreen::Render() {

}

void GameScreen::Update(float deltaTime, SDL_Event e) {

}