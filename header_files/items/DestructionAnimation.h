#ifndef _DESTRUCTION_ANIMATION_H_
#define _DESTRUCTION_ANIMATION_H_

#include "../Objects.h"

#include "../animator/Animator.h"
#include "../animator/MovingPathAnimator.h"
#include "../animation/AnimationFilmHolder.h"

#include "../animation/MovingPathAnimation.h"
#include "../animation/Sprites.h"
#include "../animation/MovingAnimation.h"
#include "../parsers/ParseMarioInfo.h"


typedef std::vector<PathEntry> Path;

#define BRICK_NAME "brickbreak"

class Destruction : public Animator {
		Sprite *s1, *s2, *s3, *s4;
		Path p1, p2, p3, p4;
		MovingPathAnimation *anim1, *anim2, *anim3, *anim4;
		MovingPathAnimator* tor1,* tor2,* tor3,* tor4;
		Dim currIndex;
		public:
				Destruction(Dim x, Dim y);
				void Progress (timestamp_t currTime);
				void Display(Bitmap at);
				void SetCurrIndex(Dim _c) { currIndex = _c; }
				static void FinishDestroy(Animator* a, void* v);
				void Reset(Dim x, Dim y) {
						s1->SetX(x-8);s2->SetX(x-8);
						s3->SetX(x+16);s4->SetX(x+16);
						s1->SetY(y);s2->SetY(y+16);
						s3->SetY(y);s4->SetY(y+16);
				}

};

#endif