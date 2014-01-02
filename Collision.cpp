#include "header_files\collision\Collision.h"

Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1)
			Collision_map[x][y] = value;
		else
			Collision_map[x][y] = 0;
}

bool Collision::MarioCollision(Dim x_tile, Dim y_tile) {
	return false;
}