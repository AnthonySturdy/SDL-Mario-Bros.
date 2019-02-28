#include "Character_Luigi.h"

Character_Luigi::Character_Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map, MOVEMENT_SPEED) {

}

Character_Luigi::~Character_Luigi() {

}

void Character_Luigi::Update(float deltaTime, SDL_Event e) {
	//Call Parent Update to handle gravity/collision/etc.
	Character::Update(deltaTime, e);

	switch (e.type) {
	//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			break;
		case SDLK_w:
			if (mCanJump)
				Jump();
			break;
		}
		break;

	//Key Up Events
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
		break;

	}
}