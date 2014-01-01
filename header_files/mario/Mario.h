#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include <assert.h>


class Mario {
	private:
		static Mario* mario;
		static MovingAnimator* MarioAnimator;
		Mario(MovingAnimator* mario_animator);
		~Mario();

	public:
		static void Create(MovingAnimator* mario_animator);
		static void Destroy();
		void MarioMovesLeft();
		void MarioMovesRight();
};

#endif