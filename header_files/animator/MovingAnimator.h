#ifndef _MOVING_ANIMATOR_H_
#define _MOVING_ANIMATOR_H_

#include "Animator.h"
#include "../animation/Sprites.h"
#include "../animation/MovingAnimation.h"
// lecture11 slide27
typedef unsigned long timestamp_t;

class MovingAnimator : public Animator {
	Sprite* sprite;
	MovingAnimation* anim;
	public:
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingAnimation* a, timestamp_t t) {
			sprite = s;
			anim  = a;
			lastTime  = t;
			state  = ANIMATOR_RUNNING;
		}
		MovingAnimator (void): sprite((Sprite*) 0), anim((MovingAnimation*) 0){}
		~MovingAnimator(){}
};

#endif