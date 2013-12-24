#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "AnimationFilm.h"
#include "..\Objects.h"

class Animation {
		public:
				void Animate(AnimationFilm& film, const Point at);
};

#endif