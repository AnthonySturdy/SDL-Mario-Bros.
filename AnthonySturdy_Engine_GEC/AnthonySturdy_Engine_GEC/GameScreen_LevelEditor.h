#pragma once

#include "SDL.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"

#include <vector>
#include <iostream>

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
	enum SPRITES {
		CLEAR = 0,
		TEST_SPRITE,
		TEST_SPRITE_2
	};
	void EditMap(unsigned short sprite, int x, int y);

	//Camera Panning
	void CameraPanning(int mX, int mY);
	float cameraOffsetX = 0, cameraOffsetY = 0;
	int startPanX = 0, startPanY = 0;

	bool leftMouseDown = false;
	bool middleMouseDown = false;

	Texture2D* texture;
	Texture2D* texture2;
};