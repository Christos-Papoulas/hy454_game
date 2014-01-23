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
		//extern MovingAnimator* Time;
		//extern MovingAnimator* Mario;

		extern void Init();
		//extern void InitTime();
};

#endif