#include "Entity_LevelEnd.h"

Entity_LevelEnd::Entity_LevelEnd(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed) {
	isMoveable = false;

	type = ENTITY_TYPE::ENTITY_LEVELEND;

	currentAnimation = new Animation(renderer, "Images/level_end", 1, 1.0f);
}

Entity_LevelEnd::~Entity_LevelEnd() {

}

void Entity_LevelEnd::Update(float deltaTime, SDL_Event e) {
	//If colliding with entity
	if (collidingEntity != nullptr) {
		//If colliding but not up
		if (collidingEntity->type == ENTITY_TYPE::ENTITY_MARIO) {
			collidingEntity->Die();
		}
	}

	Entity::Update(deltaTime, e);
}