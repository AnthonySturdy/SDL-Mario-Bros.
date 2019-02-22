#pragma once
#include "Constants.h"

class LevelMap {
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int w, unsigned int h);
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newVal);

private:
	int** mMap;
};