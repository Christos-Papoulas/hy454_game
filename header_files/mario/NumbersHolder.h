#ifndef _NUMBERS_HOLDER_H_
#define _NUMBERS_HOLDER_H_

#include "../animator/MovingAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animator/FrameRangeAnimator.h"
#include "../parsers/ParseMarioInfo.h"
#include <map>
#include <list>
#include <vector>

#define N_MAX 10

namespace NumbersHolder{
		extern std::map<Dim, std::list<MovingAnimator*> > suspending;
		extern std::map<Dim, std::list<MovingAnimator*> > running;

		extern MovingAnimator* Time;
		extern MovingAnimator* Mario;
		extern MovingAnimator* World;
		extern MovingAnimator* Epi;
		extern MovingAnimator* Coin;
		extern MovingAnimator* time1,*time2,*time3;
		extern Dim t1,t2,t3;
		extern MovingAnimator* coin1,*coin2;
		extern Dim c1,c2;
		extern MovingAnimator* score1,*score2,*score3,*score4,*score5,*score6;
		extern Dim sc1,sc2,sc3,sc4,sc5,sc6;

		extern void Init();
		extern void CreateNumber(Dim i);
		extern void DisplayNumber(Dim number, Dim x);
		extern void SuspendNumbers(Dim number, MovingAnimator* g);
		extern void InitTime();
		extern void InitMario();
		extern void InitWorld();
		extern void InitEpi();
		extern void InitCoin();
		extern void PrintNumberTime(Dim num);
		extern void PrintNumberCoins(Dim num);
		extern void PrintScore(Dim num);
};

#endif