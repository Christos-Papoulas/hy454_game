#include "header_files/enemies/Enemies.h"

Index	Enemies::map[MAX_HEIGHT][MAX_WIDTH];

void Enemies::CreateEnemies() { 
		Enemies();
		FILE* fp = fopen(ENEMIES_TYLES, "r");
		assert(fp);
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j){
						Index tmp;
						fscanf(fp, "%u", &tmp);
						SetOnMap(tmp, i, j);
				}
}