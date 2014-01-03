#ifndef _ANIMATOR_HOLDER_H_
#define _ANIMATOR_HOLDER_H_

#include "Animator.h"
#include "../animation/MovingAnimation.h"
#include "./FrameRangeAnimator.h"
#include <vector>
#include <algorithm>    // std::for_each
#include "..\Objects.h"

// lecture11 slide34
class AnimatorHolder {
	static std::vector<Animator*> running, suspended;
	class ProgressFunctor : public std::unary_function<Animator*, void> {
		timestamp_t t;
		public: 
			void operator()(Animator* a) const { a->Progress(t); }
			ProgressFunctor (timestamp_t _t) : t(_t){}
	};
	public:
		static void Register (Animator* a);
		static void Cancel (Animator* a);
		static void MarkAsRunning (Animator* a);
		static void MarkAsSuspended (Animator* a);
		static void Progress (timestamp_t currTime);
		static void Display(Bitmap at);
};

#endif