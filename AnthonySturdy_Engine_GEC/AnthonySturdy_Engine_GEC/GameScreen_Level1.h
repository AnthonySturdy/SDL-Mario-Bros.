#pragma once

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Collisions.h"
#include "Character.h"
#include "Character_Mario.h"
#include "Character_Luigi.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Character_Koopa.h"
class Texture2D;
class Character;

#include <vector>

class GameScreen_Level1 : public GameScreen {
public:
	GameScreen_Level1(SDL_Renderer* renderer);
	~GameScreen_Level1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePowBlock();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	Texture2D* mbackgroundTexture;
	Character* myCharacter;
	LevelMap* mLevelMap;

	std::vector<Character_Koopa*> mEnemies;
	float mEnemySpawnCountdown = 0;

	PowBlock* mPowBlock;
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	void DoScreenshake();

	bool SetUpLevel();
	void SetLevelMap();
};