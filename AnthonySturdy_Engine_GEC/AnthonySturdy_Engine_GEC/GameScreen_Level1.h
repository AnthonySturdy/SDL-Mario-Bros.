#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Collisions.h"
#include "Character.h"
#include "Character_Mario.h"
#include "Character_Luigi.h"
#include "LevelMap.h"
class Texture2D;
class Character;

class GameScreen_Level1 : public GameScreen {
public:
	GameScreen_Level1(SDL_Renderer* renderer);
	~GameScreen_Level1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mbackgroundTexture;
	Character* myCharacter;
	LevelMap* mLevelMap;

	bool SetUpLevel();
	void SetLevelMap();
};