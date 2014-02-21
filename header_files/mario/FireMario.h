#ifndef _FIRE_MARIO_H_
#define _FIRE_MARIO_H_

#include "../mario/Mario.h"
#include "../animation/Sprites.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/MovingAnimation.h"
#include "../animation/MovingPathAnimation.h"
#include "../animation/FrameRangeAnimation.h"
#include "../animator/MovingAnimator.h"
#include "../animator/MovingPathAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animator/FrameRangeAnimator.h"
#include "../terrain/terrain.h"

#include <string>

namespace FireMario{
		extern MovingAnimator* marioWalking;
		extern MovingAnimator* marioWaiting;
		extern MovingPathAnimator* MarioStandJump;
		extern MovingPathAnimator* MarioWalkJump;
		extern MovingPathAnimator* backWalkJump;
		extern MovingAnimator* marioBackWalk;
		extern MovingAnimator* marioDown;
	
		extern void FireMario();

		extern void Walking();
		extern void Waiting();
		extern void StandJump();
		extern void WalkJump();
		extern void BackWalk();
		extern void BackWalkJump();	
		extern void Down();
};

#endif