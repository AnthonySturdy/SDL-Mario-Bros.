#pragma once
#include"Commons.h"
#include"Texture2D.h"
#include"Constants.h"

class UIElement {
public:
	UIElement(Texture2D* _sprite, Rect2D _uiRect, UIElement* _parent, Vector2D _globalPos);
	UIElement(Texture2D* _sprite, Rect2D _uiRect, bool _isInteractive, void(*_onClickedFunction)(), UIElement* _parent, Vector2D _globalPos);
	~UIElement();

	Texture2D* sprite;				//Image to be rendered
	Rect2D uiRect;					//Position (relative to parent) and size
	bool isInteractive = false;		//If true onClickedFunction will be called when element clicked
	void(*onClickedFunction)();		//Function pointer to call if clicked
	UIElement* parent;				//Allows for child/parent element to group elements
	Vector2D globalPos;				//Global position of this (Sum of all parent positions and current element position)

	virtual void Update(float deltaTime);
	virtual void Render();
};