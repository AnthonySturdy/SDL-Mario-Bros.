#pragma once

#include"Character.h"
#include"Commons.h"

class Collisions {
private:
	Collisions();
	static Collisions* mInstance;

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Circle2D circle1, Circle2D circle2);
	bool Box(Rect2D rect1, Rect2D rect2);
};