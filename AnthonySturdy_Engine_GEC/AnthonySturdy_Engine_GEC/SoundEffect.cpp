#include "SoundEffect.h"


SoundEffect::SoundEffect(std::string filePath) {
	sfx = Mix_LoadWAV(filePath.c_str());
}

SoundEffect::~SoundEffect() {
	Mix_FreeChunk(sfx);
}

void SoundEffect::Play() {
	Mix_PlayChannel(-1, sfx, 0);
}