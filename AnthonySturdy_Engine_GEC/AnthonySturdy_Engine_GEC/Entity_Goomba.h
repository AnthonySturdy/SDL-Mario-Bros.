#pragma once
#include "Entity.h"

class Entity_Goomba : public Entity {
public:
	Entity_Goomba(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity_Goomba();

	void Update(float deltaTime, SDL_Event e);

};