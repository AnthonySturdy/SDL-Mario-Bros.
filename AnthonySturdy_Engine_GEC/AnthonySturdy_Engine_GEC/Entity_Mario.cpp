#include "Entity_Mario.h"

Entity_Mario::Entity_Mario(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed) {
	type = ENTITY_TYPE::ENTITY_MARIO;
}

Entity_Mario::~Entity_Mario() {

}

void Entity_Mario::Update(float deltaTime, SDL_Event e) {
	//If colliding with another entity
	if (collidingEntity != nullptr) {
		//If entity is below 
		if (isCollidingDown) {
			Jump(750);
			collidingEntity->Die();
		}
	}

	Entity::Update(deltaTime, e);
}
