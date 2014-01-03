#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "AnimationFilm.h"
#include "..\Objects.h"

// lecture11 slide 6

class Animation {
		private:
				animid_t id;

		public:
				Animation(animid_t _id) : id(_id) {}
				virtual ~Animation(){}
				void Animate(AnimationFilm& film, const Point at);
				animid_t GetID() { return id; }
				virtual Animation* Clone (animid_t newId) const = 0;
};

#endif