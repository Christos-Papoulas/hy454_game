#include "header_files/mario/NumbersHolder.h"

std::map<Dim, std::list<MovingAnimator*>> NumbersHolder::suspending;
std::map<Dim, std::list<MovingAnimator*>> NumbersHolder::running;
Dim Time::time = 400;

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

MovingAnimator* NumbersHolder::DisplayNumber(Dim number, Dim x){
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
	return g;
}

void NumbersHolder::SuspendNumbers(Dim number, MovingAnimator* g){
	std::list<MovingAnimator*>::iterator it = running[number].begin();
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
	
	SuspendNumbers(t1, time1);
	SuspendNumbers(t2, time2);
	SuspendNumbers(t3, time3);

	time1 = DisplayNumber(first, 218);
	time2 = DisplayNumber(second, 225);
	time3 = DisplayNumber(third, 231);

	t1 = first;
	t2 = second;
	t3 = third;
}

void NumbersHolder::PrintNumberCoins(Dim num) {
	Dim first = num / 10;
	Dim second = num % 10;

	SuspendNumbers(c1, coin1);
	SuspendNumbers(c2, coin2);
	
	coin1 = DisplayNumber(first, 110);
	coin2 = DisplayNumber(second, 117);

	c1 = first;
	c2 = second;
}

void NumbersHolder::PrintScore(Dim num) {
	Dim first = num / 100000;
	Dim second = (num % 100000) / 10000;
	Dim third = (num % 10000) / 1000;
	Dim fourth = (num % 1000) / 100;
	Dim fifth = (num % 100) / 10;
	Dim sixth = num % 10;

	SuspendNumbers(sc1, score1);
	SuspendNumbers(sc2, score2);
	SuspendNumbers(sc3, score3);
	SuspendNumbers(sc4, score4);
	SuspendNumbers(sc5, score5);
	SuspendNumbers(sc6, score6);

	score1 = DisplayNumber(first, 20);
	score2 = DisplayNumber(second, 27);
	score3 = DisplayNumber(third, 33);
	score4 = DisplayNumber(fourth, 40);
	score5 = DisplayNumber(fifth, 47);
	score6 = DisplayNumber(sixth, 54);

	sc1 = first;
	sc2 = second;
	sc3 = third;
	sc4 = fourth;
	sc5 = fifth;
	sc6 = sixth;

}

unsigned long prev = 0;
void Time::clock() {
	SYSTEMTIME st; GetSystemTime(&st);
	unsigned int sec = st.wSecond;

	if(prev == 0)
		prev = sec;
	else if(sec - prev >= 1) {
		prev = sec;
		time--;
	}
}