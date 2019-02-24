#include "GameScreen_LevelEditor.h"

// TODO:	- Add more Sprites
//			- Add erasing
//			- Add sprite selection
//			- Make maps playable

GameScreen_LevelEditor::GameScreen_LevelEditor(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY) : GameScreen(renderer) {
	mapSizeX = _mapSizeX;
	mapSizeY = _mapSizeY;
	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		map.push_back(CLEAR);
	}

	SetUpLevel();
}

GameScreen_LevelEditor::~GameScreen_LevelEditor() {

}

bool GameScreen_LevelEditor::SetUpLevel() {
	texture = new Texture2D(mRenderer);
	texture->LoadFromFile("Images/testTile.png");

	texture2 = new Texture2D(mRenderer);
	texture2->LoadFromFile("Images/Mario.png");

	return false;
}

void GameScreen_LevelEditor::Render() {
	int zeroWorldToScreenX, zeroWorldToScreenY;
	WorldToScreen(0, 0, zeroWorldToScreenX, zeroWorldToScreenY);
	
	SDL_Rect backgroundRect;
	backgroundRect.x = zeroWorldToScreenX * TILE_SIZE;
	backgroundRect.y = zeroWorldToScreenY * TILE_SIZE;
	backgroundRect.w = mapSizeX * TILE_SIZE;
	backgroundRect.h = mapSizeY * TILE_SIZE;
	SDL_SetRenderDrawColor(mRenderer, 159, 174, 255, 255);
	SDL_RenderFillRect(mRenderer, &backgroundRect);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	for (int x = 0; x < mapSizeX; x++) {
		for (int y = 0; y < mapSizeY; y++) {
			RenderMapSprite(map[y * mapSizeX + x],
							(zeroWorldToScreenX + x) * TILE_SIZE,
							(zeroWorldToScreenY + y) * TILE_SIZE);
		}
	}
}

void GameScreen_LevelEditor::Update(float deltaTime, SDL_Event e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	int worldMouseX, worldMouseY;
	ScreenToWorld(mouseX, mouseY, worldMouseX, worldMouseY);
	EditMap(TEST_SPRITE, worldMouseX, worldMouseY);

	CameraPanning(mouseX, mouseY);
}

void GameScreen_LevelEditor::EditMap(unsigned short sprite, int x, int y) {
	if (x > -1 && y > -1 &&
		x < mapSizeX && y < mapSizeY) {
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
	}
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
	switch (sprite) {
	case TEST_SPRITE:
		texture->Render(Vector2D(x, y), SDL_FLIP_NONE);
		break;
	case TEST_SPRITE_2:
		texture2->Render(Vector2D(x, y), SDL_FLIP_NONE);
		break;
	}
}

void GameScreen_LevelEditor::ScreenToWorld(int screenPosX, int screenPosY, int &x, int &y) {
	x = (int)((screenPosX + (cameraOffsetX*1000)) / TILE_SIZE);
	y = (int)((screenPosY + (cameraOffsetY*1000)) / TILE_SIZE);
}

void GameScreen_LevelEditor::WorldToScreen(int worldPosX, int worldPosY, int &x, int &y) {
	x = (int)((worldPosX - cameraOffsetX) * TILE_SIZE);
	y = (int)((worldPosY - cameraOffsetY) * TILE_SIZE);
}