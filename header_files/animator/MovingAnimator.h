#ifndef _MOVING_ANIMATOR_H_
#define _MOVING_ANIMATOR_H_

#include "Animator.h"
#include "../animation/Sprites.h"
#include "../animation/MovingAnimation.h"


// lecture11 slide27
class MovingAnimator : public Animator {
	Sprite* sprite;
	MovingAnimation* anim;
	
	public:
		MovingAnimator (void): sprite((Sprite*) 0), anim((MovingAnimation*) 0){}
		~MovingAnimator(){}
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingAnimation* a, timestamp_t t) {
			sprite = s;
			anim  = a;
			lastTime  = t;
			state  = ANIMATOR_RUNNING;
		}
		void SetLastTime(timestamp_t t) { lastTime = t; }
		void Display(Bitmap at);
		Sprite* GetSprite();
		MovingAnimation* GetMovingAnimation() { return anim; }
};

#endif