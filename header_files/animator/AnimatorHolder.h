#ifndef _ANIMATOR_HOLDER_H_
#define _ANIMATOR_HOLDER_H_

#include "Animator.h"
#include "../animation/MovingAnimation.h"
#include <list>
#include <algorithm>    // std::for_each
#include "..\Objects.h"

// lecture11 slide34
class AnimatorHolder {
	static std::list<Animator*> running, suspended;
	class ProgressFunctor : public std::unary_function<Animator*, void> {
		timestamp_t t;
		public: 
			void operator()(Animator* a) const { a->Progress(t); }
			ProgressFunctor (timestamp_t _t) : t(_t){}
	};
	public:
		static void Register (Animator* a) { suspended.push_back(a); }
		static void Cancel (Animator* a) { suspended.remove(a); }
		static void MarkAsRunning (Animator* a) { suspended.remove(a); running.push_back(a); }
		static void MarkAsSuspended (Animator* a) { running.remove(a); suspended.push_back(a); }
		static void Progress (timestamp_t currTime);
		static void Display(Bitmap at);
};

#endif