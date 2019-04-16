#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

#include <string>
#include <iostream>
#include <vector>

class Entity {
protected:
	SDL_Renderer* mRenderer;
	Texture2D* texture;

	Rect2D collisionRect;

	Vector2D position;
	Vector2D velocity;
	float accelerationSpeed, decelerationSpeed;
	bool isMovingLeft;
	bool isMovingRight;
	float movementSpeed;
	bool isJumping;
	float gravityMultiplier = 1.85f;

	bool isCollidingDown, isCollidingUp, isCollidingLeft, isCollidingRight;
	Rect2D collideUpRect, collideDownRect, collideLeftRect, collideRightRect;

public:
	Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render(Vector2D pos);

	void SetMoveLeft(bool val) { isMovingLeft = val; }
	void SetMoveRight(bool val) { isMovingRight = val; }
	void Jump(float jumpHeight) { velocity.y -= jumpHeight; isJumping = true; }

	void RectCollisionCheck(Rect2D r1, Rect2D r2);

	bool GetIsJumping() { return isJumping; }
	Vector2D GetPosition() { return position; }
	void RefreshCollisionRect() { collisionRect = Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight()); }
	Rect2D GetCollisionRect() { return collisionRect; }
};