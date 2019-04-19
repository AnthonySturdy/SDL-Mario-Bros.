#include "Entity_Koopa.h"

Entity_Koopa::Entity_Koopa(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed) {
	isMovingLeft = true;

	normalTexture = texture;
	hitTexture = new Texture2D(renderer);
	hitTexture->LoadFromFile("Images/small_koopa_hit.png");

	type = ENTITY_TYPE::ENTITY_KOOPA;
}

Entity_Koopa::~Entity_Koopa() {

}

void Entity_Koopa::Update(float deltaTime, SDL_Event e) {
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

	hitFrameDelay++;

	Entity::Update(deltaTime, e);
}

void Entity_Koopa::Die() {
	if (hitFrameDelay > 6) {
		hitFrameDelay = 0;

		if (!isHit) {
			isHit = true;
			texture = hitTexture;
			isMovingLeft = false;
			isMovingRight = false;
			velocity.x = 0;
			movementSpeed *= 2;
		} else if (isHit && (isMovingLeft || isMovingRight)) {
			isMovingLeft = false;
			isMovingRight = false;
			velocity.x = 0;
		} else if (isHit && (!isMovingLeft && !isMovingRight)) {
			isMovingLeft = true;
			isMovingRight = true;
		}
	}
}