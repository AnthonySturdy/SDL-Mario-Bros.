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

	if (velocity.y > 0) {
		//If falling, fall faster
		velocity.y -= GRAVITY_SPEED * gravityMultiplier;
	} 

	if (position.y > SCREEN_HEIGHT - 48) {
		//if colliding
		velocity.y = 0;
		position.y = SCREEN_HEIGHT - 48;
		isJumping = false;
	} else {
		velocity.y -= GRAVITY_SPEED;
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

	int x = round(position.x / TILE_SIZE);
	int y = round((position.y - (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE))) / TILE_SIZE);

	std::cout << "X: " << x << "\tY: " << y << "\tSPR: " << (*map)[y * mapSizeX + x]->sprite << std::endl;

	/*if ((*map)[(int)(position.y / 16) * mapSizeX + (int)(position.x / 16)]) {

	}*/
}
