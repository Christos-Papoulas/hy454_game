#ifndef _MOVINGANIMATION_H_
#define _MOVINGANIMATION_H_

#include "Animation.h"

/*
 * lecture11 slide 8
 */
class MovingAnimation : public Animation {
		private:
				offset_t		dx, dy;
				delay_t			delay;
				bool				continuous;
		public:
				MovingAnimation(offset_t _dx, offset_t _dy, delay_t	_delay, bool c, animid_t _id) :
				dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id) 
				{}
				offset_t		GetDx() const						{ return dx; }
				void				SetDx(offset_t v)				{dx = v; }
				offset_t		GetDy() const						{ return dy; }
				void				SetDy(offset_t v)				{dy = v; }
				delay_t			GetDelay()							{ return delay; }
				void				SetDelay(delay_t v)			{ delay = v; }
				bool				GetContinuous()					{ return continuous; }
				void				SetContinuous(bool v)		{ continuous = v; }
				Animation*	Clone(animid_t newId) const {
						return new MovingAnimation(dx, dy, delay, continuous, newId);
				}
};

#endif