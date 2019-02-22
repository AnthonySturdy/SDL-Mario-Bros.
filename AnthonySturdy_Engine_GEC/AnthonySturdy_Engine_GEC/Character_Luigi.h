#pragma once
#include "Character.h"

class Character_Luigi : public Character {
public:
	Character_Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character_Luigi();

	void Update(float deltaTime, SDL_Event e);
};