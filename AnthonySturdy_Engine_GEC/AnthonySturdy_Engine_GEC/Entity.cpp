#include "Entity.h"


Entity::Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed) {
	mRenderer = renderer;
	texture = new Texture2D(renderer);
	texture->LoadFromFile(texturePath);

	position = startPosition;
	movementSpeed = _movementSpeed;
	accelerationSpeed = _accelerationSpeed;
	decelerationSpeed = _decelerationSpeed;

	collisionRect = Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight());
}

Entity::~Entity() {

}

void Entity::Update(float deltaTime, SDL_Event e) {
	//Movement
	if (isMovingLeft) {
		velocity.x -= accelerationSpeed;

		//Limit velocity to movementSpeed
		if (abs(velocity.x) > movementSpeed) {
			velocity.x = -movementSpeed;
		}

		//Quickly switch direction
		if (velocity.x > 0) {
			velocity.x += -decelerationSpeed;
		}

	} else if (isMovingRight) {
		velocity.x += accelerationSpeed;

		//Limit velocity to movementSpeed
		if (abs(velocity.x) > movementSpeed) {
			velocity.x = movementSpeed;
		}

		//Quickly switch direction
		if (velocity.x < 0) {
			velocity.x += decelerationSpeed;
		}

	} else {
		//Apply deceleration (or friction)
		if (velocity.x > 10.0f || velocity.x < -10.0f)
			velocity.x += (velocity.x > 0 ? -decelerationSpeed : decelerationSpeed);
		else
			velocity.x = 0;	//Snap velocity to 0 if gets too small
	}

	//If falling, fall faster
	if (velocity.y > 0 && isJumping == true) {
		velocity.y -= GRAVITY_SPEED * gravityMultiplier;
	} 

	//Collision
	if (isCollidingDown) {
		//If is going down (So not jumping)
		if (velocity.y > 0) {
			velocity.y = 0;
			isJumping = false;
			position.y -= (int)position.y % TILE_SIZE;
		} 

	} else {
		//If not colliding below, apply gravity
		velocity.y -= GRAVITY_SPEED;
		isJumping = true;
	}
	if (isCollidingUp) {
		//If is going up (Jumping)
		if (velocity.y < 0) {
			velocity.y = 0;
		}
	}

	if (isCollidingLeft) {
		//If is going left (toward wall)
		if (velocity.x <= 0 && collideLeftRect.y != collideDownRect.y) {
			velocity.x = 0;
		}
	}
	if (isCollidingRight) {
		//If is going left (toward wall)
		if (velocity.x >= 0 && collideRightRect.y != collideDownRect.y) {
			velocity.x = 0;
		}
	}

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	//After everything, set collisions to false (if still colliding, will be set to true before this is called)
	isCollidingDown = isCollidingUp = isCollidingLeft = isCollidingRight = false;
	collidingEntity = nullptr;
}

void Entity::Render(Vector2D pos) {
	if (isMovingRight || isMovingLeft) {
		flipSprite = !isMovingRight;
	}
	
	texture->Render(Vector2D(pos.x, position.y), (flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

bool Entity::RectCollisionCheck(Rect2D r1, Rect2D r2) {
	bool rVal = false;

	if (r1.x + 1 < r2.x + r2.w &&
		r1.x + r1.w - 1 > r2.x &&
		r1.y < r2.y + r2.h &&
		r1.y + r1.h - (TILE_SIZE / 2) > r2.y) {
		//Up
		isCollidingUp = true;
		collideUpRect = r2;
		rVal = true;
	} else {
		collideUpRect = Rect2D(-999, -999, -999, -999);
	}

	if (r1.x + 1 < r2.x + r2.w &&
		r1.x + r1.w - 1 > r2.x &&
		r1.y + (TILE_SIZE / 2) < r2.y + r2.h &&
		r1.y + r1.h > r2.y) {
		//Down
		isCollidingDown = true;
		collideDownRect = r2;
		rVal = true;
	} else {
		collideUpRect = Rect2D(-999, -999, -999, -999);
	}

	if (r1.x < r2.x + r2.w &&
		r1.x + r1.w - (TILE_SIZE / 2) > r2.x &&
		r1.y + 1 < r2.y + r2.h &&
		r1.y + r1.h - 1 > r2.y) {
		//Left
		isCollidingLeft = true;
		collideLeftRect = r2;
		rVal = true;
	} else {
		collideUpRect = Rect2D(-999, -999, -999, -999);
	}

	if (r1.x + (TILE_SIZE / 2) < r2.x + r2.w &&
		r1.x + r1.w > r2.x &&
		r1.y + 1 < r2.y + r2.h &&
		r1.y + r1.h - 1 > r2.y) {
		//Right
		isCollidingRight = true;
		collideRightRect = r2;
		rVal = true;
	} else {
		collideUpRect = Rect2D(-999, -999, -999, -999);
	}

	return rVal;
}
