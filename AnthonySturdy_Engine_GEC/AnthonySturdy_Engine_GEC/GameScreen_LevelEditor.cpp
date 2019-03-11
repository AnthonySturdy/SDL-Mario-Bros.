#include "GameScreen_LevelEditor.h"

// TODO:	- Sprite selection. Either clickable (https://www.dreamincode.net/forums/topic/175010-creating-buttonsmenus-in-sdl/) or a menu type system using WASD/ArrowKeys

GameScreen_LevelEditor::GameScreen_LevelEditor(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY) : GameScreen(renderer) {
	mapSizeX = _mapSizeX;
	mapSizeY = _mapSizeY;

	SetUpLevel();
}

GameScreen_LevelEditor::~GameScreen_LevelEditor() {
	for (int i = 0; i < tileset.size(); i++) {
		delete tileset[i];
	}

	delete texture_tileset;
	delete texture_tileset_cursor;

	delete textureSpriteSelectBackground;
	delete uiSpriteSelectBackground;
	delete uiSpritePick0;
}

bool GameScreen_LevelEditor::SetUpLevel() {
	//Load tileset textures
	texture_tileset = new Texture2D(mRenderer);
	texture_tileset->LoadFromFile("Images/tileset.png");

	texture_tileset_cursor = new Texture2D(mRenderer);
	texture_tileset_cursor->LoadFromFile("Images/tileset_cursor.png");

	//Load each texture source Rect into vector
	for (int y = 0; y < (texture_tileset->GetHeight() / TILE_SIZE); y++) {
		for (int x = 0; x < (texture_tileset->GetWidth() / TILE_SIZE); x++) {
			tileset.push_back(new Rect2D(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		}
	}

	//Create map
	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		map.push_back(SPRITE_CLEAR);
	}

	//Load UI textures
	textureSpriteSelectBackground = new Texture2D(mRenderer);
	textureSpriteSelectBackground->LoadFromFile("Images/UI_TileSelection.png");

	uiSpriteSelectBackground = new UIElement(textureSpriteSelectBackground, Rect2D(31, 210), nullptr);
	uiSpritePick0 = new UIElement(texture_tileset, Rect2D(10, 15, TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[1]);

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
	mouseX /= SCREEN_SCALE;
	mouseY /= SCREEN_SCALE;

	int wX, wY;
	ScreenToWorld(mouseX, mouseY, wX, wY);
	DrawCursor(currentSprite, (zeroWorldToScreenX + wX) * TILE_SIZE, (zeroWorldToScreenY + wY) * TILE_SIZE);

	//UI
	uiSpriteSelectBackground->Render();
	uiSpritePick0->Render();
}

void GameScreen_LevelEditor::Update(float deltaTime, SDL_Event e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mouseX /= SCREEN_SCALE;
	mouseY /= SCREEN_SCALE;
	
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
			//Left mouse down
			leftMouseDown = true;
			map[y * mapSizeX + x] = sprite;
		} else {
			//Left mouse up
			leftMouseDown = false;
		}

		//Erasing tiles
		if (rightMouseDown) {
			//Right mouse held
			map[y * mapSizeX + x] = SPRITE_CLEAR;
		}
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) { 
			//Right mouse down
			rightMouseDown = true;
			map[y * mapSizeX + x] = SPRITE_CLEAR;
		} else {
			//Right mouse up
			rightMouseDown = false;
		}
	}
}

//TODO: Get rid of this function, which is just a middle-man for the RenderCursorSprite function for no reason
void GameScreen_LevelEditor::DrawCursor(unsigned short sprite, int x, int y) {
	RenderCursorSprite(sprite, x, y);
}

void GameScreen_LevelEditor::CameraPanning(int mX, int mY) {
	if (middleMouseDown) {
		//Middle mouse held
		cameraOffsetX -= (mX - startPanX) * 0.004f;
		cameraOffsetY -= (mY - startPanY) * 0.004f;

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
	if (sprite != SPRITE_CLEAR) {
		SDL_Rect source = { tileset[sprite]->x, tileset[sprite]->y, tileset[sprite]->w, tileset[sprite]->h };
		SDL_Rect dest = { x, y, tileset[sprite]->w, tileset[sprite]->h };

		texture_tileset->Render(source, dest, SDL_FLIP_NONE);
	}
}

void GameScreen_LevelEditor::RenderCursorSprite(unsigned short sprite, int x, int y) {
	SDL_Rect source = { tileset[sprite]->x, tileset[sprite]->y, tileset[sprite]->w, tileset[sprite]->h };
	SDL_Rect dest = { x, y, tileset[sprite]->w, tileset[sprite]->h };

	texture_tileset_cursor->Render(source, dest, SDL_FLIP_NONE);
}

void GameScreen_LevelEditor::ScreenToWorld(int screenPosX, int screenPosY, int &x, int &y) {
	x = (int)((screenPosX + (cameraOffsetX*250)) / TILE_SIZE);
	y = (int)((screenPosY + (cameraOffsetY*250)) / TILE_SIZE);
}

void GameScreen_LevelEditor::WorldToScreen(int worldPosX, int worldPosY, int &x, int &y) {
	x = (int)((worldPosX - cameraOffsetX) * TILE_SIZE);
	y = (int)((worldPosY - cameraOffsetY) * TILE_SIZE);
}