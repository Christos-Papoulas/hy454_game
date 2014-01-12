#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
MovingAnimator* Mario::MarioAnimator = NULL;
MovingAnimator* Mario::MarioWaiting = NULL;
MovingPathAnimator* Mario::MarioSJump = NULL;
MovingPathAnimator* Mario::MarioWJump = NULL;
MovingAnimator* Mario::MarioBWalk = NULL;

MarioState Mario::marioState = Walking;

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

void Mario::CreateBackWalking(MovingAnimator* mario_animator) {
		if(!MarioBWalk)
				MarioBWalk = mario_animator;
}

void Mario::CreateSjumping(MovingPathAnimator* mario_animator) {
		if(!MarioSJump)
				MarioSJump = mario_animator;
} 

void Mario::CreateWjumping(MovingPathAnimator* mario_animator) {
		if(!MarioWJump)
				MarioWJump = mario_animator;
}

MovingAnimator* Mario::GetActiveMario() {
		switch (marioState) {
		case Waiting:
				return MarioWaiting;
		case Walking:
				return MarioAnimator;
		case backwalk:
				return NULL;
		case Jumping:
				return NULL;
		case WalkAndJump:
				return NULL;
		default: 
				assert(0);
		}
		return NULL;
}

Sprite* Mario::GetMarioCurrentSprite() {
		switch (marioState) {
		case Waiting:
				return MarioWaiting->GetSprite();
		case Walking:
				return MarioAnimator->GetSprite();
		case backwalk:
				return MarioBWalk->GetSprite();
		case Jumping:
				return MarioSJump->GetSprite();
		case WalkAndJump:
				return MarioWJump->GetSprite();
		default: 
				assert(0);
		}
		return NULL;
}

void Mario::ChangeState(MarioState nextState) {
		if(marioState == nextState)
				return ;
		unsigned int curr = CurrTime();
		switch (nextState) {
		case Waiting:
				MarioWaiting->SetLastTime(curr);
				break;
		case Walking:
				MarioAnimator->SetLastTime(curr);
				break;
		case backwalk:
				MarioBWalk->SetLastTime(curr);
				break;
		case Jumping:
				MarioSJump->SetLastTime(curr);
				break;
		case WalkAndJump:
				MarioWJump->SetLastTime(curr);
				break;
		default: 
				assert(0);
		}
		marioState = nextState;
		return ;
}

void Mario::MarioFinisWaiting(Animator*, void*){ 
		SetDimensions(MarioBWalk, MarioAnimator);
		return ;
}

void Mario::MarioMovesLeft() {
	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsSuspended(MarioAnimator);
	AnimatorHolder::MarkAsRunning(MarioBWalk);
	
	ChangeState(backwalk);
	//Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	//MarioAnimator->GetSprite()->MoveLeft(1);
}

Dim countScroll = 0;
void Mario::MarioMovesRight() {
	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsSuspended(MarioBWalk);
	AnimatorHolder::MarkAsRunning(MarioAnimator);
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	Dim x = MarioAnimator->GetSprite()->GetX();
	
	if( x > 85) {
			//(Terrain::GetTileLayer())-> ScrollHorizBy(1); 
			//MarioAnimator->GetSprite()->SetX(16*5);
			(Terrain::GetTileLayer())->SetScrollviewWindow(countScroll);
			MarioAnimator->GetSprite()->SetX(MarioAnimator->GetSprite()->GetX() - 1);
			Goumbas::ViewWindowMove();
			GreenKoopa::ViewWindowMove();
			countScroll++;
			if(countScroll == 16) {
				(Terrain::GetTileLayer())-> ScrollHorizBy(1);
				//MarioAnimator->GetSprite()->SetX(16*5);
				(Terrain::GetTileLayer())->SetScrollviewWindow(0); 
				countScroll = 0;
			}
			
	}  
			
	
	ChangeState(Walking);
}

void Mario::MarioFinishWalking(Animator* anmtr, void* param) {
		SetDimensions(MarioWaiting, MarioAnimator);
		
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);

		ChangeState(Waiting);
		return ;
}

void Mario::MarioStandingJump() {
		SetDimensions(MarioSJump, MarioWaiting);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsRunning(MarioSJump);
		
		//MarioMovesUp();
		
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);
		
		ChangeState(Jumping);
		return ;
}

void Mario::MarioWalkingJump() {
		SetDimensions(MarioWJump, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsRunning(MarioWJump);
		
		ChangeState(WalkAndJump);
		return ;
}

void Mario::MarioFinishBackWalk(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioBWalk);
		SetDimensions(MarioAnimator, MarioBWalk);
		SetDimensions(MarioSJump, MarioBWalk);
		SetDimensions(MarioWJump, MarioBWalk);

		AnimatorHolder::MarkAsSuspended(MarioBWalk);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		ChangeState(Waiting);

		return ;
}

void Mario::MarioFinishSjumping(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);
		SetDimensions(MarioBWalk, MarioSJump);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		ChangeState(Waiting);

		return ;
}

void Mario::MarioFinishWjumping(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioWJump);
		SetDimensions(MarioAnimator, MarioWJump);
		SetDimensions(MarioSJump, MarioWJump);
		SetDimensions(MarioBWalk, MarioWJump);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioWJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		ChangeState(Waiting);

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
		SetDimensions(MarioWJump, dest);
}

void Mario::SetDimensions(Dim x, Dim y) {
		MarioAnimator->GetSprite()->SetX(x);
		MarioAnimator->GetSprite()->SetY(y);

		MarioBWalk->GetSprite()->SetX(x);
		MarioBWalk->GetSprite()->SetY(y);

		MarioWaiting->GetSprite()->SetX(x);
		MarioWaiting->GetSprite()->SetY(y);

		MarioSJump->GetSprite()->SetX(x);
		MarioSJump->GetSprite()->SetY(y);

		MarioWJump->GetSprite()->SetX(x);
		MarioWJump->GetSprite()->SetY(y);
}

void Mario::SetDimensions(MovingPathAnimator* source, MovingAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingAnimator* source, MovingPathAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingPathAnimator* source, MovingPathAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
}