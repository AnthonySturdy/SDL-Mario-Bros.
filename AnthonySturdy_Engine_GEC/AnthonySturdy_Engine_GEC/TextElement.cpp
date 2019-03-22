#include "TextElement.h"

TextElement::TextElement(std::string _text, std::string _fontPath, int _fontSize, Rect2D _pos, SDL_Color _colour, SDL_Renderer* _mRenderer) {
	text = _text;
	fontPath = _fontPath;
	fontSize = _fontSize;
	pos = _pos;
	colour = _colour;
	mRenderer = _mRenderer;
}

TextElement::~TextElement() {

}

void TextElement::Render() {
	//TODO: Text Rendering



	//Setup text render
	//TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	//SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	//SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
	//SDL_Rect textRect = { pos.x, pos.y, pos.w, pos.h };

	////Render text
	//SDL_RenderCopy(mRenderer, textTexture, NULL, &textRect);

	////Destroy pointers
	//SDL_DestroyTexture(textTexture);
	//SDL_FreeSurface(textSurface);
}