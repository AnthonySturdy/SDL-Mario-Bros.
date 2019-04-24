#pragma once
#include<SDL_mixer.h>
#include<string>

class SoundEffect {
public:
	SoundEffect(std::string filePath);
	~SoundEffect();

	void Play();

private:
	Mix_Chunk* sfx;
};