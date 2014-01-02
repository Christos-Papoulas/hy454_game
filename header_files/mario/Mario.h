#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../tiles/TilesBitmap.h"

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
		static void MarioMovesLeft();
		static void MarioMovesRight();
};

#endif