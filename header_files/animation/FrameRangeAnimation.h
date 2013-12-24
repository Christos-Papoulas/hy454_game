#ifndef _FRAMEANIMATION_H_
#define _FRAMEANIMATION_H_

#include "MovingAnimation.h"

// lecture11 slide 10
typedef unsigned char frame_t;

class FrameRangeAnimation : public MovingAnimation {
		private:
				frame_t start, end;
		public:
				frame_t GetStartFrame() const { return start; }
				void		SetStartFrame(frame_t v) { start = v; }
				frame_t GetEndFrame() const { return end; }
				void		SetEndFrame(frame_t v) { end = v; }
				Animation* Clone (animid_t newId) const {
						return new FrameRangeAnimation(
								start, end, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId
						);
				}
				FrameRangeAnimation(
						frame_t s, frame_t e, 
						offset_t dx, offset_t dy, delay_t d, bool c, animid_t id
						) : start(s), end(e), MovingAnimation(dx, dy, d, c, id) {}

};

#endif