#include "header_files/mario/NumbersHolder.h"

MovingAnimator* NumbersHolder::Numbers[N_MAX];

void NumbersHolder::Init() {
		Dim i = 0;
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("zero") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("zero"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Numbers[i++] = aMovAnimr;
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning(Numbers[0]);
}
