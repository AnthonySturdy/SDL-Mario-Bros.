#include "LevelMap.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]) {
	//Allocate memory for level map
	mMap = new int*[MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		//For every map Y, create a new X array
		mMap[i] = new int[MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int y = 0; y < MAP_HEIGHT; y++) {
		for (unsigned int x = 0; x < MAP_WIDTH; x++) {
			mMap[y][x] = map[y][x];
		}
	}
}

LevelMap::~LevelMap() {
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		delete[] mMap[i];
	}
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int w, unsigned int h) {
	if (h < MAP_HEIGHT && w < MAP_WIDTH) {
		return mMap[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newVal) {
	mMap[row][column] = newVal;
}