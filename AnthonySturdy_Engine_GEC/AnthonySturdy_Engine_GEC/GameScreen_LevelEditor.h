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
	GameScreen_LevelEditor(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY, GameScreenManager* _manager);
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
	void ChangeSpriteDescription();

	bool isPaused = false;
	bool PauseMenu(int mouseX, int mouseY);
	Texture2D* pauseMenuTexture;
	Texture2D* currentPauseMenuSelectionTexture;
	UIElement* uiPauseMenu;
	UIElement* uiCurrentPauseMenuSelection;
	std::vector<Rect2D> uiPauseMenuButtonRects;
};