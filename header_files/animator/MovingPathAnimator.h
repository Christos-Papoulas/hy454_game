#ifndef _MOVING_PATH_ANIMATOR_H_
#define _MOVING_PATH_ANIMATOR_H_

#include "../Objects.h"
#include "Animator.h"
#include "../animation/MovingPathAnimation.h"
#include "../animation/Sprites.h"

#include <assert.h>

typedef void (*OnProcessCallback)(int );

class MovingPathAnimator : public Animator {
		Sprite *sprite;
		MovingPathAnimation *anim;
		int totalReplays;
		int currIndex;
		public:
				MovingPathAnimator();
				~MovingPathAnimator();

				MovingPathAnimation* GetAnimation();
				Sprite* GetSprite();

				void Progress (timestamp_t currTime);
				void Start (Sprite* s, MovingPathAnimation* a, timestamp_t t);
				void Display(Bitmap at);
				//int GetCurrIndex(){return currIndex;}
				void SetLastTime(timestamp_t t) { lastTime = t; }
};

#endif