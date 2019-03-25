#include "GameScreen_LevelEditor.h"

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
			entityMap.push_back(SPRITE_CLEAR);
		}
	}
	
	//Load UI textures
	fontTexture = new Texture2D(mRenderer);
	fontTexture->LoadFromFile("Images/UI_Font_Sprite.png");

	textureSpriteSelectBackground = new Texture2D(mRenderer);
	textureSpriteSelectBackground->LoadFromFile("Images/UI_TileSelection.png");
	uiSpriteSelectBackground = new UIElement(textureSpriteSelectBackground, Rect2D(31, 220), nullptr);

	currentSpriteDescription = new TextElement("Ground", fontTexture, Rect2D(31, SCREEN_HEIGHT - 15), mRenderer);

#pragma region UI_Buttons
	int xOff = 0, yOff = 0;	//Used for the positioning of buttons so it's easier when coding them

	//Collisions
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
	//Non-Collisions
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
	//Entities
	xOff = 0;
	yOff = 0;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(332 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_ENTITY_MARIO_LEVEL_START]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_ENTITY_MARIO_LEVEL_START);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(332 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_ENTITY_FLAG_LEVEL_END]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_ENTITY_FLAG_LEVEL_END);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(332 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_ENTITY_COIN]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_ENTITY_COIN);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(332 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_ENTITY_GOOMBA]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_ENTITY_GOOMBA);
	xOff++;
	uiSpriteSelectButtons.push_back(new UIElement(texture_tileset, Rect2D(332 + (xOff * 18), 15 + (yOff * 18), TILE_SIZE, TILE_SIZE), uiSpriteSelectBackground, *tileset[SPRITE_ENTITY_KOOPA]));
	spriteSelectButtonRects.push_back(Rect2D(uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.x, uiSpriteSelectButtons[uiSpriteSelectButtons.size() - 1]->globalPos.y, TILE_SIZE, TILE_SIZE));
	spriteSelectButtonSprites.push_back(SPRITE_ENTITY_KOOPA);

#pragma endregion

	pauseMenuTexture = new Texture2D(mRenderer);
	pauseMenuTexture->LoadFromFile("Images/UI_Pause.png");
	currentPauseMenuSelectionTexture = new Texture2D(mRenderer);
	currentPauseMenuSelectionTexture->LoadFromFile("Images/UI_Pause_Cursor.png");
	uiPauseMenu = new UIElement(pauseMenuTexture, Rect2D((SCREEN_WIDTH / 4) - (pauseMenuTexture->GetWidth() / 2), (SCREEN_HEIGHT / 4) - (pauseMenuTexture->GetHeight() / 2)), nullptr);
	uiCurrentPauseMenuSelection = new UIElement(currentPauseMenuSelectionTexture, Rect2D(18, 43), uiPauseMenu);
	uiPauseMenuButtonRects.push_back(Rect2D(uiPauseMenu->globalPos.x + 16, uiPauseMenu->globalPos.y + 43, 92, 7));
	uiPauseMenuButtonRects.push_back(Rect2D(uiPauseMenu->globalPos.x + 16, uiPauseMenu->globalPos.y + 58, 92, 7));
	uiPauseMenuButtonRects.push_back(Rect2D(uiPauseMenu->globalPos.x + 16, uiPauseMenu->globalPos.y + 73, 92, 7));

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
			//Render normal map
			RenderMapSprite(map[y * mapSizeX + x],
							(zeroWorldToScreenX + x) * TILE_SIZE,
							(zeroWorldToScreenY + y) * TILE_SIZE);

			//Render entity map
			RenderMapSprite(entityMap[y * mapSizeX + x],
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
		RenderCursorSprite(currentSprite, (zeroWorldToScreenX + wX) * TILE_SIZE, (zeroWorldToScreenY + wY) * TILE_SIZE);
	}

	//UI
	uiSpriteSelectBackground->Render();

	SDL_SetRenderDrawColor(mRenderer, 255, 20, 20, 255);
	SDL_RenderFillRect(mRenderer, &curSpriteHighlight);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	for (int i = 0; i < uiSpriteSelectButtons.size(); i++) {
		uiSpriteSelectButtons[i]->Render();
	}

	currentSpriteDescription->Render();

	if (isPaused) {
		uiPauseMenu->Render();
		uiCurrentPauseMenuSelection->Render();
	}
}

void GameScreen_LevelEditor::Update(float deltaTime, SDL_Event e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX /= SCREEN_SCALE;
	mouseY /= SCREEN_SCALE;
	int worldMouseX, worldMouseY;
	ScreenToWorld(mouseX, mouseY, worldMouseX, worldMouseY);

	//Keyboard input
	switch (e.type) {
	//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			if (isPaused) {
				isPaused = false;
			} else {
				isPaused = true;
			}
			break;
		}
	}

	//Mouse input
	//It's like this to have layers (of UI and the editor) without cross-interaction
	if (PauseMenu(mouseX, mouseY)) { return; }
	if (SelectSprites(mouseX, mouseY)) { return; }
	if (EditMap(currentSprite, worldMouseX, worldMouseY)) { return; }
	if (CameraPanning(mouseX, mouseY)) { return; }
}

bool GameScreen_LevelEditor::EditMap(unsigned short sprite, int x, int y) {
	//If mouse is in screen bounds
	if (x > -1 && y > -1 &&
		x < mapSizeX && y < mapSizeY) {

		//Drawing tiles
		if (leftMouseDown) {
			//Left mouse held
			if (sprite >= SPRITE_ENTITY_MARIO_LEVEL_START) {
				entityMap[y * mapSizeX + x] = sprite;
			} else {
				map[y * mapSizeX + x] = sprite;
			}
		}
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
			//Left mouse down
			leftMouseDown = true;

			if (sprite >= SPRITE_ENTITY_MARIO_LEVEL_START) {
				entityMap[y * mapSizeX + x] = sprite;
			} else {
				map[y * mapSizeX + x] = sprite;
			}
		} else {
			//Left mouse up
			leftMouseDown = false;
		}

		//Erasing tiles
		if (rightMouseDown) {
			//Right mouse held
			map[y * mapSizeX + x] = SPRITE_CLEAR;
			entityMap[y * mapSizeX + x] = SPRITE_CLEAR;
		}
		if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) { 
			//Right mouse down
			rightMouseDown = true;
			map[y * mapSizeX + x] = SPRITE_CLEAR;
			entityMap[y * mapSizeX + x] = SPRITE_CLEAR;
		} else {
			//Right mouse up
			rightMouseDown = false;
		}
	}

	return (leftMouseDown || rightMouseDown);
}

bool GameScreen_LevelEditor::CameraPanning(int mX, int mY) {
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

	return middleMouseDown;
}

bool GameScreen_LevelEditor::SelectSprites(int mouseX, int mouseY) {
	for (int i = 0; i < spriteSelectButtonRects.size(); i++) {
		Rect2D r = spriteSelectButtonRects[i];

		//If user hovering over sprite
		if ((mouseX > r.x) && (mouseX < r.x + r.w) && (mouseY > r.y) && (mouseY < r.y + r.h)) {
			if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
				//Left mouse down
				std::cout << "Sprite changing to: " << spriteSelectButtonSprites[i] << std::endl;
				currentSprite = spriteSelectButtonSprites[i];
				curSpriteHighlight.x = r.x - 1;
				curSpriteHighlight.y = r.y - 1;

				ChangeSpriteDescription();

				return true;
			}
		}
	}

	return false;
}

void GameScreen_LevelEditor::ChangeSpriteDescription() {
	switch (currentSprite) {
		case SPRITE_CLEAR: currentSpriteDescription->text = "CLEARSPRITE"; break;
		case SPRITE_GROUND: currentSpriteDescription->text = "Ground"; break;
		case SPRITE_BRICK_WHITE_TOP: currentSpriteDescription->text = "Brick (White top)"; break;
		case SPRITE_BRICK: currentSpriteDescription->text = "Brick"; break;
		case SPRITE_BEZEL: currentSpriteDescription->text = "Bezel"; break;
		case SPRITE_QUESTION_BLOCK: currentSpriteDescription->text = "Question Block"; break;
		case SPRITE_QUESTION_BLOCK_USED: currentSpriteDescription->text = "Question Block Used"; break;
		case SPRITE_CASTLE_BRICKS: currentSpriteDescription->text = "Castle Bricks"; break;
		case SPRITE_CASTLE_BATTLEMENT_EMPTY: currentSpriteDescription->text = "Castle Battlement Empty"; break;
		case SPRITE_CASTLE_BATTLEMENT_FULL: currentSpriteDescription->text = "Castle Battlement Full"; break;
		case SPRITE_CASTLE_WINDOW_RIGHT: currentSpriteDescription->text = "Castle Window Right"; break;
		case SPRITE_CASTLE_WINDOW_LEFT: currentSpriteDescription->text = "Castle Window Left"; break;
		case SPRITE_CASTLE_DOOR_ARCH: currentSpriteDescription->text = "Castle door arch"; break;
		case SPRITE_CASTLE_DOOR_BLACK: currentSpriteDescription->text = "Castle door black"; break;
		case SPRITE_PIPE_VERTICAL_OPENING_LEFT: currentSpriteDescription->text = "Pipe vertical opening left"; break;
		case SPRITE_PIPE_VERTICAL_OPENING_RIGHT: currentSpriteDescription->text = "Pipe vertical opening right"; break;
		case SPRITE_PIPE_VERTICAL_BASE_LEFT: currentSpriteDescription->text = "Pipe vertical base left"; break;
		case SPRITE_PIPE_VERTICAL_BASE_RIGHT: currentSpriteDescription->text = "Pipe vertical base right"; break;
		case SPRITE_PIPE_HORIZONTAL_OPENING_TOP: currentSpriteDescription->text = "Pipe horizontal opening top"; break;
		case SPRITE_PIPE_HORIZONTAL_OPENING_BOTTOM: currentSpriteDescription->text = "Pipe horizontal opening bottom"; break;
		case SPRITE_PIPE_HORIZONTAL_BASE_TOP: currentSpriteDescription->text = "Pipe horizontal base top"; break;
		case SPRITE_PIPE_HORIZONTAL_BASE_BOTTOM: currentSpriteDescription->text = "Pipe horizontal base bottom"; break;
		case SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_TOP: currentSpriteDescription->text = "Pipe vertical horizontal connect top"; break;
		case SPRITE_PIPE_VERTICAL_HORIZONTAL_CONNECT_BOTTOM: currentSpriteDescription->text = "Pipe vertical horizontal connect bottom"; break;
		case SPRITE_BUSH_LARGE_LEFT_SLOPE: currentSpriteDescription->text = "Bush large left slope"; break;
		case SPRITE_BUSH_LARGE_LEFT_SPOTS: currentSpriteDescription->text = "Bush large left spots"; break;
		case SPRITE_BUSH_LARGE_TOP: currentSpriteDescription->text = "Bush large top"; break;
		case SPRITE_BUSH_LARGE_FULL: currentSpriteDescription->text = "Bush large full"; break;
		case SPRITE_BUSH_LARGE_RIGHT_SLOPE: currentSpriteDescription->text = "Bush large right slope"; break;
		case SPRITE_BUSH_LARGE_RIGHT_SPOTS: currentSpriteDescription->text = "Bush large right spots"; break;
		case SPRITE_BUSH_SMALL_LEFT: currentSpriteDescription->text = "Bush small left"; break;
		case SPRITE_BUSH_SMALL_MIDDLE: currentSpriteDescription->text = "Bush small middle"; break;
		case SPRITE_BUSH_SMALL_RIGHT: currentSpriteDescription->text = "Bush small right"; break;
		case SPRITE_CLOUD_TOP_LEFT: currentSpriteDescription->text = "Cloud top left"; break;
		case SPRITE_CLOUD_TOP_MIDDLE: currentSpriteDescription->text = "Cloud top middle"; break;
		case SPRITE_CLOUD_TOP_RIGHT: currentSpriteDescription->text = "Cloud top right"; break;
		case SPRITE_CLOUD_BOTTOM_LEFT: currentSpriteDescription->text = "Cloud bottom left"; break;
		case SPRITE_CLOUD_BOTTOM_MIDDLE: currentSpriteDescription->text = "Cloud bottom middle"; break;
		case SPRITE_CLOUD_BOTTOM_RIGHT: currentSpriteDescription->text = "Cloud bottom right"; break;
		case SPRITE_ENTITY_MARIO_LEVEL_START: currentSpriteDescription->text = "Level Start"; break;
		case SPRITE_ENTITY_FLAG_LEVEL_END: currentSpriteDescription->text = "Level End"; break;
		case SPRITE_ENTITY_COIN: currentSpriteDescription->text = "Coin"; break;
		case SPRITE_ENTITY_GOOMBA: currentSpriteDescription->text = "Goomba"; break;
		case SPRITE_ENTITY_KOOPA: currentSpriteDescription->text = "Koopa"; break;
	}
}

bool GameScreen_LevelEditor::PauseMenu(int mouseX, int mouseY) {
	if (isPaused) {
		for (int i = 0; i < uiPauseMenuButtonRects.size(); i++) {
			Rect2D r = uiPauseMenuButtonRects[i];

			//If user hovering over sprite
			if ((mouseX > r.x) && (mouseX < r.x + r.w) && (mouseY > r.y) && (mouseY < r.y + r.h)) {
				uiCurrentPauseMenuSelection->globalPos.y = r.y;

				if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
					switch (i) {
					case 0:
						// Clicked Resume
						isPaused = false;
						break;
					case 1:
						//Clicked Save
						WriteMapToFile("LevelMap.gec");
						break;
					case 2:
						//Clicked Main Menu
						break;
					}
				}
			}
		}

	}

	return isPaused;
}

bool GameScreen_LevelEditor::ReadMapFromFile(const char* filePath) {
	std::ifstream inFile(filePath, std::ifstream::binary);
	if (!inFile.is_open()) {
		std::cout << "Failed to load map file" << std::endl;
		return false ;
	}

	for (int i = 0; i < mapSizeX * mapSizeY; i++) {
		map.push_back(0);
		entityMap.push_back(0);
	}

	inFile.read((char*)&map[0], sizeof(unsigned short) * map.size());
	inFile.read((char*)&entityMap[0], sizeof(unsigned short) * entityMap.size());
	inFile.close();

	return true;
}

void GameScreen_LevelEditor::WriteMapToFile(const char* filePath) {
	std::ofstream outFile(filePath, std::ofstream::binary);
	outFile.write((char*)&map[0], sizeof(unsigned short) * map.size());
	outFile.write((char*)&entityMap[0], sizeof(unsigned short) * entityMap.size());
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
	x = (int)((screenPosX + (cameraOffsetX * 255)) / TILE_SIZE);
	y = (int)((screenPosY + (cameraOffsetY * 255)) / TILE_SIZE);
}

void GameScreen_LevelEditor::WorldToScreen(int worldPosX, int worldPosY, int &x, int &y) {
	x = (int)((worldPosX - cameraOffsetX) * TILE_SIZE);
	y = (int)((worldPosY - cameraOffsetY) * TILE_SIZE);
}