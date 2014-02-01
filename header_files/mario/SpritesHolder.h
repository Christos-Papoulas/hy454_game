#ifndef _SPRITES_HOLDER_H_
#define _SPRITES_HOLDER_H_

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

namespace Initializer {
		extern void InitMario();

		extern void InitMarioWalking();
		extern void InitMarioWaiting();
		extern void InitMarioStandJump();
		extern void InitMarioWalkJumnp();
		extern void InitMarioBackWalk();
		extern void BackWalkJump();

		extern void InitMarioDeath();
		
		extern void InitSuperMario();
		extern void SuperWaiting();
		extern void SuperWalking();
		extern void SuperBackWalk();
		extern void SuperWalkJump();
		extern void SuperStandJump();
		extern void SuperBackWalkJump();
		extern void SuperDown();
};

class SpritesHolder {
		public:
				SpritesHolder();
				~SpritesHolder();
};

#endif