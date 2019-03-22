#pragma once
#include<string>

#include "SDL.h"
#include "Commons.h"

class TextElement {
public:
	TextElement(std::string _text, std::string _fontPath, int _fontSize, Rect2D _pos, SDL_Color _colour, SDL_Renderer* _mRenderer);
	~TextElement();

	std::string text, fontPath;
	int fontSize;
	Rect2D pos;
	SDL_Color colour;
	
	SDL_Renderer* mRenderer;

	void Render();
};