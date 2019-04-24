#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Animation.h"
#include "SoundEffect.h"

#include <string>
#include <iostream>
#include <vector>

class Entity {
protected:
	SDL_Renderer* mRenderer;
	Animation* currentAnimation;
	bool flipSprite = false;
	Rect2D collisionRect;

	Texture2D* texture;	//Used for w/h only

	bool isDead;

	Vector2D position;
	Vector2D velocity;
	float accelerationSpeed, decelerationSpeed;
	bool isMoveable = true;
	bool isMovingLeft;
	bool isMovingRight;
	float movementSpeed;
	bool isJumping;
	float gravityMultiplier = 1.85f;

	bool isCollidingDown, isCollidingUp, isCollidingLeft, isCollidingRight;
	Rect2D collideUpRect, collideDownRect, collideLeftRect, collideRightRect;
	Entity* collidingEntity;

public:
	Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render(Vector2D pos);

	void SetMoveLeft(bool val) { isMovingLeft = val; }
	void SetMoveRight(bool val) { isMovingRight = val; }
	void Jump(float jumpHeight) { velocity.y = 0; velocity.y -= jumpHeight; isJumping = true; }
	virtual void Die() { isDead = true; }

	bool RectCollisionCheck(Rect2D r1, Rect2D r2);

	bool GetIsJumping() { return isJumping; }
	Vector2D GetPosition() { return position; }
	void RefreshCollisionRect() { collisionRect = Rect2D(position.x, position.y, currentAnimation->GetFrame(0)->GetWidth(), currentAnimation->GetFrame(0)->GetHeight()); }
	Rect2D GetCollisionRect() { return collisionRect; }
	void SetCollidingEntity(Entity* e) { collidingEntity = e; }
	Entity* GetCollidingEntity() { return collidingEntity; }
	bool GetIsDead() { return isDead; }

	ENTITY_TYPE type = ENTITY_TYPE::ENTITY_DEFAULT;
};