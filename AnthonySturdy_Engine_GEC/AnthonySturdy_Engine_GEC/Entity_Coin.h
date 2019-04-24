#pragma once
#include "Entity.h"

class Entity_Coin : public Entity {
public:
	Entity_Coin(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity_Coin();

	void Update(float deltaTime, SDL_Event e);

};