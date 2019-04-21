#include "Animation.h"

Animation::Animation(SDL_Renderer* mRenderer, std::string spritesDirectory, int _frameCount, float _frameDelay) {
	for (int i = 0; i < _frameCount; i++) {
		frames.push_back(new Texture2D(mRenderer));
		frames[i]->LoadFromFile(spritesDirectory + "/" + std::to_string(i) + ".png");
	}

	frameDelay = _frameDelay;
}

Animation::~Animation() {

}

void Animation::Update(float deltaTime) {
	curFrameTime += deltaTime;

	if (curFrameTime >= frameDelay) {
		curFrameTime = 0;
		curFrame++;
		if (curFrame >= frames.size()) {
			curFrame = 0;
		}
	}
}

void Animation::Render(Vector2D pos, SDL_RendererFlip flip) {
	frames[curFrame]->Render(pos, flip);
}