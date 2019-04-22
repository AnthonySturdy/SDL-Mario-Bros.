#pragma once
#include "Entity.h"

class Entity_LevelEnd : public Entity {
public:
	Entity_LevelEnd(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity_LevelEnd();

	void Update(float deltaTime, SDL_Event e);

};