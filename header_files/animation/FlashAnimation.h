#ifndef _FLASHANIMATION_H_
#define _FLASHANIMATION_H_

#include "Animation.h"
#include "FrameRangeAnimation.h"

//lecture11 slide 16

class FlashAnimation : public Animation {
		frame_t			repetitions;
		delay_t			hideDelay;
		delay_t			showDelay;
public:
		frame_t			SetRepetitions(frame_t n) { repetitions = n; }
		frame_t			GetRepetitions() const { return repetitions; }
		void				SetHideDelay(delay_t d) { hideDelay = d; }
		delay_t			GetHideDelay() const { return hideDelay; }
		void				SetShowDelay(delay_t d) { showDelay = d; }
		delay_t			GetShowDelay() const { return showDelay; }

		Animation* Clone(animid_t newId) const {
				return new FlashAnimation(repetitions, hideDelay, showDelay, newId);
		}

		FlashAnimation( frame_t n, delay_t show, delay_t hide, animid_t id) :
				repetitions(n), hideDelay(hide), showDelay(show), Animation(id) {}

};

#endif