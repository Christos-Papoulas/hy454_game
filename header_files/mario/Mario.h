#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../tiles/TilesBitmap.h"

#include <assert.h>

enum MarioState { 
		Walking = 0,
		Waiting,
		Jumping
};

class Mario {
	private:
		static Mario* mario;
		static MovingAnimator* MarioAnimator;
		static MovingAnimator* MarioWaiting;
		static MovingAnimator* MarioSJump;
		Mario(MovingAnimator* mario_animator);
		~Mario();

	public:
		static void CreateWalking(MovingAnimator* mario_animator);
		static void CreateWaiting(MovingAnimator* mario_animator);
		static void CreateSjumping(MovingAnimator* mario_animator); //waiting and jump
		static void Destroy();
		static void MarioMovesLeft();
		static void MarioMovesRight();
		static void MarioMovesUp();
		static void MarioFinishWalking(Animator*, void*);
		static void MarioStandingJump();
		static  MovingAnimator* GetAnimator();
};

#endif