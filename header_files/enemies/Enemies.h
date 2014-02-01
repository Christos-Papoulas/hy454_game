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
#include "../mario/Mario.h"
#include "Goumba.h"

#define ENEMIES_TYLES "data/enemies_1-1.txt"
#define ENEMIES_SPRITES "data/Enemies.info"

#define COLLISION_DETECT 10

#define X_INDEX 0
#define Y_INDEX 1
#define ISACTIVE 2

class Enemies {
		static Index	map[MAX_HEIGHT][MAX_WIDTH];
		static Index**	shortMap;
		static Dim totalFrames;
		static MarioInfo_t* enemies;
		static Index countEnemies;
		
		
		Enemies(){;}

		public:
				static void Create();
				static void SetOnMap(Index value, Dim x, Dim y) {
						assert(x < MAX_HEIGHT && y < MAX_WIDTH );
						map[x][y] = value;
				}
				static Index GetFromMap(Dim x, Dim y) {
						assert(x < MAX_HEIGHT+1 && y < MAX_WIDTH);
						return map[x][y];
				}
				static void ReadMap();
				static void MakeShortMap();
				static void SetEnemyAsActive(Dim x, Dim y);
				static bool IsEnemyActive(Dim x, Dim y);
				static bool CanGoLeft(Dim x, Dim y);
				
				static bool CanGoRight(Dim x, Dim y);
				
				static bool IsOnAir(Dim x, Dim y, Dim width);
				static bool IsOnBrick(Dim x, Dim y);

				static bool IsMarioLeftOrRight(Dim x, Dim y);
				static bool IsMarioAbove(Dim x, Dim y);
				static bool IsMarioLeft(Dim x, Dim y);
				static bool IsMarioRight(Dim x, Dim y);

				static void IncreaseEnemies(){ countEnemies++; }

				static void Reactivate(Dim x);
};

#endif