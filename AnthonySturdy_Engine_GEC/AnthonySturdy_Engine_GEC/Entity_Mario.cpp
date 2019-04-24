#include "Entity_Mario.h"

Entity_Mario::Entity_Mario(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed) {
	type = ENTITY_TYPE::ENTITY_MARIO;

	idleAnimation = new Animation(renderer, "Images/idle_mario", 1, 1.0f);
	runAnimation = new Animation(renderer, "Images/run_mario", 4, 0.08f);
	jumpAnimation = new Animation(renderer, "Images/jump_mario", 1, 1.0f);

	currentAnimation = idleAnimation;
}

Entity_Mario::~Entity_Mario() {
	delete idleAnimation;
	delete jumpAnimation;
	delete runAnimation;
}

void Entity_Mario::Update(float deltaTime, SDL_Event e) {
	//If colliding with another entity
	if (collidingEntity != nullptr) {
		//If entity is below 
		if (isCollidingDown) {
			if(collidingEntity->type != ENTITY_TYPE::ENTITY_COIN)
				Jump(185);
			collidingEntity->Die();
		}
	}

	if (!isCollidingDown) {
		currentAnimation = jumpAnimation;
	} else if (isMovingLeft || isMovingRight) {
		currentAnimation = runAnimation;
	} else {
		currentAnimation = idleAnimation;
	}

	Entity::Update(deltaTime, e);
}
