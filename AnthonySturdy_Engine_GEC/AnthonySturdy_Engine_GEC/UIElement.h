#pragma once
#include"Commons.h"
#include"Texture2D.h"
#include"Constants.h"

class UIElement {
public:
	UIElement(Texture2D* _sprite, Rect2D _uiRect, UIElement* _parent, Rect2D _sourceRect = Rect2D());
	~UIElement();

	Texture2D* sprite;				//Image to be rendered
	Rect2D uiRect;					//Position (relative to parent) and size
	UIElement* parent;				//Allows for child/parent element to group elements
	Vector2D globalPos;				//Global position of this (Sum of all parent positions and current element position)
	Rect2D sourceRect;				//SourceRect is optional

	virtual void Update(float deltaTime);
	virtual void Render();
};