#pragma once
#include<string>

#include "SDL.h"
#include "Texture2D.h"
#include "Commons.h"

class TextElement {
public:
	TextElement(std::string _text, Texture2D* _fontTexture, Rect2D _pos, SDL_Renderer* _mRenderer);
	~TextElement();

	std::string text;
	Texture2D* fontTexture;
	Rect2D pos;
	SDL_Color colour;
	
	SDL_Renderer* mRenderer;

	void Render();

private:
	SDL_Rect GetRectFromChar(char c);
};