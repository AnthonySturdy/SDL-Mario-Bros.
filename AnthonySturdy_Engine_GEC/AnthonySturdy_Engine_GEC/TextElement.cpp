#include "TextElement.h"

TextElement::TextElement(std::string _text, Texture2D* _fontTexture, Rect2D _pos, SDL_Renderer* _mRenderer) {
	text = _text;
	fontTexture = _fontTexture;
	pos = _pos;
	mRenderer = _mRenderer;
}

TextElement::~TextElement() {
	delete fontTexture;
}

void TextElement::Render() {
	for (int i = 0; i < text.length(); i++) {
		SDL_Rect dest = { pos.x + (i * 9), pos.y, 10, 10 };
		fontTexture->Render(GetRectFromChar(text[i]), dest, SDL_FLIP_NONE);
	}
}

SDL_Rect TextElement::GetRectFromChar(char c) {
	SDL_Rect r;

	switch (c) {
	//Letters
	case 'a':
	case 'A':
		r = { 0, 0, 10, 10 };
		break;
	case 'b':
	case 'B':
		r = { 10, 0, 10, 10 };
		break;
	case 'c':
	case 'C':
		r = { 20, 0, 10, 10 };
		break;
	case 'd':
	case 'D':
		r = { 30, 0, 10, 10 };
		break;
	case 'e':
	case 'E':
		r = { 40, 0, 10, 10 };
		break;
	case 'f':
	case 'F':
		r = { 50, 0, 10, 10 };
		break;
	case 'g':
	case 'G':
		r = { 60, 0, 10, 10 };
		break;
	case 'h':
	case 'H':
		r = { 70, 0, 10, 10 };
		break;
	case 'i':
	case 'I':
		r = { 80, 0, 10, 10 };
		break;
	case 'j':
	case 'J':
		r = { 90, 0, 10, 10 };
		break;
	case 'k':
	case 'K':
		r = { 100, 0, 10, 10 };
		break;
	case 'l':
	case 'L':
		r = { 110, 0, 10, 10 };
		break;
	case 'm':
	case 'M':
		r = { 120, 0, 10, 10 };
		break;
	case 'n':
	case 'N':
		r = { 130, 0, 10, 10 };
		break;
	case 'o':
	case 'O':
		r = { 140, 0, 10, 10 };
		break;
	case 'p':
	case 'P':
		r = { 150, 0, 10, 10 };
		break;
	case 'q':
	case 'Q':
		r = { 160, 0, 10, 10 };
		break;
	case 'r':
	case 'R':
		r = { 170, 0, 10, 10 };
		break;
	case 's':
	case 'S':
		r = { 180, 0, 10, 10 };
		break;
	case 't':
	case 'T':
		r = { 190, 0, 10, 10 };
		break;
	case 'u':
	case 'U':
		r = { 200, 0, 10, 10 };
		break;
	case 'v':
	case 'V':
		r = { 210, 0, 10, 10 };
		break;
	case 'w':
	case 'W':
		r = { 220, 0, 10, 10 };
		break;
	case 'x':
	case 'X':
		r = { 230, 0, 10, 10 };
		break;
	case 'y':
	case 'Y':
		r = { 240, 0, 10, 10 };
		break;
	case 'z':
	case 'Z':
		r = { 250, 0, 10, 10 };
		break;
	//Numbers
	case '0':
		r = { 0, 10, 10, 10 };
		break;
	case '1':
		r = { 10, 10, 10, 10 };
		break;
	case '2':
		r = { 20, 10, 10, 10 };
		break;
	case '3':
		r = { 30, 10, 10, 10 };
		break;
	case '4':
		r = { 40, 10, 10, 10 };
		break;
	case '5':
		r = { 50, 10, 10, 10 };
		break;
	case '6':
		r = { 60, 10, 10, 10 };
		break;
	case '7':
		r = { 70, 10, 10, 10 };
		break;
	case '8':
		r = { 80, 10, 10, 10 };
		break;
	case '9':
		r = { 90, 10, 10, 10 };
		break;
	//Special
	case ' ':
		r = { 100, 10, 10, 10 };
		break;
	case '.':
		r = { 110, 10, 10, 10 };
		break;
	case '"':
	case '\'':
		r = { 120, 10, 10, 10 };
		break;
	case ',':
		r = { 130, 10, 10, 10 };
		break;
	case '-':
		r = { 140, 10, 10, 10 };
		break;
	case '?':
		r = { 150, 10, 10, 10 };
		break;
	case '!':
		r = { 160, 10, 10, 10 };
		break;
	case '(':
		r = { 170, 10, 10, 10 };
		break;
	case ')':
		r = { 180, 10, 10, 10 };
		break;
	case '+':
		r = { 220, 20, 10, 10 };
		break;
	case '#':
		r = { 230, 20, 10, 10 };
		break;
	case '@':
		r = { 240, 20, 10, 10 };
		break;
	default:
		r = { 250, 20, 10, 10 };

		break;
	}

	return r;
}
