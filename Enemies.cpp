#include "header_files/enemies/Enemies.h"

Index	Enemies::map[MAX_HEIGHT][MAX_WIDTH];
Dim Enemies::totalFrames = 0;
MarioInfo_t* Enemies::enemies = NULL;
Index**	Enemies::shortMap = NULL;
Index Enemies::countEnemies = 0;

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
}

void Enemies::Create() { 
		ReadMap();
}

void Enemies::MakeShortMap() {
		countEnemies = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j]) countEnemies++;

		shortMap = (Index**) malloc(sizeof(Index*)*countEnemies);
		for(Dim i = 0; i < countEnemies; i++)
				shortMap[i] = (Index*) malloc(sizeof(Index)*3);
		
		Dim en = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j]) {
								shortMap[en][X_INDEX] = i;
								shortMap[en][Y_INDEX] = j;
								shortMap[en++][ISACTIVE] = 0;
						}
}

void Enemies::SetEnemyAsActive(Dim x, Dim y) {
		for(Dim i = 0; i < countEnemies; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y) {
						shortMap[i][ISACTIVE] = 1; return ;
				}
				assert(0);
}

bool Enemies::IsEnemyActive(Dim x, Dim y) {
		for(Dim i = 0; i < countEnemies; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y)
						return shortMap[i][ISACTIVE] == 1;
		assert(0);
		return 0;
}

bool Enemies::CanGoLeft(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		if(x + i == 0) 
				return true;
		if(Collision::GetValue(x + i - 1, y + j) != 0)
				return false;
		return true;
}

bool Enemies::CanGoRight(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		
		if(Collision::GetValue(x + i + 1, y + j) != 0)
				return false;
		return true;
}

bool Enemies::IsOnBrick(Dim x, Dim y) {
		return Items::IsEnemyOnBrick("bricks", x, y) ||
				Items::IsEnemyOnBrick("questionbrick", x, y) ||
				Items::IsEnemyOnBrick("leftuppipe", x, y) ||
				Items::IsEnemyOnBrick("rightuppipe", x, y) ||
				Items::IsEnemyOnBrick("solidbrick", x, y) ||
				Items::IsEnemyOnBrick("questionfinish", x, y);
}

bool Enemies::IsOnAir(Dim x, Dim y, Dim width) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		Dim shift = (width>>4);
		Dim value = Collision::GetValue(x + i, y + j + 1 + shift);
		if(value == 0)
				return true;
		return false;
}

bool Enemies::IsMarioLeft(Dim x, Dim y) {
		Dim mi = Mario::GetMarioCurrentSprite()->GetX();
		Dim mj = Mario::GetMarioCurrentSprite()->GetY();

		Dim j = (y > mj) ? y - mj : mj - y;
		if(x > mi && x - mi < COLLISION_DETECT && j < COLLISION_DETECT)
				return true;
		return false;
}

bool Enemies::IsMarioRight(Dim x, Dim y) {
		Dim mi = Mario::GetMarioCurrentSprite()->GetX();
		Dim mj = Mario::GetMarioCurrentSprite()->GetY();

		Dim j = (y > mj) ? y - mj : mj - y;
		if(x < mi && mi - x < COLLISION_DETECT && j < COLLISION_DETECT)
				return true;
		return false;
}

bool Enemies::IsMarioLeftOrRight(Dim x, Dim y) { // x, y, is on screen
		Dim mi = Mario::GetMarioCurrentSprite()->GetX();
		Dim mj = Mario::GetMarioCurrentSprite()->GetY();

		Dim i = (x > mi) ? x - mi : mi - x;
		Dim j = (y > mj) ? y - mj : mj - y;

		if(i < COLLISION_DETECT && j < COLLISION_DETECT)
				return true;

		if(Mario::IsSuperMario()){
				Dim j = (y + 16 > mj) ? y - 16 - mj : mj - 16 - y;
				if(i < (COLLISION_DETECT  + 2) & j < COLLISION_DETECT)
						return true;
		}
		return false;
}

bool Enemies::IsMarioAbove(Dim x, Dim y) { //x, y, is tiles
		Dim mx = Mario::GetMarioCurrentSprite()->GetTileX();
		Dim my = Mario::GetMarioCurrentSprite()->GetTileY();

		if(x == mx && my + 1 == y)
				return true;
		return false;
}

void Enemies::Reactivate(Dim x) {
	Dim en = 0;
	for(Dim i = 0; i < MAX_HEIGHT; ++i)
		for(Dim j = 0; j < MAX_WIDTH; ++j)
			if(map[i][j]) {
					shortMap[en][X_INDEX] = i;
					shortMap[en][Y_INDEX] = j;
					shortMap[en++][ISACTIVE] = 0;
			}
	Goumbas::KillGoumbas();
	GreenKoopa::DeactivateAllKoopas();
	Piranhas::Deactivate();
}