#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

#include<string>
#include<vector>

class Animation {
public:
	Animation(SDL_Renderer* mRenderer, std::string spritesDirectory, int _frameCount, float _frameDelay);
	~Animation();

	void Update(float deltaTime);
	void Render(Vector2D pos, SDL_RendererFlip flip);

	Texture2D* GetFrame(int i) { return frames[i]; }

private:
	int curFrame;
	float frameDelay;
	float curFrameTime;
	std::vector<Texture2D*> frames;
};