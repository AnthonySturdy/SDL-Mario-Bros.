#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

#include<string>
#include<iostream>

class PowBlock {
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	void TakeHit();

	Rect2D	GetCollisionBox()	{ return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); }
	bool	IsAvailable()		{ return mNumberOfHitsLeft > 0; }

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

};