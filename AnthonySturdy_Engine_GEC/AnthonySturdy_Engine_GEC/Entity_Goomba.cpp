#include "Entity_Goomba.h"

Entity_Goomba::Entity_Goomba(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed){
	isMovingLeft = true;

	type = ENTITY_TYPE::ENTITY_GOOMBA;
}

Entity_Goomba::~Entity_Goomba() {

}

void Entity_Goomba::Update(float deltaTime, SDL_Event e) {
	if (isCollidingLeft) {
		isMovingLeft = false;
		isMovingRight = true;

	} else if (isCollidingRight) {
		isMovingLeft = true;
		isMovingRight = false;
	}

	//If colliding with entity
	if (collidingEntity != nullptr) {
		//If colliding but not up
		if (!isCollidingUp && collidingEntity->type == ENTITY_TYPE::ENTITY_MARIO) {
			collidingEntity->Die();
		}
	}

	Entity::Update(deltaTime, e);
}
