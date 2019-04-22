#include "Entity_Koopa.h"

Entity_Koopa::Entity_Koopa(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) : Entity(renderer, startPosition, texturePath, _movementSpeed, _accelerationSpeed, _decelerationSpeed) {
	isMovingLeft = true;

	walkAnimation = new Animation(renderer, "Images/walk_koopa", 2, 0.2f);
	hitAnimation = new Animation(renderer, "Images/hit_koopa", 1, 1.0f);

	currentAnimation = walkAnimation;

	type = ENTITY_TYPE::ENTITY_KOOPA;
}

Entity_Koopa::~Entity_Koopa() {
	delete walkAnimation;
	delete hitAnimation;
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
			currentAnimation = hitAnimation;
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