#ifndef _GREEN_KOOPA_TROOPA_H_
#define _GREEN_KOOPA_TROOPA_H_

#include <assert.h>
#include <list>

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/FrameRangeAnimation.h"
#include "../Objects.h"
#include "../enemies/Enemies.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"

class GreenKoopa {
		static std::list<MovingAnimator*> suspending;
		static std::list<MovingAnimator*> running;
public:
		static void Create();
		static void ArtificialIntelligence();
		static void CreateGreenKoopaIfAny();
		static void MoveGreenKoopas();
		static void ViewWindowMove();
};

#endif