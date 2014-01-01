#ifndef _SPRITES_HOLDER_H_
#define _SPRITES_HOLDER_H_

#include "../animation/Sprites.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/MovingAnimation.h"
#include "../terrain/terrain.h"

#include <string>

namespace Initializer {
		extern void InitMario();
};

class SpritesHolder {
		public:
				SpritesHolder();
				~SpritesHolder();
};

#endif