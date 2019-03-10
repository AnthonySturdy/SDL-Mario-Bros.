#include "UIElement.h"


UIElement::UIElement(Texture2D* _sprite, Rect2D _uiRect, UIElement* _parent, Vector2D _globalPos) {
	sprite = _sprite;
	uiRect = _uiRect;
	parent = _parent;
	globalPos = _globalPos;
}

UIElement::UIElement(Texture2D* _sprite, Rect2D _uiRect, bool _isInteractive, void(*_onClickedFunction)(), UIElement* _parent, Vector2D _globalPos) {
	sprite = _sprite;
	uiRect = _uiRect;
	isInteractive = _isInteractive;
	onClickedFunction = _onClickedFunction;
	parent = _parent;
	globalPos = _globalPos;
}

UIElement::~UIElement() {
	delete sprite;
}

void UIElement::Update(float deltaTime) {
	//If element is interactive
	if (isInteractive) {
		//If user left clicks
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
			//Get mouse position
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			mouseX /= SCREEN_SCALE;
			mouseY /= SCREEN_SCALE;

			//If mouse is over element
			if (mouseX > uiRect.x && mouseY > uiRect.y &&
				mouseX < uiRect.x + uiRect.w && mouseY < uiRect.y + uiRect.h) {
				//Call function pointer
				onClickedFunction();
			}
		}
	}

}

void UIElement::Render() {

}
