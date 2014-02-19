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
		static std::map<std::string,std::list<MovingAnimator*>> suspending;
		static std::map<std::string,std::list<MovingAnimator*>> running;
		static std::map<std::string,std::list<MovingAnimator*>> suspendingdead;
		static std::map<std::string,std::list<MovingAnimator*>> walkingdead;

		static void Dead(const char* id);
		static void MoveKoopasInShells(const char* id);
		static Dim delay;

		static void KoopasKillMario(const char* id);
		static void CollicionWithKoopaInShells(const char* id, Dim kx, Dim ky) ;
public:
		static void Create(const char* id);
		static void ArtificialIntelligence();
		static void CreateGreenKoopaIfAny();
		static void MoveGreenKoopas(const char* id);
		static void ViewWindowMove(const char* id);
		static void CommitDestructions(const char* id);
		static void ComeOutFromShell(Animator* a, void* v);
		static void SetDelay(Dim _delay) { delay = _delay; }
		static void DeactivateAllKoopas(const char* id);
		static void DeactivateAllKoopas();
};

#endif