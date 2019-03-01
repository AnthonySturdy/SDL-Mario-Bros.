#include "Character_Koopa.h"

Character_Koopa::Character_Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map, KOOPA_SPEED) {
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	isAlive = true;

	mSingleSpriteWidth = mTexture->GetWidth()/2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

Character_Koopa::~Character_Koopa() {

}

void Character_Koopa::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

	if (!mInjured) {
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		} else if (mFacingDirection == FACING_RIGHT) {
			mMovingRight = true;
			mMovingLeft = false;
		}
	} else {
		mMovingRight = false;
		mMovingLeft = false;
		
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0) {
			FlipRightWayUp();
		}
	}
}

void Character_Koopa::Render() {
	int left = 0;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	} else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void Character_Koopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void Character_Koopa::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void Character_Koopa::FlipRightWayUp() {
	mFacingDirection = (mFacingDirection == FACING_RIGHT ? FACING_LEFT : FACING_RIGHT);
	mInjured = false;
	Jump();
}