#include "Character_Mario.h"

Character_Mario::Character_Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {

}


Character_Mario::~Character_Mario() {

}

void Character_Mario::Update(float deltaTime, SDL_Event e) {
	//Call Parent Update to handle gravity/collision/etc.
	Character::Update(deltaTime, e);

	switch (e.type) {
	//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			break;
		case SDLK_UP:
			if (mCanJump)
				Jump();
			break;
		}
		break;

	//Key Up Events
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
		break;

	}
}