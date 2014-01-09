#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include "../Objects.h"
#include "../tiles/TileLayer.h" //only for the MAX_HEGHT and MAX_WIDTH of map
#define ENEMIES_TYLES "data/enemies_1-1.txt"

class Enemies {
		static Index	map[MAX_HEIGHT][MAX_WIDTH];
		Enemies(){;}
		public:
				static void CreateEnemies();
				static void SetOnMap(Index value, Dim x, Dim y) {
						assert(x < MAX_HEIGHT && y < MAX_WIDTH );
						map[x][y] = value;
				}
};

#endif