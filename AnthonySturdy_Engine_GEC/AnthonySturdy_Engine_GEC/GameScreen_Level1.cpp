#include "GameScreen_Level1.h"
#include "Texture2D.h"

#include <iostream>

GameScreen_Level1::GameScreen_Level1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	mLevelMap = NULL;
}

GameScreen_Level1::~GameScreen_Level1() {
	delete mbackgroundTexture;
	mbackgroundTexture = NULL;

	delete myCharacter;
	myCharacter = NULL;
}

bool GameScreen_Level1::SetUpLevel() {
	mbackgroundTexture = new Texture2D(mRenderer);
	if (!mbackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}

	SetLevelMap();

	myCharacter = new Character_Mario(mRenderer, "Images/Mario.png", Vector2D(200, 0), mLevelMap);

	return true;
}

void GameScreen_Level1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up old map
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);
}

void GameScreen_Level1::Render() {
	mbackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	myCharacter->Render();
}

void GameScreen_Level1::Update(float deltaTime, SDL_Event e) {
	myCharacter->Update(deltaTime, e);
}