#ifndef _NUMBERS_HOLDER_H_
#define _NUMBERS_HOLDER_H_

#include "../animator/MovingAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animator/FrameRangeAnimator.h"
#include "../parsers/ParseMarioInfo.h"
#include<vector>

#define N_MAX 10

namespace NumbersHolder{ 
		extern MovingAnimator* Numbers[N_MAX];
		extern MovingAnimator* Time;
		extern MovingAnimator* Mario;
		extern MovingAnimator* World;
		extern MovingAnimator* Epi;
		extern MovingAnimator* Coin;
		extern MovingAnimator* time1,*time2,*time3;

		extern void Init();
		extern void InitTime();
		extern void InitMario();
		extern void InitWorld();
		extern void InitEpi();
		extern void InitCoin();
		extern void PrintNumberTime(Dim num);
};

#endif