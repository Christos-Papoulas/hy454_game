#include "header_files\collision\Collision.h"
#include "header_files\terrain\terrain.h"
#include <iostream>
#include "header_files\mario\Mario.h"



Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1 || value == 34 || value == 298 || value == 265)
			Collision_map[x][y] = value;
		else if(value == 2 )
			Collision_map[x][y] = 1;
		else
			Collision_map[x][y] = 0;
		if (value == 303)
			std::cout<< "(" << x << " " << y << ")";
}

bool Collision::MarioCollision(Dim y_tile, Dim x_tile) {
	Dim i,j;
	i = Terrain::GetTileLayer()->GetViewWindow().GetX();
	j = Terrain::GetTileLayer()->GetViewWindow().GetY();
	assert(j+x_tile+1 < MAX_HEIGHT);
	assert(i+y_tile < MAX_WIDTH);
	if(Collision_map[j + x_tile + 1][i+y_tile] == 1) {
		if (Collision_map[j + x_tile][i + y_tile + 1] != 0) {	//touvlo
			Mario::GetActiveMario()->GetSprite()->MoveLeft(1);
		}
		
		return true;
	}

	if(Collision_map[j+x_tile+1][i+y_tile] != 0) {
		if (Collision_map[j+x_tile][i+y_tile+1] != 0) {	//touvlo
			Mario::GetActiveMario()->GetSprite()->MoveLeft(1);
		}
		return true;
	}

	if(Collision_map[j+x_tile+1][i+y_tile] == 265) {
		return true;
	}

	if(Collision_map[j+x_tile+1][i+y_tile] == 266) {
		return true;
	}
	return false;
}

void Collision::CheckGroundCollision() {
	Sprite* activeMario = Mario::GetMarioCurrentSprite();
	if(activeMario == NULL) return ; // NULL when mario is jumping
	Dim x = activeMario->GetTileX();
	Dim y = activeMario->GetTileY();
	
	if(!Collision::MarioCollision(x,y)){
		activeMario->Move(0,1);
		Mario::SetDimensions(Mario::GetActiveMario());
	}
}