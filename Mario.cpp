#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
MovingAnimator* Mario::MarioAnimator = NULL;
MovingAnimator* Mario::MarioWaiting = NULL;
MovingAnimator* Mario::MarioSJump = NULL;
MarioState marioState = Waiting;

Mario::Mario(MovingAnimator* mario_animator){
	assert(mario_animator);
	MarioAnimator = mario_animator;
}

Mario::~Mario() {
		delete mario; mario = NULL;
}

void Mario::CreateWalking(MovingAnimator* mario_animator) {
		if(!mario)
				mario = new Mario(mario_animator);
}

void Mario::CreateWaiting(MovingAnimator* mario_animator) {
		if(!MarioWaiting)
				MarioWaiting = mario_animator;
}

void Mario::CreateSjumping(MovingAnimator* mario_animator) {
		if(!MarioSJump)
				MarioSJump = mario_animator;
} 

MovingAnimator* Mario::GetActiveMario() {
		switch (marioState) {
		case Waiting:
				return MarioWaiting;
		case Walking:
				return MarioAnimator;
		case Jumping:
				return MarioSJump;
		default:
				assert(0);
		}
		return NULL;
}

void Mario::MarioMovesLeft() {
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	//if(MarioAnimator->GetSprite()->GetX() >= vw.GetX())
		MarioAnimator->GetSprite()->MoveLeft(1);
}

void Mario::MarioMovesUp() {
	MarioSJump->GetSprite()->MoveUp(1);
}

void Mario::MarioMovesRight() {
	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsRunning(MarioAnimator);
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	Dim x = MarioAnimator->GetSprite()->GetX();
	if( x > 85) {
			(Terrain::GetTileLayer())-> ScrollHorizBy(5);
			MarioAnimator->GetSprite()->SetX(16);
	} else {
			MarioAnimator->GetSprite()->Move(1,0);
			MarioAnimator->Progress(GetCurrTime());
	}
}

void Mario::MarioFinishWalking(Animator* anmtr, void* param) {
		MarioWaiting->GetSprite()->SetX(MarioAnimator->GetSprite()->GetX());
		MarioWaiting->GetSprite()->SetY(MarioAnimator->GetSprite()->GetY());

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		return ;
}

void Mario::MarioStandingJump() {
		MarioSJump->GetSprite()->SetX(MarioWaiting->GetSprite()->GetX());
		MarioSJump->GetSprite()->SetY(MarioWaiting->GetSprite()->GetY());

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		MarioMovesUp();
		
		MarioWaiting->GetSprite()->SetX(MarioSJump->GetSprite()->GetX());
		MarioWaiting->GetSprite()->SetY(MarioSJump->GetSprite()->GetY());
		return ;
}

void Mario::MarioFinishSjumping(Animator*, void*) {
		MarioWaiting->GetSprite()->SetX(MarioSJump->GetSprite()->GetX());
		MarioWaiting->GetSprite()->SetY(MarioSJump->GetSprite()->GetY());

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		return ;
}


MovingAnimator* Mario::GetAnimator() {
	return MarioAnimator;
}
