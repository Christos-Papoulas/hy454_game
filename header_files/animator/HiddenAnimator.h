#ifndef _HIDDEN_ANIMATOR_H_
#define _HIDDEN_ANIMATOR_H_

#include "Animator.h"
#include "../animation/Sprites.h"
#include "../animation/MovingPathAnimation.h"
#include "../Objects.h"

class HiddenAnimator : public Animator {
	Sprite* sprite;
	MovingPathAnimation* anim;
	Dim show;
	int totalReplays;
	int currIndex;
	public:
		HiddenAnimator (void): sprite(0), anim(0), show(0), currIndex(0){}
		~HiddenAnimator(){}
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingPathAnimation* a, timestamp_t t) ;
		void SetLastTime(timestamp_t t) { lastTime = t; }
		void Display(Bitmap at);
		Sprite* GetSprite();
		MovingPathAnimation* GetMovingPathAnimation() { return anim; }
		void SetShow(Dim x) { show = x; }
		void ResetCurrIndex() { currIndex = 0; }
};

#endif