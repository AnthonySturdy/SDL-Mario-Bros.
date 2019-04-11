#pragma once
#include "GameScreen.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include "Entity.h"
#include "Commons.h"

#include <vector>
#include <fstream>
#include <iostream>

class GameScreen_CustomLevel : public GameScreen {
public:
	GameScreen_CustomLevel(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY, GameScreenManager* _manager);
	~GameScreen_CustomLevel();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	void SetUpLevel();

	Entity* tempPlayer;

	int halfScreen = SCREEN_WIDTH / 2;

	//Map
	int mapSizeX, mapSizeY;
	std::vector<unsigned short> map;
	std::vector<unsigned short> entityMap;
	bool ReadMapFromFile(const char* filePath);
	enum SPRITES {	//Tileset Positions
		SPRITE_CLEAR = 0,
		SPRITE_GROUND = 1,
		SPRITE_BRICK_WHITE_TOP = 2,
		SPRITE_BRICK = 3,
		SPRITE_BEZEL = 34,
		SPRITE_QUESTION_BLOCK = 25,
		SPRITE_QUESTION_BLOCK_USED = 4,
		SPRITE_CASTLE_BRICKS = 14,
		SPRITE_CASTLE_BATTLEMENT_EMPTY = 12,
		SPRITE_CASTLE_BATTLEMENT_FULL = 45,
		SPRITE_CASTLE_WINDOW_RIGHT = 13,
		SPRITE_CASTLE_WINDOW_LEFT = 15,
		SPRITE_CASTLE_DOOR_ARCH = 46,
		SPRITE_CASTLE_DOOR_BLACK = 47,
		SPRITE_PIPE_VERTICAL_OPENING_LEFT = 264,
		SPRITE_PIPE_VERTICAL_OPENING_RIGHT = 265,
		SPRITE_PIPE_VERTICAL_BASE_LEFT = 297,
		SPRITE_PIPE_VERTICAL_BASE_RIGHT = 298,
		SPRITE_PIPE_HORIZONTAL_OPENING_TOP = 266,
		SPRITE_PIPE_HORIZONTAL_OPENING_BOTTOM = 299,
		SPRITE_PIPE_HORIZONTAL_BASE_TOP = 267,
		SPRITE_PIPE_HORIZONTAL_BASE_BOTTOM = 300,
		SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP = 268,
		SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_BOTTOM = 301,
		SPRITE_BUSH_LARGE_LEFT_SLOPE = 272,
		SPRITE_BUSH_LARGE_LEFT_SPOTS = 305,
		SPRITE_BUSH_LARGE_TOP = 273,
		SPRITE_BUSH_LARGE_FULL = 306,
		SPRITE_BUSH_LARGE_RIGHT_SLOPE = 274,
		SPRITE_BUSH_LARGE_RIGHT_SPOTS = 307,
		SPRITE_BUSH_SMALL_LEFT = 308,
		SPRITE_BUSH_SMALL_MIDDLE = 309,
		SPRITE_BUSH_SMALL_RIGHT = 310,
		SPRITE_CLOUD_TOP_LEFT = 660,
		SPRITE_CLOUD_TOP_MIDDLE = 661,
		SPRITE_CLOUD_TOP_RIGHT = 662,
		SPRITE_CLOUD_BOTTOM_LEFT = 693,
		SPRITE_CLOUD_BOTTOM_MIDDLE = 694,
		SPRITE_CLOUD_BOTTOM_RIGHT = 695,
		SPRITE_ENTITY_MARIO_LEVEL_START = 919,
		SPRITE_ENTITY_FLAG_LEVEL_END = 920,
		SPRITE_ENTITY_COIN = 921,
		SPRITE_ENTITY_GOOMBA = 922,
		SPRITE_ENTITY_KOOPA = 923
	};
	Texture2D* texture_tileset;
	std::vector<Rect2D*> tileset;
	std::vector<LevelTile*> levelTiles;
	bool IsTileCollidable(unsigned short sprite);

};