#include "header_files\collision\Collision.h"
#include "terrain\terrain.h"
#include <iostream>
#include "..\header_files\mario\Mario.h"



Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1 || value == 34 || value == 298 || value == 265)
			Collision_map[x][y] = value;
		else
			Collision_map[x][y] = 0;
		if (value == 303)
			std::cout<< "(" << x << " " << y << ")";
}

bool Collision::MarioCollision(Dim y_tile, Dim x_tile) {
	Dim i,j;
	i = Terrain::GetTileLayer()->GetViewWindow().GetX();
	j = Terrain::GetTileLayer()->GetViewWindow().GetY();
	//std::cout<< "(" << j+x_tile << " " << i+y_tile << ")";
	if(Collision_map[j+x_tile+1][i+y_tile] == 1) {
		if (Collision_map[j+x_tile][i+y_tile+1] == 34) {	//touvlo
			//std::cout<< "(" << j+x_tile << " " << i+y_tile << ")";
			Mario::GetAnimator()->GetSprite()->MoveLeft(1);
		}
		else if (Collision_map[j+x_tile][i+y_tile+1] == 298) {	//swlhnas
			Mario::GetAnimator()->GetSprite()->MoveLeft(1);
		}
		else if(Collision_map[j+x_tile][i+y_tile+1] == 265) {	//swlhnas 2
			Mario::GetAnimator()->GetSprite()->MoveLeft(1);
		}
		return true;
	}
	
	return false;
}

void Collision::CheckGroundCollision() {
	MovingAnimator* lala = Mario::GetActiveMario();
	if(!Collision::MarioCollision(Mario::GetAnimator()->GetSprite()->GetTileX(),Mario::GetAnimator()->GetSprite()->GetTileY()))
			Mario::GetAnimator()->GetSprite()->Move(0,1);
}