#pragma once
#include "Entity.h"

class Entity_Mario : public Entity {
public:
	Entity_Mario(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity_Mario();

	void Update(float deltaTime, SDL_Event e);

private:
	Animation* idleAnimation;
	Animation* jumpAnimation;
	Animation* runAnimation;

};