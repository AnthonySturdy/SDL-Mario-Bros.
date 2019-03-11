#include "UIElement.h"


UIElement::UIElement(Texture2D* _sprite, Rect2D _uiRect, UIElement* _parent, Rect2D _sourceRect) {
	sprite = _sprite;

	uiRect = _uiRect;
	if (uiRect.w == 0 && uiRect.h == 0) {
		//If doesn't specify width and height, default to sprite width and height
		uiRect.w = sprite->GetWidth();
		uiRect.h = sprite->GetHeight();
	}

	parent = _parent;
	if (parent != nullptr) {
		//If this has a parent, this global position is the parents global position + this local position
		globalPos = Vector2D(parent->globalPos.x + uiRect.x, parent->globalPos.y + uiRect.y);
	} else {
		//Otherwise the global position is just the local position as this is at the top of the chain
		globalPos = Vector2D(uiRect.x, uiRect.y);
	}

	if (_sourceRect.x == 0 && _sourceRect.y == 0 && _sourceRect.w == 0 && _sourceRect.h == 0) {
		//If doesn't specify source rect, use whole sprite
		sourceRect = Rect2D(0, 0, sprite->GetWidth(), sprite->GetHeight());
	} else {
		sourceRect = _sourceRect;
	}
}

UIElement::~UIElement() {
	delete sprite;
}

void UIElement::Update(float deltaTime) {

}

void UIElement::Render() {
	SDL_Rect srcRect = { sourceRect.x, sourceRect.y, sourceRect.w, sourceRect.h };
	SDL_Rect destRect = { globalPos.x, globalPos.y, uiRect.w, uiRect.h };

	sprite->Render(srcRect, destRect, SDL_FLIP_NONE);
}
