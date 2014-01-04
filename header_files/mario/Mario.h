#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/MovingPathAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../tiles/TilesBitmap.h"
#include "../terrain/TerrainStartScreen.h"

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
		static MovingPathAnimator* MarioSJump;
		Mario(MovingAnimator* mario_animator);
		~Mario();

	public:
		static void CreateWalking(MovingAnimator* mario_animator);
		static void CreateWaiting(MovingAnimator* mario_animator);
		static void CreateSjumping(MovingPathAnimator* mario_animator); //waiting and jump
		static MovingAnimator* GetActiveMario();
		static void Destroy();
		static void MarioMovesLeft();
		static void MarioMovesRight();
		static void MarioMovesUp();
		static void MarioFinishWalking(Animator*, void*);
		static void MarioFinishSjumping(Animator*, void*);
		static void MarioFinisWaiting(Animator*, void*);
		static void MarioStandingJump();
		static  MovingAnimator* GetAnimator();
		//copy the dest x,y to the the source
		static void SetDimensions(MovingAnimator* source, MovingAnimator* dest);
		//copy the dest x,y to all other mario animations
		static void SetDimensions(MovingAnimator* dest);
		static void SetDimensions(MovingPathAnimator* source, MovingAnimator* dest);
		static void SetDimensions(MovingAnimator* source, MovingPathAnimator* dest);
};

#endif