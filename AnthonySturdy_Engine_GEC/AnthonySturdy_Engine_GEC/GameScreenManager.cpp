#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreen_Level1.h"
#include "GameScreen_CustomLevel.h"
#include "GameScreen_LevelEditor.h"
#include "GameScreen_MainMenu.h"

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
		tempScreen = new GameScreen_Level1(mRenderer, this);
		mCurrentScreen = tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LEVEL_EDITOR:
		tempScreen = new GameScreen_LevelEditor(mRenderer, 224, 15, this);
		mCurrentScreen = tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_MAIN_MENU:
		tempScreen = new GameScreen_MainMenu(mRenderer, this);
		mCurrentScreen = tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_CUSTOM_LEVEL:
		tempScreen = new GameScreen_CustomLevel(mRenderer, 224, 15, this);
		mCurrentScreen = tempScreen;
		tempScreen = NULL;
		break;
	}
}