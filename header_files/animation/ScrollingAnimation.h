#ifndef _SCROLLING_ANIMATION_H_
#define _SCROLLING_ANIMATION_H_

#include "Animation.h"
#include <list>

//lecture11 slide18

struct ScrollEntry {
		HorizScroll h;
		VertScroll v;
		delay_t delay;
};

class ScrollAnimation : public Animation {
		std::list<ScrollEntry> scroll;
		public:
				const std::list<ScrollEntry>& GetScroll (void) const { return scroll; }
				void SetScroll (const std::list<ScrollEntry>& p) { scroll.clear(); scroll = p; }
				Animation* Clone (animid_t newId) const {
						return new ScrollAnimation(scroll, newId); 
				}

				ScrollAnimation (const std::list<ScrollEntry>& _scroll, animid_t id) :
				scroll(_scroll), Animation(id){}
};

#endif