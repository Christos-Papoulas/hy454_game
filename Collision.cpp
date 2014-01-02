#include "header_files\collision\Collision.h"
#include "terrain\terrain.h"
#include <iostream>
#include "..\header_files\mario\Mario.h"



Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1)
			Collision_map[x][y] = value;
		else
			Collision_map[x][y] = 0;
		//std::cout<< Collision_map[x][y] << " ";
}

bool Collision::MarioCollision(Dim y_tile, Dim x_tile) {
	Dim i,j;
	i = Terrain::GetTileLayer()->GetViewWindow().GetX();
	j = Terrain::GetTileLayer()->GetViewWindow().GetY();
	if(Collision_map[j+x_tile+1][i+y_tile] == 1)
		return true;
	return false;
}

void Collision::CheckGroundCollision() {
	if(!Collision::MarioCollision(Mario::GetAnimator()->GetSprite()->GetTileX(),Mario::GetAnimator()->GetSprite()->GetTileY()))
			Mario::GetAnimator()->GetSprite()->Move(0,1);
}