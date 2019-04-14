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
	float jumpHeight;
	float gravityMultiplier = 1.5f;

	bool isCollidingDown, isCollidingUp, isCollidingLeft, isCollidingRight;

public:
	Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed, float _jumpHeight);
	~Entity();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render(Vector2D pos);

	void SetMoveLeft(bool val) { isMovingLeft = val; }
	void SetMoveRight(bool val) { isMovingRight = val; }
	void Jump() { velocity.y -= jumpHeight; isJumping = true; }

	void AssignCollisionVariables(std::vector<LevelTile*>* map, int mapSizeX, int mapSizeY);

	void RectCollisionCheck(Rect2D r1, Rect2D r2);

	bool GetIsJumping() { return isJumping; }
	Vector2D GetPosition() { return position; }
	Rect2D GetCollisionRect() { return collisionRect; }
};