#include "header_files\collision\Collision.h"

Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		Collision_map[x][y] = value;
}