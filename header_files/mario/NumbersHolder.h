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

		extern void Init();
		extern void CreateNumber(Dim i);
		extern void DisplayNumber(Dim number, Dim x);
		extern void SuspendNumbers();
		extern void InitTime();
		extern void InitMario();
		extern void InitWorld();
		extern void InitEpi();
		extern void InitCoin();
		extern void PrintNumberTime(Dim num);
};

#endif