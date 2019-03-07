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
	
	void ScreenToWorld(int screenPosX, int screenPosY, int &x, int &y);	//Converts screen point to map point
	void WorldToScreen(int worldPosX, int worldPosY, int &x, int &y);	//Converts map point to screen point

	//Map
	int mapSizeX, mapSizeY;
	std::vector<unsigned short> map;
	void RenderMapSprite(unsigned short sprite, int x, int y);		//Renders a sprite from map tileset
	void RenderCursorSprite(unsigned short sprite, int x, int y);	//Renders a sprite from cursor tileset
	enum SPRITES {	//Tileset labels		TODO: LABEL ALL TILES THAT WILL BE USED
		SPRITE_CLEAR = 0,
		SPRITE_GROUND,
		SPRITE_BRICK_WALL_WHITE_TOP,
		SPRITE_BRICK_WALL,
		SPRITE_QUESTION_BLOCK_USED,
	};
	unsigned short currentSprite = SPRITE_QUESTION_BLOCK_USED;		//Current sprite being drawn
	void EditMap(unsigned short sprite, int x, int y);				//Edit map array
	void DrawCursor(unsigned short sprite, int x, int y);

	//Map textures and information
	Texture2D* texture_tileset;
	Texture2D* texture_tileset_cursor;
	std::vector<Rect2D*> tileset;
	std::vector<Rect2D*> tileset_cursor;

	//Camera Panning
	void CameraPanning(int mX, int mY);
	float cameraOffsetX = 0, cameraOffsetY = 0;
	int startPanX = 0, startPanY = 0;

	//Mouse button input
	bool leftMouseDown = false;
	bool middleMouseDown = false;
	bool rightMouseDown = false;
};