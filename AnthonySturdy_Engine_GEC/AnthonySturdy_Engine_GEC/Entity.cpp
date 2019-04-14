#include "Entity.h"


Entity::Entity(SDL_Renderer* renderer, Vector2D startPosition, std::string texturePath, float _movementSpeed, float _accelerationSpeed, float _decelerationSpeed, float _jumpHeight) {
	mRenderer = renderer;
	texture = new Texture2D(renderer);
	texture->LoadFromFile(texturePath);

	position = startPosition;
	movementSpeed = _movementSpeed;
	accelerationSpeed = _accelerationSpeed;
	decelerationSpeed = _decelerationSpeed;
	jumpHeight = _jumpHeight;

	collisionRect = Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight());
}

Entity::~Entity() {

}

void Entity::Update(float deltaTime, SDL_Event e) {
	collisionRect = Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight());

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

	//if (position.y > SCREEN_HEIGHT - 48) {
	//	//If colliding
	//	velocity.y = 0;
	//	position.y = SCREEN_HEIGHT - 48;
	//	isJumping = false;
	//} else {
	//	//If not colliding
	//	velocity.y -= GRAVITY_SPEED;
	//}

	//Collision
	if (isCollidingDown) {
		//If is going down (So not jumping)
		if (velocity.y >= 0) {
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
			position.y += (int)position.y % TILE_SIZE;
		}
	}

	if (isCollidingLeft) {
		//If is going left (toward wall)
		if (velocity.x <= 0) {
			velocity.x = 0;
		}
	}
	if (isCollidingRight) {
		//If is going left (toward wall)
		if (velocity.x >= 0) {
			velocity.x = 0;
			position.x -= (int)position.x % TILE_SIZE;
		}
	}

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	//After everything, set collisions to false (if still colliding, will be set to true before this is called)
	isCollidingDown = isCollidingUp = isCollidingLeft = isCollidingRight = false;
}

void Entity::Render(Vector2D pos) {
	texture->Render(Vector2D(pos.x, position.y), SDL_FLIP_NONE);
}

void Entity::AssignCollisionVariables(std::vector<LevelTile*>* map, int mapSizeX, int mapSizeY) {
	//Called when from gamescreen player is collding. Check surrounding tiles

	//TODO: Figure out how to only have one collision at a time when there's only supposed to be one collision

	int x = round(position.x / TILE_SIZE);
	int y = round((position.y - (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE))) / TILE_SIZE);

	//Colliding below check
	if ((*map)[(y + 1) * mapSizeX + x]->sprite) {
		isCollidingDown = true;
		std::cout << "DOWN";
	}

	std::cout << "\t";

	x = floor(position.x / TILE_SIZE);
	y = floor((position.y - (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE))) / TILE_SIZE);

	//Colliding right check
	if ((*map)[y * mapSizeX + (x + 1)]->sprite) {
		isCollidingRight = true;
		std::cout << "RIGHT";
	}

	std::cout << "\t";

	//Colliding left check
	if ((*map)[y * mapSizeX + (x)]->sprite) {
		isCollidingLeft = true;
		std::cout << "LEFT";
	}

	std::cout << "\t";

	//Colliding above check
	if ((*map)[(y) * mapSizeX + x]->sprite) {
		isCollidingUp = true;
		std::cout << "UP";
	}

	std::cout << "\t" << position.x << "\t" << position.y;

	std::cout << std::endl;

}
