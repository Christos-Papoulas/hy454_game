#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <sstream>

#include "../parsers/ParseMarioInfo.h"
#include "../Objects.h"
#include "../tiles/TileLayer.h" //only for the MAX_HEGHT and MAX_WIDTH of map
#include "Goumba.h"

#define ENEMIES_TYLES "data/enemies_1-1.txt"
#define ENEMIES_SPRITES "data/Enemies.info"

class Enemies {
		static Index	map[MAX_HEIGHT][MAX_WIDTH];
		static Dim totalFrames;
		static MarioInfo_t* enemies;
		Enemies(){;}
		public:
				static void Create();
				static void SetOnMap(Index value, Dim x, Dim y) {
						assert(x < MAX_HEIGHT && y < MAX_WIDTH );
						map[x][y] = value;
				}
				static Index GetFromMap(Dim x, Dim y) {
						assert(x < MAX_HEIGHT && y < MAX_WIDTH);
						return map[x][y];
				}
				static void ReadMap();
};

#endif