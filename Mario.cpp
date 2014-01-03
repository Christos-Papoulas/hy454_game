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

void Mario::MarioFinisWaiting(Animator*, void*){ 

		return ;
}

void Mario::MarioMovesLeft() {
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	MarioAnimator->GetSprite()->MoveLeft(1);
}

void Mario::MarioMovesUp() {
	MarioSJump->GetSprite()->MoveUp(2);
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
	marioState = Walking;
}

void Mario::MarioFinishWalking(Animator* anmtr, void* param) {
		SetDimensions(MarioWaiting, MarioAnimator);
		
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);

		marioState = Waiting;
		return ;
}

void Mario::MarioStandingJump() {
		SetDimensions(MarioSJump, MarioWaiting);

		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsRunning(MarioSJump);
		
		MarioMovesUp();
		
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);
		
		marioState = Jumping;
		return ;
}

void Mario::MarioFinishSjumping(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		marioState = Waiting;

		return ;
}


MovingAnimator* Mario::GetAnimator() {
	return MarioAnimator;
}

void Mario::SetDimensions(MovingAnimator* source, MovingAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingAnimator* dest) {
		SetDimensions(MarioAnimator, dest);
		SetDimensions(MarioWaiting, dest);
		SetDimensions(MarioSJump, dest);
}