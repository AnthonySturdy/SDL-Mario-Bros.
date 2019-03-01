#pragma once

#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"

#include<iostream>
#include<string>

class Character {
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;

	float movementSpeed;
	bool mMovingLeft;
	bool mMovingRight;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	float mCollisionRadius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void Jump();
	void AddGravity(float deltaTime);


public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float _movementSpeed);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool		IsJumping()						{ return mJumping; }
	void CancelJump();

	void		SetPosition(Vector2D newPos)	{ mPosition = newPos; }
	Vector2D	GetPosition()					{ return mPosition; }
	void		SetCollisionRadius(float radius){ mCollisionRadius = radius; }
	float		GetCollisionRadius()			{ return mCollisionRadius; }

	Rect2D		GetCollisionBox()				{ return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }
	Circle2D	GetCollisionCircle()			{ return Circle2D(mPosition.x, mPosition.y, GetCollisionRadius()); }
};