#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreen_Level1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen = NULL;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;
	
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render() {
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	if (mCurrentScreen != NULL)
		delete mCurrentScreen;

	GameScreen* tempScreen;

	switch (newScreen) {
	case SCREEN_LEVEL1:
		tempScreen = new GameScreen_Level1(mRenderer);
		mCurrentScreen = tempScreen;
		tempScreen = NULL;
		break;
	}
}