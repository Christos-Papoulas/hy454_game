#include "header_files/enemies/Enemies.h"

Index	Enemies::map[MAX_HEIGHT][MAX_WIDTH];
Dim Enemies::totalFrames = 0;
MarioInfo_t* Enemies::enemies = NULL;

void Enemies::ReadMap() {
		using namespace std;
		Enemies();
		ifstream read(ENEMIES_TYLES);

		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j){
						Index tmp;
						read >> tmp;
						SetOnMap(tmp, i, j);
				}
		read.close();
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j] != 0)
								std::cout << i << ", " << j << " = " << map[i][j] << std::endl;
}

void Enemies::Create() { 
		ReadMap();
		//ReadSprites();
		Goumbas::Create();
}

