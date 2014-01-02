#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
MovingAnimator* Mario::MarioAnimator = NULL;

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

void Mario::MarioMovesLeft() {
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	//if(MarioAnimator->GetSprite()->GetX() >= vw.GetX())
		MarioAnimator->GetSprite()->MoveLeft(1);
}

void Mario::MarioMovesRight() {
	Rect vw = (Terrain::GetTileLayer())->GetViewWindow();
	Dim x = MarioAnimator->GetSprite()->GetX();
	if( x > 85) {
			(Terrain::GetTileLayer())-> ScrollHorizBy(5);
			MarioAnimator->GetSprite()->SetX(0);
	} else {
			MarioAnimator->GetSprite()->Move(1,0);
			MarioAnimator->Progress(GetCurrTime());
	}
}
