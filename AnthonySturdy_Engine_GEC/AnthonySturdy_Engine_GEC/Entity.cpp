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
	collisionRect = Rect2D(position.x, position.y, texture->GetWidth(), texture->GetHeight());

	//Movement
	if (isMovingLeft) {
		velocity.x -= deltaTime * accelerationSpeed;
		if (abs(velocity.x) > movementSpeed) {
			velocity.x = movementSpeed;
		}

	} else if (isMovingRight) {
		velocity.x += deltaTime * accelerationSpeed;
		if (abs(velocity.x) > movementSpeed) {
			velocity.x = movementSpeed;
		}

	}

	position.x += velocity.x;
	position.y += velocity.y;
}

void Entity::Render() {
	texture->Render(position, SDL_FLIP_NONE);
}
