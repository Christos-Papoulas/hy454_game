#include "header_files/mario/NumbersHolder.h"

MovingAnimator* NumbersHolder::Numbers[N_MAX];

void NumbersHolder::Init() {
		Dim i = 0;
		std::vector<std::string> names;
		char * name[N_MAX] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
		for(i=0; i < N_MAX; i++){
			names.push_back(name[i]);
			Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
			MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
							0, 0, 
							0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
							);
			MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
			Numbers[i] = aMovAnimr;
			aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
			AnimatorHolder::Register( aMovAnimr );				
			AnimatorHolder::MarkAsRunning(Numbers[0]);
		}
}
