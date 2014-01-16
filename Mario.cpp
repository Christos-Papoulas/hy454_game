#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
MovingAnimator* Mario::MarioAnimator = NULL;
MovingAnimator* Mario::MarioWaiting = NULL;
MovingPathAnimator* Mario::MarioSJump = NULL;
MovingPathAnimator* Mario::MarioWJump = NULL;
MovingAnimator* Mario::MarioBWalk = NULL;
MovingPathAnimator* Mario::MarioDeath = NULL;


MarioState Mario::marioState = Walking;

Dim countScroll = 0;
static bool MoveViewWindow(Dim x) {
		if( x > 85) {
			(Terrain::GetTileLayer())->SetScrollviewWindow(countScroll);
			
			Goumbas::ViewWindowMove();
			GreenKoopa::ViewWindowMove();
			Items::ViewWindowMove();
			countScroll++;
			if(countScroll == 16) {
				(Terrain::GetTileLayer())-> ScrollHorizBy(1);
				(Terrain::GetTileLayer())->SetScrollviewWindow(0); 
				countScroll = 0;
			}
			return true;
	} 
	return false;
}

void Mario::MoveViewWin() {
		Sprite* m = Mario::GetMarioCurrentSprite();
		if(MoveViewWindow(m->GetX()))
				m->SetX(m->GetX() - 1);
}
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

void Mario::CreateDeath(MovingPathAnimator* mario_animator) {
		if(!MarioDeath)
				MarioDeath = mario_animator;
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
		case Death:
				return MarioDeath->GetSprite();
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
//						MoveViewWindow(MarioWaiting->GetSprite()->GetX());
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
				case Death:
						MarioDeath->SetLastTime(curr);

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
	if(MarioBWalk->GetSprite()->GetX() <= 3)
			MarioBWalk->GetMovingAnimation()->SetDx(0);
	else
			MarioBWalk->GetMovingAnimation()->SetDx(-3);
	ChangeState(backwalk);
}

void Mario::MarioMovesRight() {
	if(marioState == WalkAndJump)
			return ;
	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsSuspended(MarioBWalk);
	AnimatorHolder::MarkAsRunning(MarioAnimator);
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	Dim x = MarioAnimator->GetSprite()->GetX();
		
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
		if(marioState == Jumping)
				return ;
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
		if(marioState == WalkAndJump){
				return ;
		}

		SetDimensions(MarioWJump, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		
		AnimatorHolder::MarkAsRunning(MarioWJump);
		
		ChangeState(WalkAndJump);
		return ;
}

void Mario::MarioDeading() {
		if(marioState == Death) return ;
		SetDimensions(MarioDeath, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsSuspended(MarioWJump);
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioBWalk);

		AnimatorHolder::MarkAsRunning(MarioDeath);
		ChangeState(WalkAndJump);
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

void Mario::MarioFinishWjumping(Animator* , void* ) {
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

void Mario::MarioFinishDeath(Animator*, void*) {
		; //@todo finish the game
}

MovingAnimator* Mario::GetAnimator() {
	return MarioAnimator;
}

bool startScrolling = false;
void Mario::EnterPipe() {
		return;
}

Dim scrollX = 0;
#define PIPE_WINDOW 180
Dim Mario::PipeEnterScroll(Dim i) {
		return 0;
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

bool Mario::IsOnAir(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();;
		
		if(Collision::GetValue(x + i, y + j + 1) == 0)
				return true;
		return false;
}

bool Mario::CanGoLeft(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();;
		
		if(Collision::GetValue(x + i, y + j) != 0)
				return false;
		return true;
}

bool Mario::CanGoRight(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();;
		
		if(Collision::GetValue(x + i + 1, y + j) != 0)
				return false;
		return true;
}