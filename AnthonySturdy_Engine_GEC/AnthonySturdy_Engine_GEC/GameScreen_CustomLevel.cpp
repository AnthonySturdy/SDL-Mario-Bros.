#include "GameScreen_CustomLevel.h"

GameScreen_CustomLevel::GameScreen_CustomLevel(SDL_Renderer* renderer, int _mapSizeX, int _mapSizeY, GameScreenManager* _manager) : GameScreen(renderer, _manager) {
	mapSizeX = _mapSizeX;
	mapSizeY = _mapSizeY;

	SetUpLevel();
}

GameScreen_CustomLevel::~GameScreen_CustomLevel() {

}

void GameScreen_CustomLevel::SetUpLevel() {
	if (!ReadMapFromFile("LevelMap.gec")) {
		std::cout << "Map file doesn't exist! Go to level editor to fix this." << std::endl;
	}

	texture_tileset = new Texture2D(mRenderer);
	texture_tileset->LoadFromFile("Images/tileset.png");
	for (int y = 0; y < (texture_tileset->GetHeight() / TILE_SIZE); y++) {
		for (int x = 0; x < (texture_tileset->GetWidth() / TILE_SIZE); x++) {
			tileset.push_back(new Rect2D(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		}
	}

	//Create tiles
	for (int x = 0; x < mapSizeX; x++) {
		for (int y = 0; y < mapSizeY; y++) {
			levelTiles.push_back(new LevelTile(Rect2D(x * TILE_SIZE, (y * TILE_SIZE) + (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE)), TILE_SIZE, TILE_SIZE), map[y * mapSizeX + x], IsTileCollidable(map[y * mapSizeX + x])));
		}
	}

	tempPlayer = new Entity(mRenderer, Vector2D(100, 100), "Images/Mario.png", 3.0f, 2.5f, 3.5f);
}

void GameScreen_CustomLevel::Render() {
	//Draw background
	SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(mRenderer, 159, 174, 255, 255);
	SDL_RenderFillRect(mRenderer, &backgroundRect);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	//Draw Tiles
	for (int i = 0; i < levelTiles.size(); i++) {
		if (levelTiles[i]->sprite != SPRITE_CLEAR) {
			SDL_Rect src = { tileset[levelTiles[i]->sprite]->x, tileset[levelTiles[i]->sprite]->y, tileset[levelTiles[i]->sprite]->w, tileset[levelTiles[i]->sprite]->h };
			SDL_Rect dest = { levelTiles[i]->rect.x, levelTiles[i]->rect.y, levelTiles[i]->rect.w, levelTiles[i]->rect.h };

			texture_tileset->Render(src, dest, SDL_FLIP_NONE);
		}
	}

	tempPlayer->Render();
}

void GameScreen_CustomLevel::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
		//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			tempPlayer->SetMoveLeft(true);
			tempPlayer->SetMoveRight(false);
			break;
		case SDLK_RIGHT:
			tempPlayer->SetMoveLeft(false);
			tempPlayer->SetMoveRight(true);
			break;
		}
		break;

		//Key Up Events
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			tempPlayer->SetMoveLeft(false);
			break;
		case SDLK_RIGHT:
			tempPlayer->SetMoveRight(false);
			break;
		}
		break;

	}

	tempPlayer->Update(deltaTime, e);
}

bool GameScreen_CustomLevel::ReadMapFromFile(const char* filePath) {
	std::ifstream inFile(filePath, std::ifstream::binary);
	if (!inFile.is_open()) {
		std::cout << "Failed to load map file" << std::endl;
		return false;
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

bool GameScreen_CustomLevel::IsTileCollidable(unsigned short sprite) {
	switch (sprite) {
	//Non-collidable sprites return false
	case SPRITE_CLEAR:
	case SPRITE_BUSH_LARGE_LEFT_SLOPE:
	case SPRITE_BUSH_LARGE_LEFT_SPOTS:
	case SPRITE_BUSH_LARGE_TOP:
	case SPRITE_BUSH_LARGE_FULL:
	case SPRITE_BUSH_LARGE_RIGHT_SLOPE:
	case SPRITE_BUSH_LARGE_RIGHT_SPOTS:
	case SPRITE_BUSH_SMALL_LEFT:
	case SPRITE_BUSH_SMALL_MIDDLE:
	case SPRITE_BUSH_SMALL_RIGHT:
	case SPRITE_CLOUD_TOP_LEFT:
	case SPRITE_CLOUD_TOP_MIDDLE:
	case SPRITE_CLOUD_TOP_RIGHT:
	case SPRITE_CLOUD_BOTTOM_LEFT:
	case SPRITE_CLOUD_BOTTOM_MIDDLE:
	case SPRITE_CLOUD_BOTTOM_RIGHT:
		return false;
		break;
	}

	return true;
}
