#include "GameScreen_MainMenu.h"


GameScreen_MainMenu::GameScreen_MainMenu(SDL_Renderer* renderer, GameScreenManager* _manager) : GameScreen(renderer, _manager) {
	SetUpLevel();
}

GameScreen_MainMenu::~GameScreen_MainMenu() {
	delete marioText;
	delete scoreText;
	delete coinsText;
	delete worldText;
	delete worldText2;
	delete timeText;
	delete copyrightText;
	delete copyrightText2;
	delete menuText1;
	delete menuText2;
	delete menuText3;

	delete superMarioBrosLogoTexture;
	delete superMarioBrosLogo;
}

bool GameScreen_MainMenu::SetUpLevel() {
	//Load font
	fontTexture = new Texture2D(mRenderer);
	fontTexture->LoadFromFile("Images/UI_Font_Sprite.png");

	//Load Background
	tileset = new Texture2D(mRenderer);
	tileset->LoadFromFile("Images/tileset.png");
	for (int i = 0; i < SCREEN_WIDTH; i += 16) {
		groundSpriteLocations.push_back(Rect2D(i, SCREEN_HEIGHT - 32));
		groundSpriteLocations.push_back(Rect2D(i, SCREEN_HEIGHT - 16));
	}
	marioLocation = Rect2D(118, SCREEN_HEIGHT - 48);

	//Load UI
	marioText = new TextElement("Mario", fontTexture, Rect2D(65, 15), mRenderer);
	scoreText = new TextElement("000000", fontTexture, Rect2D(65, 25), mRenderer);
	coinsText = new TextElement("@x00", fontTexture, Rect2D(195, 25), mRenderer);
	worldText = new TextElement("World", fontTexture, Rect2D(305, 15), mRenderer);
	worldText2 = new TextElement("1-1", fontTexture, Rect2D(314, 25), mRenderer);
	timeText = new TextElement("Time", fontTexture, Rect2D(415, 15), mRenderer);
	superMarioBrosLogoTexture = new Texture2D(mRenderer);
	superMarioBrosLogoTexture->LoadFromFile("Images/UI_SDL_Mario_Bros.png");
	superMarioBrosLogo = new UIElement(superMarioBrosLogoTexture, Rect2D((SCREEN_WIDTH / 2)-(superMarioBrosLogoTexture->GetWidth() / 2), 40), nullptr);
	copyrightText = new TextElement("+1985 Nintendo", fontTexture, Rect2D(superMarioBrosLogo->globalPos.x + 226, 216), mRenderer);
	copyrightText2 = new TextElement("#2019 A.Sturdy", fontTexture, Rect2D(superMarioBrosLogo->globalPos.x + 226, 226), mRenderer);
	menuText1 = new TextElement("Play Level 1", fontTexture, Rect2D(200, 266), mRenderer);
	menuText2 = new TextElement("Play Custom Level", fontTexture, Rect2D(200, 286), mRenderer);
	menuText3 = new TextElement("Open Level Editor", fontTexture, Rect2D(200, 306), mRenderer);

	currentMenuSelectionTexture = new Texture2D(mRenderer);
	currentMenuSelectionTexture->LoadFromFile("Images/UI_MainMenu_Cursor.png");
	uiCurrentMenuSelection = new UIElement(currentMenuSelectionTexture, Rect2D(180, 266), nullptr);
	uiMenuButtonRects.push_back(Rect2D(0, 262, SCREEN_WIDTH, 15));
	uiMenuButtonRects.push_back(Rect2D(0, 282, SCREEN_WIDTH, 15));
	uiMenuButtonRects.push_back(Rect2D(0, 302, SCREEN_WIDTH, 15));

	return false;
}

void GameScreen_MainMenu::Render() {
	//Draw background
	SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(mRenderer, 159, 174, 255, 255);
	SDL_RenderFillRect(mRenderer, &backgroundRect);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	SDL_Rect src = { 16, 0, 16, 16 };
	for (int i = 0; i < groundSpriteLocations.size(); i++) {
		SDL_Rect dest = { groundSpriteLocations[i].x, groundSpriteLocations[i].y, 16, 16 };
		tileset->Render(src, dest, SDL_FLIP_NONE);
	}

	src = { 144, 128, 16, 16 };	//Large Bush
	SDL_Rect dest = { (16 * 7), SCREEN_HEIGHT - 80, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 128, 128, 16, 16 };	
	dest = { (16 * 6), SCREEN_HEIGHT - 64, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 144, 144, 16, 16 };
	dest = { (16 * 7), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 160, 128, 16, 16 };
	dest = { (16 * 8), SCREEN_HEIGHT - 64, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 128, 128, 16, 16 };
	dest = { (16 * 5), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 160, 128, 16, 16 };
	dest = { (16 * 9), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 128, 144, 16, 16 };
	dest = { (16 * 6), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 128, 144, 16, 16 };
	dest = { (16 * 7), SCREEN_HEIGHT - 64, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 160, 144, 16, 16 };
	dest = { (16 * 8), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);

	src = { 176, 144, 16, 16 };	//Small Bush
	dest = { SCREEN_WIDTH - (16*9), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 192, 144, 16, 16 };
	dest = { SCREEN_WIDTH - (16 * 8), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 192, 144, 16, 16 };
	dest = { SCREEN_WIDTH - (16 * 7), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 192, 144, 16, 16 };
	dest = { SCREEN_WIDTH - (16 * 6), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);
	src = { 208, 144, 16, 16 };
	dest = { SCREEN_WIDTH - (16 * 5), SCREEN_HEIGHT - 48, 16, 16 };
	tileset->Render(src, dest, SDL_FLIP_NONE);

	src = { 448, 432, 16, 16 };	//Mario
	SDL_Rect destRect = { marioLocation.x, marioLocation.y, 16, 16 };
	tileset->Render(src, destRect, SDL_FLIP_NONE);

	//Draw UI
	marioText->Render();
	scoreText->Render();
	coinsText->Render();
	worldText->Render();
	worldText2->Render();
	timeText->Render();
	superMarioBrosLogo->Render();
	copyrightText->Render();
	copyrightText2->Render();
	menuText1->Render();
	menuText2->Render();
	menuText3->Render();

	uiCurrentMenuSelection->Render();
}

void GameScreen_MainMenu::Update(float deltaTime, SDL_Event e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX /= SCREEN_SCALE;
	mouseY /= SCREEN_SCALE;

	for (int i = 0; i < uiMenuButtonRects.size(); i++) {
		Rect2D r = uiMenuButtonRects[i];

		//If user hovering over sprite
		if ((mouseX > r.x) && (mouseX < r.x + r.w) && (mouseY > r.y) && (mouseY < r.y + r.h)) {
			uiCurrentMenuSelection->globalPos.y = r.y + 4;

			if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
				switch (i) {
				case 0:
					// Clicked Level 1
					manager->ChangeScreen(SCREENS::SCREEN_LEVEL1);
					break;
				case 1:
					//Clicked Custom Level
					manager->ChangeScreen(SCREENS::SCREEN_CUSTOM_LEVEL);
					break;
				case 2:
					//Clicked Level Editor
					manager->ChangeScreen(SCREENS::SCREEN_LEVEL_EDITOR);
					break;
				}
			}
		}
	}
}