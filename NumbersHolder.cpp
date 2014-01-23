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
Dim NumbersHolder::t1,NumbersHolder::t2,NumbersHolder::t3;
MovingAnimator* NumbersHolder::coin1=NULL,*NumbersHolder::coin2=NULL;
Dim NumbersHolder::c1,NumbersHolder::c2;
MovingAnimator* NumbersHolder::score1=NULL,*NumbersHolder::score2=NULL,*NumbersHolder::score3=NULL,*NumbersHolder::score4=NULL,*NumbersHolder::score5=NULL,*NumbersHolder::score6=NULL;
Dim NumbersHolder::sc1,NumbersHolder::sc2,NumbersHolder::sc3,NumbersHolder::sc4,NumbersHolder::sc5,NumbersHolder::sc6;

void NumbersHolder::Init() {
		Dim i = 0;
		
		for(i=0; i < N_MAX; i++){
			names.push_back(name[i]);
			Sprite *sprite = new Sprite(218, 20, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
			MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
							0, 0, 
							0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
							);
			MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
			suspending[i].push_back( aMovAnimr );

			aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		}
}

void NumbersHolder::CreateNumber(Dim i) {
		Sprite *sprite = new Sprite(218, 20, AnimationFilmHolder::GetFilm( std::string(names.at(i)) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 1000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(name[i]))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[i].push_back( aMovAnimr );

		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());
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
	Sprite *sprite = new Sprite(100, 20, AnimationFilmHolder::GetFilm( std::string("epi") ));
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
	Sprite *sprite = new Sprite(85, 15, AnimationFilmHolder::GetFilm( std::string("coinanimation") ));
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
	AnimatorHolder::Register( g );
	AnimatorHolder::MarkAsRunning(g);
	suspending[number].pop_back();
}

void NumbersHolder::SuspendNumbers(Dim number, MovingAnimator* g){
	std::list<MovingAnimator*>::iterator it;
	while (it != running[number].end()){
				if((*it) == (MovingAnimator*)  g) {
						suspending[number].push_back( *it );
						AnimatorHolder::MarkAsSuspended( *it );
						running[number].erase( it );
						return ;
				}
				else
						 ++it;
		}
	return ;
}

void NumbersHolder::PrintNumberTime(Dim num) {
	Dim first = num / 100;
	Dim second = (num % 100) / 10;
	Dim third = num % 10;
	
	DisplayNumber(first, 218);
	DisplayNumber(second, 225);
	DisplayNumber(third, 231);
}

void NumbersHolder::PrintNumberCoins(Dim num) {
	Dim first = num / 10;
	Dim second = num % 10;
	
	DisplayNumber(first, 110);
	DisplayNumber(second, 117);
}

void NumbersHolder::PrintScore(Dim num) {
	Dim first = num / 100000;
	Dim second = (num % 100000) / 10000;
	Dim third = (num % 10000) / 1000;
	Dim fourth = (num % 1000) / 100;
	Dim fifth = (num % 100) / 10;
	Dim sixth = num % 10;

	DisplayNumber(first, 20);
	DisplayNumber(second, 27);
	DisplayNumber(third, 33);
	DisplayNumber(fourth, 40);
	DisplayNumber(fifth, 47);
	DisplayNumber(sixth, 54);

}
