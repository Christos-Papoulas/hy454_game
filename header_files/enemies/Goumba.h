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
#include "../items/Items.h"

#include <stdlib.h>
#include <list>

class Goumbas {
		static std::list<MovingAnimator*> goumbaSuspending;
		static std::list<MovingAnimator*> running;
		static std::list<MovingAnimator*> dead;

		static void GoumbasKillMario();
		static void CreateGoumbaifAny();
		static void MoveGoumbas();
		static Dim delay;
public:
		static void Create();
		static void Dead();
		static void BadDeath(Dim x, Dim y);

		static void Finish(Animator *a, void *f);

		static void ArtificialIntelligence();
			
		static void ViewWindowMove();
		static void SuspendGoumbas();
		static void KillGoumbas();
		
		static void SetDelay(Dim _delay) { delay = _delay; }

		static void CollicionWithKoopaInShells(Dim kx, Dim ky);
		static bool FireCollision(Dim fx, Dim fy);
};

#endif