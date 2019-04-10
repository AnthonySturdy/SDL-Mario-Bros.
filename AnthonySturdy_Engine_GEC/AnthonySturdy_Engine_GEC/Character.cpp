#include "Character.h"


Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float _movementSpeed) {
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mCurrentLevelMap = map;

	SetPosition(startPosition);
	mFacingDirection = FACING_RIGHT;
	SetCollisionRadius(15.0f);
	movementSpeed = _movementSpeed;
}

Character::~Character() {
	mRenderer = NULL;
}

void Character::Render() {
	mTexture->Render(mPosition, (mFacingDirection == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL), 0.0);
}

void Character::Update(float deltaTime, SDL_Event e) {

	int centralXPosition =	(int)(mPosition.x + (mTexture->GetWidth()*0.5f)) / TILE_SIZE / SCREEN_SCALE;
	int footPosition =		(int)(mPosition.y + mTexture->GetHeight()) / TILE_SIZE / SCREEN_SCALE;

	if (mCurrentLevelMap->GetTileAt(centralXPosition, footPosition) == 0) {
		AddGravity(deltaTime);
	} else {
		//Collided with ground so can jump again
		mCanJump = true;
	}

	if (mJumping) {
		mPosition.y -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mMovingLeft) {
		MoveLeft(deltaTime);
	} else if(mMovingRight){
		MoveRight(deltaTime);
	}
}

void Character::CancelJump() {
	mJumping = false;
}

void Character::MoveLeft(float deltaTime) {
	mPosition.x -= movementSpeed * deltaTime;
	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime) {
	mPosition.x += movementSpeed * deltaTime;
	mFacingDirection = FACING_RIGHT;
}

void Character::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::AddGravity(float deltaTime) {
	mPosition.y += GRAVITY_SPEED * deltaTime;
	mCanJump = false;
}