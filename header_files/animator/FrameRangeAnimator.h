#ifndef _FRAME_RANGE_ANIMATOR_H_
#define _FRAME_RANGE_ANIMATOR_H_

#include "Animator.h"
#include "../animation/Sprites.h"
#include "../animation/FrameRangeAnimation.h"

// lecture11 slide29
class FrameRangeAnimator : public Animator {
	Sprite* sprite;
	FrameRangeAnimation* anim;
	frame_t currFrame;
	public:
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, FrameRangeAnimation* a, timestamp_t t) {
			sprite = s;
			anim = a;
			lastTime = t;
			state = ANIMATOR_RUNNING;
			sprite->SetFrame(currFrame = anim->GetStartFrame());
		}
		FrameRangeAnimator (void): sprite((Sprite*) 0), 
			anim((FrameRangeAnimation*) 0), currFrame(0xFF){}
		~FrameRangeAnimator(){}
};

#endif