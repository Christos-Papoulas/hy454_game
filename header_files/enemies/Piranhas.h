#ifndef _PIRANHAS_H_
#define _PIRANHAS_H_

#include "../animator/MovingAnimator.h"
#include "../animator/HiddenAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/FrameRangeAnimation.h"
#include "../Objects.h"
#include "../enemies/Enemies.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../collision/Collision.h"
#include "../items/Items.h"

#include <stdlib.h>
#include <list>

class Piranhas {
		static std::list<HiddenAnimator*> suspending;
		static std::list<HiddenAnimator*> running;
		static std::list<HiddenAnimator*> dead;

		static void KillMario();
		
		static void Move();
public:
		static void Create();

		static void Finish(Animator *a, void *f);

		static void ArtificialIntelligence();
			static void CreateIfAny();
		static void ViewWindowMove();
		static void Suspend();
		static void Kill();
		
};

#endif