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
		std::cout << "Map file doesn't exist! Go to level editor and save to fix this." << std::endl;
	}

	texture_tileset = new Texture2D(mRenderer);
	texture_tileset->LoadFromFile("Images/tileset.png");
	for (int y = 0; y < (texture_tileset->GetHeight() / TILE_SIZE); y++) {
		for (int x = 0; x < (texture_tileset->GetWidth() / TILE_SIZE); x++) {
			tileset.push_back(new Rect2D(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		}
	}

	//Create tiles
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			levelTiles.push_back(new LevelTile(Rect2D(x * TILE_SIZE, (y * TILE_SIZE) + (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE)), TILE_SIZE, TILE_SIZE), map[y * mapSizeX + x], IsTileCollidable(map[y * mapSizeX + x])));
		}
	}

	//Create entities
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			CreateEntity(entityMap[y * mapSizeX + x], x * TILE_SIZE, (y * TILE_SIZE) + (SCREEN_HEIGHT - (mapSizeY * TILE_SIZE)));
		}
	}

}

void GameScreen_CustomLevel::Render() {
	//Draw background
	SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(mRenderer, 159, 174, 255, 255);
	SDL_RenderFillRect(mRenderer, &backgroundRect);
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	//Calculate camera offset
	int cameraOffsetX;
	if (playerEntity->GetPosition().x - halfScreen < 0) {
		cameraOffsetX = halfScreen - abs(playerEntity->GetPosition().x - halfScreen);
	} else if (playerEntity->GetPosition().x + halfScreen > mapSizeX * TILE_SIZE) {
		cameraOffsetX = halfScreen + (playerEntity->GetPosition().x + halfScreen) - (mapSizeX * TILE_SIZE);
	} else {
		cameraOffsetX = (SCREEN_WIDTH / 2);
	}

	//Draw Tiles
	for (int i = 0; i < levelTiles.size(); i++) {
		if (levelTiles[i]->sprite != SPRITE_CLEAR) {
			SDL_Rect src = { tileset[levelTiles[i]->sprite]->x, tileset[levelTiles[i]->sprite]->y, tileset[levelTiles[i]->sprite]->w, tileset[levelTiles[i]->sprite]->h };
			SDL_Rect dest = { levelTiles[i]->rect.x - playerEntity->GetPosition().x + cameraOffsetX, levelTiles[i]->rect.y, levelTiles[i]->rect.w, levelTiles[i]->rect.h };

			texture_tileset->Render(src, dest, SDL_FLIP_NONE);
		}
	}

	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == playerEntity) {
			entities[i]->Render(Vector2D(cameraOffsetX, 0));	//The Y position in this isn't used at the moment as there is only X scrolling
		} else {
			entities[i]->Render(Vector2D(entities[i]->GetPosition().x - playerEntity->GetPosition().x + cameraOffsetX, entities[i]->GetPosition().y));
		}
	}
}

void GameScreen_CustomLevel::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	//Key Down Events
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			if (!playerEntity->GetIsJumping())
				playerEntity->Jump(350);
			break;
		case SDLK_LEFT:
			playerEntity->SetMoveLeft(true);
			playerEntity->SetMoveRight(false);
			break;
		case SDLK_RIGHT:
			playerEntity->SetMoveLeft(false);
			playerEntity->SetMoveRight(true);
			break;
		}
		break;

	//Key Up Events
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			playerEntity->SetMoveLeft(false);
			break;
		case SDLK_RIGHT:
			playerEntity->SetMoveRight(false);
			break;
		}
		break;

	}

	//Refresh entities collision rects (before we check for collision)
	for (int j = 0; j < entities.size(); j++) {
		entities[j]->RefreshCollisionRect();
	}
	//Check entity tile collision
	for (int j = 0; j < entities.size(); j++) {
		for (int i = 0; i < levelTiles.size(); i++) {
			if (levelTiles[i]->isCollidable) {
				entities[j]->RectCollisionCheck(entities[j]->GetCollisionRect(), levelTiles[i]->rect);
			}
		}
	}
	//Check entity on entity collision
	for (int i = 0; i < entities.size(); i++) {
		for (int j = 0; j < entities.size(); j++) {
			//Don't check collision on itself
			if (entities[i] != entities[j]) {
				entities[i]->RectCollisionCheck(entities[i]->GetCollisionRect(), entities[j]->GetCollisionRect());
			}
		}
	}
	//Call entities Update()
	for (int j = 0; j < entities.size(); j++) {
		entities[j]->Update(deltaTime, e);
	}
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

void GameScreen_CustomLevel::CreateEntity(unsigned short sprite, int x, int y) {
	switch (sprite) {
	case SPRITE_ENTITY_MARIO_LEVEL_START: {
		Entity* e = new Entity(mRenderer, Vector2D(x, y), "Images/small_mario.png", 180.0f, 0.7f, 8.0f);
		entities.push_back(e);
		if (playerEntity == nullptr) {
			playerEntity = e;
		} else {
			//TODO: Add message to alert player there are 2 player objects in the scene
		}
	}
	break;

	case SPRITE_ENTITY_GOOMBA: {
		Entity* e = new Entity_Goomba(mRenderer, Vector2D(x, y), "Images/Goomba.png", 60, 999, 999);
		entities.push_back(e);
	}
	break;

	}
}
