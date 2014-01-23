#include "header_files/mario/NumbersHolder.h"

MovingAnimator* NumbersHolder::Numbers[N_MAX];
MovingAnimator* NumbersHolder::Time;
MovingAnimator* NumbersHolder::Mario;
MovingAnimator* NumbersHolder::World;
MovingAnimator* NumbersHolder::Epi;
MovingAnimator* NumbersHolder::Coin;
MovingAnimator* NumbersHolder::time1=NULL,*NumbersHolder::time2=NULL,*NumbersHolder::time3=NULL;

void NumbersHolder::Init() {
		Dim i = 0;
		std::vector<std::string> names;
		char * name[N_MAX] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
		for(i=0; i < N_MAX; i++){
			names.push_back(name[i]);
			Sprite *sprite = new Sprite(180, 30, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
			MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
							0, 0, 
							0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
							);
			MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
			Numbers[i] = aMovAnimr;
			aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
			AnimatorHolder::Register( aMovAnimr );
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

void NumbersHolder::InitCoin() {
	Sprite *sprite = new Sprite(85, 7, AnimationFilmHolder::GetFilm( std::string("coinanimation") ));
	MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
					0, 2, 
					0, 0, 200, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("coinanimation"))
					);
	MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
	Coin = aMovAnimr;
	aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
	AnimatorHolder::Register( aMovAnimr );				
	AnimatorHolder::MarkAsRunning(Coin);
}

void NumbersHolder::PrintNumberTime(Dim num) {
	Dim first = num / 100;
	Dim second = (num % 100) / 10;
	Dim third = num % 10;
	if(time1) AnimatorHolder::MarkAsSuspended(time1);
	if(time2) AnimatorHolder::MarkAsSuspended(time2);
	if(time3) AnimatorHolder::MarkAsSuspended(time3);
	Numbers[first]->GetSprite()->SetX(180);

	AnimatorHolder::MarkAsRunning(Numbers[first]);
	Numbers[second]->GetSprite()->SetX(186);

	AnimatorHolder::MarkAsRunning(Numbers[second]);
	Numbers[third]->GetSprite()->SetX(192);

	AnimatorHolder::MarkAsRunning(Numbers[third]);

	time1 = Numbers[first];
	time2 = Numbers[second];
	time3 = Numbers[third];

}