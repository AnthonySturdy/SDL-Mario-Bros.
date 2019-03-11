#pragma once

struct Vector2D {
	float x, y;

	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initX, float initY) {
		x = initX;
		y = initY;
	}
};

struct Rect2D {
	float x, y, w, h;

	Rect2D() {
		x = y = w = h = 0.0f;
	}

	Rect2D(int _x, int _y) {
		//Used for UI elements where w and h are defined after
		x = _x;
		y = _y;
		w = h = 0;
	}

	Rect2D(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};

struct Circle2D {
	float x, y, r;

	Circle2D(float _x, float _y, float _r) {
		x = _x;
		y = _y;
		r = _r;
	}
};

enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES,
	SCREEN_LEVEL_EDITOR
};

enum FACING {
	FACING_LEFT = 0,
	FACING_RIGHT
};