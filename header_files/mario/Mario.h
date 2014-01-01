#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include <assert.h>


class Mario {
	private:
		static Mario* mario;
		

	public:
		static void Create(MovingAnimator* mario_animator);
		Mario(MovingAnimator* mario_animator);
		~Mario();
		void MarioMovesLeft();
		void MarioMovesRight();
}

#endif