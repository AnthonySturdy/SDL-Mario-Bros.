#pragma once
#include "Character.h"
#include "SoundEffect.h"

class Character_Mario : public Character {
public:
	Character_Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character_Mario();

	void Update(float deltaTime, SDL_Event e);

private:
	SoundEffect* jumpSound;
};