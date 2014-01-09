#include "header_files/enemies/Enemies.h"

Index	Enemies::map[MAX_HEIGHT][MAX_WIDTH];

void Enemies::CreateEnemies() { 
		using namespace std;
		Enemies();
		ifstream read(ENEMIES_TYLES);
		FILE* fp = fopen(ENEMIES_TYLES, "r");
		assert(fp);
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j){
						Index tmp;
						read >> tmp;
						SetOnMap(tmp, i, j);
				}
}