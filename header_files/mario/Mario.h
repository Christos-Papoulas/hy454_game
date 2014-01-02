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

class Mario {
	private:
		static Mario* mario;
		static MovingAnimator* MarioAnimator;
		static MovingAnimator* MarioWaiting;
		Mario(MovingAnimator* mario_animator);
		~Mario();

	public:
		static void Create(MovingAnimator* mario_animator);
		static void Destroy();
		static void MarioMovesLeft();
		static void MarioMovesRight();
		static void MarioFinishWalking(Animator*, void*);
		static  MovingAnimator* GetAnimator();
};

#endif