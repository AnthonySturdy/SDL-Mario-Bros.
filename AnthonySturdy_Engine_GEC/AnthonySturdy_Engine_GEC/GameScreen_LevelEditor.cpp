#include "GameScreen_LevelEditor.h"

// TODO:	- Add more Sprites
//			- Add sprite selection
//			- Make maps playable

GameScreen_LevelEditor::GameScreen_LevelEditor(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY) : GameScreen(renderer) {
	mapSizeX = _mapSizeX;
	mapSizeY = _mapSizeY;

	SetUpLevel();
}

GameScreen_LevelEditor::~GameScreen_LevelEditor() {

}

bool GameScreen_LevelEditor::SetUpLevel() {
	texture = new Texture2D(mRenderer);
	texture->LoadFromFile("Images/testTile.png");

	texture2 = new Texture2D(mRenderer);
	texture2->LoadFromFile("Images/Mario.png");

	for (int i = 0; i < 2; i++) {
		std::stringstream ss;
		ss << "Images/Spritesheet/" << i << ".png";
		spritesheet.push_back(new Texture2D(mRenderer));
		spritesheet[i]->LoadFromFile(ss.str().c_str());

		std::stringstream ss_1;
		ss_1 << "Images/Spritesheet_Cursor/" << i << ".png";
		spritesheet_cursor.push_back(new Texture2D(mRenderer));
		spritesheet_cursor[i]->LoadFromFile(ss_1.str().c_str());
	}

	//Create map
	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		map.push_back(SPRITE_CLEAR);
	}

	return false;
}

void GameScreen_LevelEditor::Render() {
	int zeroWorldToScreenX, zeroWorldToScreenY;
	WorldToScreen(0, 0, zeroWorldToScreenX, zeroWorldToScreenY);
	
	//Draw background
	SDL_Rect backgroundRect;
	backgroundRect.x = zeroWorldToScreenX * TILE_SIZE;
	backgroundRect.y = zeroWorldToScreenY * TILE_SIZE;
	backgroundRect.w = mapSizeX * TILE_SIZE;
	backgroundRect.h = mapSizeY * TILE_SIZE;
	SDL_SetRenderDrawColor(mRenderer, 159, 174, 255, 255);
	SDL_RenderFillRect(mRenderer, &backgroundRect);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	//Draw Map
	for (int x = 0; x < mapSizeX; x++) {
		for (int y = 0; y < mapSizeY; y++) {
			RenderMapSprite(map[y * mapSizeX + x],
							(zeroWorldToScreenX + x) * TILE_SIZE,
							(zeroWorldToScreenY + y) * TILE_SIZE);
		}
	}

	//Draw Cursor
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int wX, wY;
	ScreenToWorld(mouseX, mouseY, wX, wY);
	DrawCursor(currentSprite, (zeroWorldToScreenX + wX) * TILE_SIZE, (zeroWorldToScreenY + wY) * TILE_SIZE);
}

void GameScreen_LevelEditor::Update(float deltaTime, SDL_Event e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	int worldMouseX, worldMouseY;
	ScreenToWorld(mouseX, mouseY, worldMouseX, worldMouseY);

	EditMap(currentSprite, worldMouseX, worldMouseY);
	CameraPanning(mouseX, mouseY);
}

void GameScreen_LevelEditor::EditMap(unsigned short sprite, int x, int y) {
	//If mouse is in screen bounds
	if (x > -1 && y > -1 &&
		x < mapSizeX && y < mapSizeY) {

		//Drawing tiles
		if (leftMouseDown) {
			//Left mouse held
			map[y * mapSizeX + x] = sprite;
		}
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
			//Middle mouse down
			leftMouseDown = true;
			map[y * mapSizeX + x] = sprite;
		} else {
			//Middle mouse up
			leftMouseDown = false;
		}

		//Erasing tiles
		if (rightMouseDown) {
			//Left mouse held
			map[y * mapSizeX + x] = SPRITE_CLEAR;
		}
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) { 
			//Middle mouse down
			rightMouseDown = true;
			map[y * mapSizeX + x] = SPRITE_CLEAR;
		} else {
			//Middle mouse up
			rightMouseDown = false;
		}
	}
}

void GameScreen_LevelEditor::DrawCursor(unsigned short sprite, int x, int y) {
	RenderCursorSprite(sprite, x, y);
}

void GameScreen_LevelEditor::CameraPanning(int mX, int mY) {
	if (middleMouseDown) {
		//Middle mouse held
		cameraOffsetX -= (mX - startPanX) * 0.001f;
		cameraOffsetY -= (mY - startPanY) * 0.001f;

		startPanX = mX;
		startPanY = mY;
	}
	if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2)) {
		//Middle mouse down
		middleMouseDown = true;

		startPanX = mX;
		startPanY = mY;
	} else {
		//Middle mouse up
		middleMouseDown = false;
	}
}

void GameScreen_LevelEditor::RenderMapSprite(unsigned short sprite, int x, int y) {
	if(sprite != SPRITE_CLEAR)
		spritesheet[sprite]->Render(Vector2D(x, y), SDL_FLIP_NONE);
}

void GameScreen_LevelEditor::RenderCursorSprite(unsigned short sprite, int x, int y) {
	spritesheet_cursor[sprite]->Render(Vector2D(x, y), SDL_FLIP_NONE);
}

void GameScreen_LevelEditor::ScreenToWorld(int screenPosX, int screenPosY, int &x, int &y) {
	x = (int)((screenPosX + (cameraOffsetX*1000)) / TILE_SIZE);
	y = (int)((screenPosY + (cameraOffsetY*1000)) / TILE_SIZE);
}

void GameScreen_LevelEditor::WorldToScreen(int worldPosX, int worldPosY, int &x, int &y) {
	x = (int)((worldPosX - cameraOffsetX) * TILE_SIZE);
	y = (int)((worldPosY - cameraOffsetY) * TILE_SIZE);
}