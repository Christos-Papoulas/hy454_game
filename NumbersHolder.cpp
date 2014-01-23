#include "header_files/mario/NumbersHolder.h"

MovingAnimator* NumbersHolder::Numbers[N_MAX];
MovingAnimator* NumbersHolder::Time;
MovingAnimator* NumbersHolder::Mario;
MovingAnimator* NumbersHolder::World;
MovingAnimator* NumbersHolder::Epi;

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

void NumbersHolder::InitTime() {
	Sprite *sprite = new Sprite(210, 10, AnimationFilmHolder::GetFilm( std::string("time") ));
	MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
					0, 0, 
					0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("time"))
					);
	MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
	Time = aMovAnimr;
	aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
	AnimatorHolder::Register( aMovAnimr );				
	AnimatorHolder::MarkAsRunning(Time);
}

void NumbersHolder::InitMario() {
	Sprite *sprite = new Sprite(20, 10, AnimationFilmHolder::GetFilm( std::string("mario") ));
	MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
					0, 0, 
					0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mario"))
					);
	MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
	Mario = aMovAnimr;
	aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
	AnimatorHolder::Register( aMovAnimr );				
	AnimatorHolder::MarkAsRunning(Mario);
}

void NumbersHolder::InitWorld() {
	Sprite *sprite = new Sprite(150, 10, AnimationFilmHolder::GetFilm( std::string("world") ));
	MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
					0, 0, 
					0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("world"))
					);
	MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
	World = aMovAnimr;
	aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
	AnimatorHolder::Register( aMovAnimr );				
	AnimatorHolder::MarkAsRunning(World);
}

void NumbersHolder::InitEpi() {
	Sprite *sprite = new Sprite(100, 10, AnimationFilmHolder::GetFilm( std::string("epi") ));
	MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
					0, 0, 
					0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("epi"))
					);
	MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
	Epi = aMovAnimr;
	aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
	AnimatorHolder::Register( aMovAnimr );				
	AnimatorHolder::MarkAsRunning(Epi);
}
