#pragma once
#include "Character.h"

class Character_Koopa : public Character {
public:
	Character_Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~Character_Koopa();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void TakeDamage();
	void Jump();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mMovementSpeed;

	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp();
};