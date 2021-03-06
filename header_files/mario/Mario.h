#ifndef _MARIO_H_
#define _MARIO_H_

#include "MovingAnimator.h"
#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "AnimatorHolder.h"
#include "AnimationFilmHolder.h"
#include "terrain.h"
#include "TileLayer.h"
#include "TilesBitmap.h"
#include "TerrainStartScreen.h"
#include "Goumba.h"
#include "Piranhas.h"
#include "GreenKoopaTroopa.h"
#include "FlushMarioHolder.h"
#include "FireMario.h"
#include "SpritesHolder.h"
#include "Coins.h"
#include "Score.h"
#include "Sounds.h"
#include "MarioBrosMain.h"

#include <assert.h>
#include <vector>
#include <time.h>

extern ALLEGRO_KEYBOARD_STATE keyboardState;
extern Dim countScroll;

#define RUNNING_DELAY		100
#define TIME_FLASH_MARIO 5000

enum MarioState { 
		Walking = 0,
		backwalk,
		Waiting,
		Jumping,
		WalkAndJump,
		BackAndJump,
		Death
};

enum MarioLevel {
		MarioSmall = 0,
		Super_Mario,
		InvincibleMario,
		InvincibleSuper,
		Fire
};

class Mario {
	private:
		static Mario* mario;
		static Mario* super;
		static MovingAnimator* MarioAnimator;
		static MovingAnimator* MarioWaiting;
		static MovingAnimator* MarioBWalk;
		static MovingPathAnimator* MarioSJump;
		static MovingPathAnimator* MarioWJump;
		static MovingPathAnimator* BackJump;
		static MovingPathAnimator* MarioDeath;
		static MovingAnimator* Down;

		static MarioState marioState;
		static MarioLevel marioLevel;
		static bool justReturn2Small;
		static timestamp_t timeReturn2Small;
		static timestamp_t timeIsInvincible;
		static timestamp_t startBeInvincible;

		static std::vector<PathEntry> paths;
		static std::vector<PathEntry> backpaths;
		static bool isOnBrick;
		static void KeepInsideViewWin();
		friend void ChangeLevel(Animator* prev);
		static bool isRunningNow;
		friend class Piranhas;

		static void SetTimeReturn2Small(timestamp_t _t) { timeReturn2Small = _t; }
		static timestamp_t GetTimeReturn2Small() { return timeReturn2Small; }
		Mario(MovingAnimator* mario_animator);
		~Mario();
		
		static void StartBeInvincible(timestamp_t t) { startBeInvincible = t; }
		static timestamp_t GetTimeBeInvincible() { return startBeInvincible; }
		static void Return2Normal();

		static void EnterPipe();
		friend bool MoveViewWindow(Dim x);
		static bool isOnDoor;
	public:
		static MovingAnimator* GetWalkingAnimator() { return MarioAnimator; }
		static bool IsOnDoor() { return isOnDoor; }
		static void SetOnDoor() { isOnDoor = true; }
		static void SuperMario();
		static void FlashMario();
		static void CreateWalking(MovingAnimator* mario_animator);

		static void CreateWaiting(MovingAnimator* mario_animator);
		static void CreateBackWalking(MovingAnimator* mario_animator);
		static void CreateSjumping(MovingPathAnimator* mario_animator); //waiting and jump
		static void CreateWjumping(MovingPathAnimator* mario_animator);
		static void CreateDeath(MovingPathAnimator* mario_animator);
		static void CreateBackAndJump(MovingPathAnimator* mario_animator);
		static void CreateDown(MovingAnimator* _m);

		static Sprite* GetMarioCurrentSprite();
		static  Animator* GetAnimator();

		static bool isWalking() { return marioState == Walking; }
		static bool isStandingJumping() { return marioState == Jumping; }
		static bool isWalkingJump() { return marioState == WalkAndJump; }
		static bool isBackJumping() { return marioState == BackAndJump; }
		static bool isBackWalk() { return marioState == backwalk; }
		static bool isRunning() {return isRunningNow; }
		static bool isDead() { return marioState == Death; }
		static void Destroy();
		
		static void MoveViewWin();
		static void MarioFinishWalking(Animator*, void*);
		static void MarioFinishBackWalk(Animator*, void*);
		static void MarioFinishSjumping(Animator*, void*);
		static void MarioFinisWaiting(Animator*, void*);
		static void MarioFinishWjumping(Animator*, void*);
		static void MarioFinishDeath(Animator*a, void*v);
		static void MarioFinishBackJump(Animator*, void*);
		static void FinishDown(Animator*, void*);
		static void MarioStandingJump();
		static void MarioWalkingJump();
		static void MarioMovesLeft();
		static void MarioMovesRight();
		static void BackWalkAndJump();
		static void MovesDown();
		static void MarioDeading();
		static void Run();
		static void isNotRunning();
		
		static void GetOutFromPipe();
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

		//functions for marioLevel
		static void SetMarioAsInvincible();
		static bool IsMarioSmall();
		static bool IsInvincible();
		static void SetSuperAsInvincible();
		static bool IsSuperMario();
		static bool IsInvincibleSuper() { return marioLevel == InvincibleSuper; }
		static bool IsInvincibleSmall() { return marioLevel == InvincibleMario; }
		static bool IsMikio() {return marioLevel == MarioSmall || marioLevel == InvincibleMario;}

		static bool isUnderGround;
		static void Hited();
		static Dim checkpoints[3];
		static void RestoreCheckpoint(Dim x);

		static void FlushAnimation();
		static bool IsJustReturn2Small() { return justReturn2Small; }

		static void SetTimeInvincible(timestamp_t t){ timeIsInvincible = t; }
		static timestamp_t GetTime2BeInvincible() {return timeIsInvincible; }
		static void CountTimeInvincibleMario();

		static void SetAsFire();
		static bool isFire() { return marioLevel == Fire; }
};

#endif