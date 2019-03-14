#include "GameScreen_LevelEditor.h"

// TODO:	- Entities
//			- Make map playable

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
	for (int i = 0; i < uiSpriteSelectButtons.size(); i++) {
		delete uiSpriteSelectButtons[i];
	}
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

	if (!ReadMapFromFile("LevelMap.gec")) {
		//If can't load existing map, create blank map
		for (int i = 0; i < mapSizeX * mapSizeY; i++) {
			map.push_back(SPRITE_CLEAR);
		}
	}
	
	//Load UI textures
	textureSpriteSelectBackground = new Texture2D(mRenderer);
	textureSpriteSelectBackground->LoadFromFile("Images/UI_TileSelection.png");
	uiSpriteSelectBackground = new UIElement(textureSpriteSelectBackground, Rect2D(31, 230), nullptr);

#pragma region UI_Buttons
	int xOff = 0, yOff = 0;	//Used for the positioning of buttons so it's easier when coding them

	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_GROUND]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_GROUND);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BRICK_WHITE_TOP]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BRICK_WHITE_TOP);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BRICK]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BRICK);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BEZEL]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BEZEL);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_QUESTION_BLOCK]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_QUESTION_BLOCK);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_QUESTION_BLOCK_USED]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_QUESTION_BLOCK_USED);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_DOOR_ARCH]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_DOOR_ARCH);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_BRICKS]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_BRICKS);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_BATTLEMENT_EMPTY]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_BATTLEMENT_EMPTY);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_BATTLEMENT_FULL]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_BATTLEMENT_FULL);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_WINDOW_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_WINDOW_RIGHT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_WINDOW_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_WINDOW_LEFT);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CASTLE_DOOR_BLACK]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CASTLE_DOOR_BLACK);
	xOff++;
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_OPENING_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_OPENING_LEFT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_OPENING_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_OPENING_RIGHT);
	xOff = 0;
	yOff++;
	xOff++;
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_BASE_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_BASE_LEFT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_BASE_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_BASE_RIGHT);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_HORIZONTAL_OPENING_TOP]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_HORIZONTAL_OPENING_TOP);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_HORIZONTAL_BASE_TOP]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_HORIZONTAL_BASE_TOP);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_BASE_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_HORIZONTAL_OPENING_BOTTOM]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_HORIZONTAL_OPENING_BOTTOM);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_HORIZONTAL_BASE_BOTTOM]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_HORIZONTAL_BASE_BOTTOM);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_BOTTOM]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_BOTTOM);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(10 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_PIPE_VERTICAL_BASE_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP);
	//Re position these +161pixels left
	xOff = 0;
	yOff = 0;
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_TOP]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_TOP);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_SMALL_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_SMALL_LEFT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_SMALL_MIDDLE]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_SMALL_MIDDLE);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_SMALL_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_SMALL_RIGHT);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_LEFT_SLOPE]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_LEFT_SLOPE);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_FULL]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_FULL);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_RIGHT_SLOPE]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_RIGHT_SLOPE);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_TOP_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_TOP_LEFT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_TOP_MIDDLE]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_TOP_MIDDLE);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_TOP_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_TOP_RIGHT);
	xOff = 0;
	yOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_LEFT_SPOTS]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_LEFT_SPOTS);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_FULL]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_FULL);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_BUSH_LARGE_RIGHT_SPOTS]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_BUSH_LARGE_RIGHT_SPOTS);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_BOTTOM_LEFT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_BOTTOM_LEFT);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_BOTTOM_MIDDLE]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_BOTTOM_MIDDLE);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(171 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_CLOUD_BOTTOM_RIGHT]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_CLOUD_BOTTOM_RIGHT);



#pragma endregion

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
	if (wX >= 0 && wY >= 0 && wX < mapSizeX && wY < mapSizeY) {
		DrawCursor(currentSprite, (zeroWorldToScreenX + wX) * TILE_SIZE, (zeroWorldToScreenY + wY) * TILE_SIZE);
	}

	//UI
	uiSpriteSelectBackground->Render();

	SDL_SetRenderDrawColor(mRenderer, 255, 20, 20, 255);
	SDL_RenderFillRect(mRenderer, &curSpriteHighlight);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	for (int i = 0; i < uiSpriteSelectButtons.size(); i++) {
		uiSpriteSelectButtons[i]->Render();
	}
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

	for (int i = 0; i < spriteSelectButtonRects.size(); i++) {
		Rect2D r = spriteSelectButtonRects[i];
		int x, y;
		SDL_GetMouseState(&x, &y);
		x /= SCREEN_SCALE;
		y /= SCREEN_SCALE;

		//If user hovering over sprite
		if ((x > r.x) && (x < r.x + r.w) && (y > r.y) && (y < r.y + r.h)) {
			std::cout << "Hovering index " << i << std::endl;

			if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
				//Left mouse down
				std::cout << "Sprite changing to: " << spriteSelectButtonSprites[i] << std::endl;
				currentSprite = spriteSelectButtonSprites[i];
				curSpriteHighlight.x = r.x - 1;
				curSpriteHighlight.y = r.y - 1;
			}
		}
	}

	switch (e.type) {
	//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_RETURN:
			WriteMapToFile("LevelMap.gec");
			break;
		}
	}
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
		cameraOffsetX -= (mX - startPanX) * 0.005f;
		cameraOffsetY -= (mY - startPanY) * 0.005f;

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

bool GameScreen_LevelEditor::ReadMapFromFile(const char* filePath) {
	std::ifstream inFile(filePath, std::ifstream::binary);
	if (!inFile.is_open()) {
		std::cout << "Failed to load map file" << std::endl;
		return false ;
	}

	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		map.push_back(0);
	}
	inFile.read((char*)&map[0], sizeof(unsigned short) * map.size());
	inFile.close();

	return true;
}

void GameScreen_LevelEditor::WriteMapToFile(const char* filePath) {
	std::ofstream outFile(filePath, std::ofstream::binary);
	outFile.write((char*)&map[0], sizeof(unsigned short) * map.size());
	outFile.close();
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
	x = (int)((screenPosX + (cameraOffsetX*255)) / TILE_SIZE);
	y = (int)((screenPosY + (cameraOffsetY*255)) / TILE_SIZE);
}

void GameScreen_LevelEditor::WorldToScreen(int worldPosX, int worldPosY, int &x, int &y) {
	x = (int)((worldPosX - cameraOffsetX) * TILE_SIZE);
	y = (int)((worldPosY - cameraOffsetY) * TILE_SIZE);
}