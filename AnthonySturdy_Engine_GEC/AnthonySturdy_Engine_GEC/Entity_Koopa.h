#pragma once
#include "Entity.h"

class Entity_Koopa : public Entity {
private:
	bool isHit = false;
	Texture2D* normalTexture;
	Texture2D* hitTexture;

	int hitFrameDelay = 0; //Delay for when it can be hit again

public:
	Entity_Koopa(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed);
	~Entity_Koopa();

	void Update(float deltaTime, SDL_Event e);

	void Die();

};