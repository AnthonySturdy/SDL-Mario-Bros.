#include "GameScreen_Level1.h"
#include "Texture2D.h"

#include <iostream>

GameScreen_Level1::GameScreen_Level1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	//mLevelMap = NULL;

	mEnemySpawnCountdown = KOOPA_SPAWN_DELAY;
}

GameScreen_Level1::~GameScreen_Level1() {
	delete mbackgroundTexture;
	mbackgroundTexture = NULL;

	delete myCharacter;
	myCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mLevelMap = NULL;

	mEnemies.clear();
}

void GameScreen_Level1::DoScreenshake() {
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

bool GameScreen_Level1::SetUpLevel() {
	mbackgroundTexture = new Texture2D(mRenderer);
	if (!mbackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}

	SetLevelMap();

	myCharacter = new Character_Mario(mRenderer, "Images/Mario.png", Vector2D(200, 0), mLevelMap);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

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
									{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
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
	mbackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	myCharacter->Render();

	mPowBlock->Render();

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
}

void GameScreen_Level1::Update(float deltaTime, SDL_Event e) {
	if (mScreenshake) {
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;
		
		if (mScreenshakeTime <= 0.0f) {
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	myCharacter->Update(deltaTime, e);

	UpdatePowBlock();

	mEnemySpawnCountdown -= deltaTime;
	if (mEnemySpawnCountdown <= 0) {
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

		mEnemySpawnCountdown = KOOPA_SPAWN_DELAY;
	}
	UpdateEnemies(deltaTime, e);
}

void GameScreen_Level1::UpdatePowBlock() {
	if (Collisions::Instance()->Box(mPowBlock->GetCollisionBox(), myCharacter->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (myCharacter->IsJumping()) {
				DoScreenshake();
				mPowBlock->TakeHit();
				myCharacter->CancelJump();
			}
		}
	}
}

void GameScreen_Level1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			//Check if enemy is on bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f) {
				//Is enemy off screen to left or right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().w*0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().w*0.55f)) {
					mEnemies[i]->SetAlive(false);
				}
			}

			mEnemies[i]->Update(deltaTime, e);
			
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) {
				//Disable collisions if behind a pipe
			} else {
				if (Collisions::Instance()->Circle(mEnemies[i]->GetCollisionCircle(), myCharacter->GetCollisionCircle())) {
					//Check to see if enemy is colliding with player
					if (mEnemies[i]->GetIsInjured()) {
						mEnemies[i]->SetAlive(false);
					} else {
						//myCharacter.SetState(CHARACTERSTATE_PLAYER_DEATH);
					}
				}
			}

			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreen_Level1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	Character_Koopa* koopaCharacter = new Character_Koopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);

	mEnemies.push_back(koopaCharacter);
}