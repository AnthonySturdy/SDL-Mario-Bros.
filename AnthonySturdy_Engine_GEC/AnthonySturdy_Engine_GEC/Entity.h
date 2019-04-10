#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

#include <string>

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

public:
	Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void SetMoveLeft(bool val) { isMovingLeft = val; }
	void SetMoveRight(bool val) { isMovingRight = val; }
};