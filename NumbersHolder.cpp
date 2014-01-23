#include "header_files/mario/NumbersHolder.h"

std::map<Dim, std::list<MovingAnimator*>> NumbersHolder::suspending;
std::map<Dim, std::list<MovingAnimator*>> NumbersHolder::running;

std::vector<std::string> names;
char * name[N_MAX] = {"zero","one","two","three","four","five","six","seven","eight","nine"};

MovingAnimator* NumbersHolder::Time;
MovingAnimator* NumbersHolder::Mario;
MovingAnimator* NumbersHolder::World;
MovingAnimator* NumbersHolder::Epi;
MovingAnimator* NumbersHolder::Coin;
MovingAnimator* NumbersHolder::time1=NULL,*NumbersHolder::time2=NULL,*NumbersHolder::time3=NULL;

void NumbersHolder::Init() {
		Dim i = 0;
		
		for(i=0; i < N_MAX; i++){
			names.push_back(name[i]);
			Sprite *sprite = new Sprite(213, 20, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
			MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
							0, 0, 
							0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
							);
			MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
			suspending[i].push_back( aMovAnimr );

			aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		
			AnimatorHolder::Register( aMovAnimr );
		}
}

void NumbersHolder::CreateNumber(Dim i) {
		Sprite *sprite = new Sprite(213, 20, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[i].push_back( aMovAnimr );

		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
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

void NumbersHolder::DisplayNumber(Dim number, Dim x){
	MovingAnimator* g;
	if(suspending[number].size() == 0) 
			CreateNumber(number);

	assert(suspending[number].size());
	
	g = suspending[number].back();
	

	g->GetSprite()->SetX(x);

	running[number].push_back(g);
	AnimatorHolder::MarkAsRunning(g);
	suspending[number].pop_back();
	assert(suspending[number].size() == 0);
}

void NumbersHolder::SuspendNumbers(){
		for(Dim id = 0; id < N_MAX; ++id){
				for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) 
						suspending[id].push_back(*it);
				running[id].clear();
		}
		return ;		
}

void NumbersHolder::PrintNumberTime(Dim num) {
	Dim first = num / 100;
	Dim second = (num % 100) / 10;
	Dim third = num % 10;
	SuspendNumbers();
	DisplayNumber(first, 214);
	DisplayNumber(second, 221);
	DisplayNumber(third, 227);
}
