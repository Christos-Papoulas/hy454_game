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
	MarioAnimator->GetSprite()->MoveLeft(1);
}

void Mario::MarioMovesRight() {
	MarioAnimator->GetSprite()->Move(1,0);
}