#ifndef _GOUMBA_H_
#define _GOUMBA_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/FrameRangeAnimation.h"
#include "../Objects.h"
#include "../enemies/Enemies.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../collision/Collision.h"

#include <stdlib.h>
#include <list>

class Goumbas {
		static std::list<MovingAnimator*> goumbaSuspending;
		static std::list<MovingAnimator*> running;
		static std::list<MovingAnimator*> dead;
public:
		static void Create();
		static void Dead();

		static void FinishWalking(Animator*, void*);

		static void ArtificialIntelligence();
		static void CreateGoumbaifAny();
		static void MoveGoumbas();
		static void ViewWindowMove();
		static void GoumbasKillMario();
};

#endif