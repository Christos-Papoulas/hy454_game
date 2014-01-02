#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
MovingAnimator* Mario::MarioAnimator = NULL;
MovingAnimator* Mario::MarioWaiting = NULL;

Mario::Mario(MovingAnimator* mario_animator){
	assert(mario_animator);
	MarioAnimator = mario_animator;
}

Mario::~Mario() {
		delete mario; mario = NULL;
}

void Mario::Create(MovingAnimator* mario_animator) {
		if(!mario)
				mario = new Mario(mario_animator);
}

void Mario::CreateWaiting(MovingAnimator* mario_animator) {
		if(!MarioWaiting)
				MarioWaiting = mario_animator;
}

void Mario::MarioMovesLeft() {
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	//if(MarioAnimator->GetSprite()->GetX() >= vw.GetX())
		MarioAnimator->GetSprite()->MoveLeft(1);
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
//		(MarioAnimator->GetSprite())->SetFilmAndReset(AnimationFilmHolder::GetFilm( std::string("mariowaiting")));
		return ;
}

MovingAnimator* Mario::GetAnimator() {
	return MarioAnimator;
}