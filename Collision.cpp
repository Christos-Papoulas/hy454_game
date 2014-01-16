#include "header_files\collision\Collision.h"
#include "header_files\terrain\terrain.h"
#include <iostream>
#include "header_files\mario\Mario.h"

Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1 || value == 34 || value == 299 || value == 298 || value == 265 || value == 266)
			Collision_map[x][y] = value;
		//else if(value == 2 )
			//Collision_map[x][y] = 1;
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
	Dim Scroll = Mario::GetCountScroll();
	assert(Scroll < 16);

	if (Collision_map[j + x_tile][i + y_tile] == 1){
		Mario::GetMarioCurrentSprite()->MoveUp(16);
	}

	if (Collision_map[j + x_tile + 1][i + y_tile] == 298 || Collision_map[j + x_tile + 1][i + y_tile] == 299 || Collision_map[j + x_tile][i+y_tile] == 265 || Collision_map[j + x_tile][i+y_tile] == 266){
		Mario::GetMarioCurrentSprite()->MoveUp(16);
	}

	if(Mario::GetState() == Jumping){
		
		return true;
	}

	if(Mario::GetState() == WalkAndJump){
		if (!Mario::CanGoRight(y_tile,x_tile)) {	//touvlo
			//Mario::MarioFinishWjumping(NULL,NULL);
			Mario::GetMarioCurrentSprite()->MoveUp(1);
		}
		if(Collision_map[j + x_tile + 1][i+y_tile] == 34 || Collision_map[j + x_tile][i+y_tile + 1] == 34)
			Mario::GetMarioCurrentSprite()->MoveUp(1);
			//Mario::MarioFinishWjumping(NULL,NULL);
		return true;
	}

	if(Mario::GetState() == Waiting){
		if(!Mario::IsOnAir(y_tile,x_tile))
			return true;
	}

	if(Mario::GetState() == Walking){
		if(!Mario::IsOnAir(y_tile,x_tile)) {		//an pataei katw
			if (!Mario::CanGoRight(y_tile,x_tile)) {	//touvlo
				Mario::GetMarioCurrentSprite()->MoveLeft(1 + Scroll);
			}
			return true;
		}
		if (!Mario::CanGoRight(y_tile,x_tile)) {	//touvlo
			Mario::GetMarioCurrentSprite()->MoveLeft(1);
			return true;
		}
		if(!Mario::IsOnAir(y_tile,x_tile))
			return true;
	}

	if(Mario::GetState() == backwalk){
		if(!Mario::IsOnAir(y_tile,x_tile)) {		//an pataei katw
			if (!Mario::CanGoLeft(y_tile,x_tile)) {	//touvlo
				Mario::GetMarioCurrentSprite()->Move(1,0);
			}
			return true;
		}
	}


	return false;
}

void Collision::CheckGroundCollision() {
	Sprite* activeMario = Mario::GetMarioCurrentSprite();
	Dim x = activeMario->GetTileX();
	Dim y = activeMario->GetTileY();
	if(Mario::GetState() == Death) return ;

	
	if(!Collision::MarioCollision(x,y)){
		activeMario->Move(0,1);
	}
	Mario::SetDimensions(Mario::GetMarioCurrentSprite()->GetX(),Mario::GetMarioCurrentSprite()->GetY());
}