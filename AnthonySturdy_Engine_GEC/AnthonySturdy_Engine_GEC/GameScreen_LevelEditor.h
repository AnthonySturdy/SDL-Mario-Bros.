#pragma once

#include "SDL.h"
#include "GameScreen.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "UIElement.h"
#include "TextElement.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

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
	std::vector<unsigned short> entityMap;
	bool ReadMapFromFile(const char* filePath);
	void WriteMapToFile(const char* filePath);
	void RenderMapSprite(unsigned short sprite, int x, int y);		//Renders a sprite from map tileset
	void RenderCursorSprite(unsigned short sprite, int x, int y);	//Renders a sprite from cursor tileset
	enum SPRITES {	//Tileset labels
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
	unsigned short currentSprite = SPRITE_GROUND;		//Current sprite being drawn
	bool EditMap(unsigned short sprite, int x, int y);				//Edit map array

	//Map textures and information
	Texture2D* texture_tileset;
	Texture2D* texture_tileset_cursor;
	std::vector<Rect2D*> tileset;

	//Camera Panning
	bool CameraPanning(int mX, int mY);
	float cameraOffsetX = 0, cameraOffsetY = 0;
	int startPanX = 0, startPanY = 0;

	//Mouse button input
	bool leftMouseDown = false;
	bool middleMouseDown = false;
	bool rightMouseDown = false;

	//UI
	Texture2D* fontTexture;

	bool SelectSprites(int mouseX, int mouseY);
	Texture2D* textureSpriteSelectBackground;
	UIElement* uiSpriteSelectBackground;			//The background sprite behind sprite selection

	SDL_Rect curSpriteHighlight = { 40, 234, 18, 18 };
	std::vector<UIElement*> uiSpriteSelectButtons;	//The sprite select button UI elements
	std::vector<Rect2D> spriteSelectButtonRects;	//Store the position and size of the sprite selection buttons
	std::vector<SPRITES> spriteSelectButtonSprites;	//Corresponds to spriteSelectButtonRects so we know what sprite to switch to on button click

	TextElement* currentSpriteDescription;

	bool isPaused = false;
	bool PauseMenu(int mouseX, int mouseY);
	Texture2D* pauseMenuTexture;
	Texture2D* currentPauseMenuSelectionTexture;
	UIElement* uiPauseMenu;
	UIElement* uiCurrentPauseMenuSelection;
	std::vector<Rect2D> uiPauseMenuButtonRects;
};