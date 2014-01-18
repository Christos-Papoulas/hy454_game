#ifndef _MARIO_H_
#define _MARIO_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/MovingPathAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../tiles/TilesBitmap.h"
#include "../terrain/TerrainStartScreen.h"
#include "../enemies/Goumba.h"
#include "../enemies/GreenKoopaTroopa.h"

#include <assert.h>
#include < vector>

extern Dim countScroll;

enum MarioState { 
		Walking = 0,
		backwalk,
		Waiting,
		Jumping,
		WalkAndJump,
		BackAndJump,
		Death
};

class Mario {
	private:
		static Mario* mario;
		static MovingAnimator* MarioAnimator;
		static MovingAnimator* MarioWaiting;
		static MovingAnimator* MarioBWalk;
		static MovingPathAnimator* MarioSJump;
		static MovingPathAnimator* MarioWJump;
		static MovingPathAnimator* BackJump;
		static MovingPathAnimator* MarioDeath;
		
		static MarioState marioState;
		Mario(MovingAnimator* mario_animator);
		~Mario();
		static std::vector<PathEntry> paths;
		static bool isOnBrick;
	public:
		static void CreateWalking(MovingAnimator* mario_animator);
		static void CreateWaiting(MovingAnimator* mario_animator);
		static void CreateBackWalking(MovingAnimator* mario_animator);
		static void CreateSjumping(MovingPathAnimator* mario_animator); //waiting and jump
		static void CreateWjumping(MovingPathAnimator* mario_animator);
		static void CreateDeath(MovingPathAnimator* mario_animator);
		static void CreateBackAndJump(MovingPathAnimator* mario_animator);

		static Sprite* GetMarioCurrentSprite();
		static  Animator* GetAnimator();

		static bool isWalking() { return marioState == Walking; }
		static bool isStandingJumping() { return marioState == Jumping; }
		static bool isWalkingJump() { return marioState == WalkAndJump; }
		static bool isBackWalk() { return marioState == backwalk; }
		static void Destroy();
		
		static void MoveViewWin();
		static void MarioFinishWalking(Animator*, void*);
		static void MarioFinishBackWalk(Animator*, void*);
		static void MarioFinishSjumping(Animator*, void*);
		static void MarioFinisWaiting(Animator*, void*);
		static void MarioFinishWjumping(Animator*, void*);
		static void MarioFinishDeath(Animator*, void*);
		static void MarioFinishBackJump(Animator*, void*);
		static void MarioStandingJump();
		static void MarioWalkingJump();
		static void MarioMovesLeft();
		static void MarioMovesRight();
		static void BackWalkAndJump();
		static void MarioDeading();
		
		static void EnterPipe();
		static Dim PipeEnterScroll(Dim i);
		
		static MarioState GetState() { return marioState; }
		static void ChangeState(MarioState );
		//copy the dest x,y to the the source
		static void SetDimensions(MovingAnimator* source, MovingAnimator* dest);
		//copy the dest x,y to all other mario animations
		static void SetDimensions(MovingAnimator* dest);
		static void SetDimensions(MovingPathAnimator* source, MovingAnimator* dest);
		static void SetDimensions(MovingAnimator* source, MovingPathAnimator* dest);
		static void SetDimensions(MovingPathAnimator* source, MovingPathAnimator* dest);
		static void SetDimensions(Dim x, Dim y);
		static bool IsOnAir(Dim x, Dim y);
		static bool CanGoLeft(Dim x, Dim y);
		static bool CanGoRight(Dim x, Dim y);
		static bool IsOnPipe(Dim x, Dim y);

		static Dim GetCountScroll(){ return countScroll;}
		static MovingPathAnimator* GetStandJump() { return MarioSJump; }
		static bool IsOnBrick() { return isOnBrick; }
		static void SetOnBrick(bool x) { isOnBrick = x; }

};

#endif