#include "Collision.h"
#include "terrain.h"
#include <iostream>
#include "Mario.h"

Dim			Collision::Collision_map[MAX_HEIGHT][MAX_WIDTH];
bool Collision::IsGravityAddicted = true;

void Collision::SetValue(Dim x, Dim y, Dim value) { 
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		if (value == 1 || //edafos
				value == 34  || //toublo
				value == 299 || //swlinas
				value == 298 ||
				value == 265 ||
				value == 67  ||
				value == 364 ||
				value == 268 ||
				value == 69  ||
				value == 266)
			Collision_map[x][y] = 1;
		else if(value == 47)
			Collision_map[x][y] = value;
		else
			Collision_map[x][y] = 0;
}

void Collision::CheckGravity(Dim x_tile, Dim y_tile) {
 if(Mario::IsOnAir(y_tile,x_tile)){
				if(Mario::IsOnBrick())
						SetGravity(false);
				else
						SetGravity(true);
		}	else {
						SetGravity(false);
		}
}

clock_t wa = 0;
bool isFinishGame = false;
void Collision::MarioCollision(Dim y_tile, Dim x_tile) { //mario tyles
	Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
	Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
	Dim y = Mario::GetMarioCurrentSprite()->GetY();
	Dim mheight = Mario::GetMarioCurrentSprite()->GetFrameBox().GetHeight() >> 4;

	if(y == 222){
		Coins::RemoveLife();
		Sounds::Play("mario_death");
		Mario::MarioFinishDeath(0,0);
	}
	if(y > 240)
		Mario::GetMarioCurrentSprite()->SetY(100);

	if(Collision::GetValue(y_tile + i, x_tile + j + mheight - 1) == 47){
		Mario::SetOnDoor();
		if(!isFinishGame) {
			AnimatorHolder::MarkAsSuspended(Mario::GetAnimator());
			TerrainStartScreen::CreateWin();
			Sounds::Play("finish");
			Sounds::Pause("music");
			isFinishGame = true;
		}
		if(wa == 0) { 
			wa = clock();
			Mario::GetWalkingAnimator()->GetMovingAnimation()->SetDx(0);
			Mario::MarioFinishWalking(0, 0);
			AnimatorHolder::MarkAsSuspended(Mario::GetAnimator());
			Items::ThrowAFirework();
		}
		if( clock() >= wa + 3000 )
			if(MarioBrosMain::GameIsPlay())
				MarioBrosMain::SetGameOver();
	}

	//assert(j+x_tile+1 < MAX_HEIGHT);
	assert(i+y_tile < MAX_WIDTH);

	Animator* marioAnimator = Mario::GetAnimator();

	switch (Mario::GetState()){
		case Waiting:
				CheckGravity(x_tile, y_tile);
				break;
		case Walking:
				CheckGravity(x_tile, y_tile);
				if(!Mario::isUnderGround)
						break;
				if (!Mario::CanGoRight(y_tile, x_tile)){
					((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(0);
				}
				else{
					((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(4);
				}
				break;
		case backwalk:
				CheckGravity(x_tile, y_tile);
				if(!Mario::isUnderGround)
						break;
				if (!Mario::CanGoLeft(y_tile, x_tile)){
					((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(0);
				}
				break;
		case WalkAndJump:
				if (!Mario::CanGoRight(y_tile, x_tile)){
					int currIndex = ((MovingPathAnimator*) marioAnimator)->GetCurrIndex();
					((MovingPathAnimator*) marioAnimator)->GetAnimation()->SetOnPath(currIndex, 0);
				}
				if(!Mario::IsOnAir(y_tile, x_tile + 1) && ((MovingPathAnimator*) marioAnimator)->GetCurrIndex() > 1) {
						Mario::MarioFinishWjumping(0, 0);
				}
				break;
		case BackAndJump:
			if (!Mario::CanGoLeft(y_tile, x_tile)){
				int currIndex = ((MovingPathAnimator*) marioAnimator)->GetCurrIndex();
				((MovingPathAnimator*) marioAnimator)->GetAnimation()->SetOnPath(currIndex, 0);
			}
			if(!Mario::IsOnAir(y_tile, x_tile+1) && ((MovingPathAnimator*) marioAnimator)->GetCurrIndex() > 1) {
					Mario::MarioFinishBackJump(0, 0);
			}
			break;
	}
}

void Collision::CheckCollision() {
	Sprite* activeMario = Mario::GetMarioCurrentSprite();
	Dim x = activeMario->GetTileX();
	Dim y = activeMario->GetTileY();

	if(Mario::GetState() == Death) 
			return ;
	MarioCollision(x,y);
	Mario::SetDimensions(Mario::GetMarioCurrentSprite()->GetX(),Mario::GetMarioCurrentSprite()->GetY());

	if(Mario::isWalkingJump() || Mario::GetState() == BackAndJump) return ;

	if(Collision::GetGravity() == true)
			activeMario->Move(0,1);
}