#ifndef _FLUSH_MARIO_HOLDER_H_
#define _FLUSH_MARIO_HOLDER_H_

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

namespace FlushMario{
		extern MovingAnimator* marioWalking;
		extern MovingAnimator* marioWaiting;
		extern MovingPathAnimator* MarioStandJump;
		extern MovingPathAnimator* MarioWalkJump;
		extern MovingPathAnimator* backWalkJump;
		extern MovingAnimator* marioBackWalk;

		extern void InitMario();

		extern void Walking();
		extern void Waiting();
		extern void StandJump();
		extern void WalkJumnp();
		extern void BackWalk();
		extern void BackWalkJump();

		
		extern void SuperWaiting();
		extern void SuperWalking();
		extern void SuperBackWalk();
		extern void SuperWalkJump();
		extern void SuperStandJump();
		extern void SuperBackWalkJump();
};

#endif