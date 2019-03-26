#pragma once
#include "SDL.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "UIElement.h"
#include "TextElement.h"

#include <vector>

class GameScreen_MainMenu : public GameScreen {
public:
	GameScreen_MainMenu(SDL_Renderer* renderer, GameScreenManager* _manager);
	~GameScreen_MainMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();

	Texture2D* fontTexture;

	//Main Menu Background
	Texture2D* tileset;
	std::vector<Rect2D> groundSpriteLocations;
	Rect2D marioLocation;

	//Main Menu UI Elements
	TextElement* marioText;
	TextElement* scoreText;
	TextElement* coinsText;
	TextElement* worldText;
	TextElement* worldText2;
	TextElement* timeText;
	TextElement* copyrightText;
	TextElement* copyrightText2;
	TextElement* menuText1;
	TextElement* menuText2;
	TextElement* menuText3;

	Texture2D* superMarioBrosLogoTexture;
	UIElement* superMarioBrosLogo;

	Texture2D* currentMenuSelectionTexture;
	UIElement* uiCurrentMenuSelection;
	std::vector<Rect2D> uiMenuButtonRects;
};