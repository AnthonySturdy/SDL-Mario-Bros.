#pragma once

#include "SDL.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

#include <vector>
#include <iostream>
#include <sstream>

class GameScreen_LevelEditor : public GameScreen {
public:
	GameScreen_LevelEditor(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY);
	~GameScreen_LevelEditor();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
	
	void ScreenToWorld(int screenPosX, int screenPosY, int &x, int &y);
	void WorldToScreen(int worldPosX, int worldPosY, int &x, int &y);

	//Map
	int mapSizeX, mapSizeY;
	std::vector<unsigned short> map;
	void RenderMapSprite(unsigned short sprite, int x, int y);
	void RenderCursorSprite(unsigned short sprite, int x, int y);
	enum SPRITES {
		SPRITE_CLEAR = 0,
		SPRITE_TEST,
		SPRITE_TEST_2
	};
	unsigned short currentSprite = SPRITE_TEST;
	void EditMap(unsigned short sprite, int x, int y);
	void DrawCursor(unsigned short sprite, int x, int y);

	//Camera Panning
	void CameraPanning(int mX, int mY);
	float cameraOffsetX = 0, cameraOffsetY = 0;
	int startPanX = 0, startPanY = 0;

	//Mouse button input
	bool leftMouseDown = false;
	bool middleMouseDown = false;
	bool rightMouseDown = false;

	Texture2D* texture;
	Texture2D* texture2;
	std::vector<Texture2D*> spritesheet;
	std::vector<Texture2D*> spritesheet_cursor;
};