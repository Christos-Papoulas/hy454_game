#include "header_files\items\DestructionAnimation.h"

Destruction::Destruction(Dim x, Dim y) {
		s1 = new Sprite(x-8, y, AnimationFilmHolder::GetFilm( std::string(BRICK_NAME) ));
		s2 = new Sprite(x-8, y+16, AnimationFilmHolder::GetFilm( std::string(BRICK_NAME) ));
		s3 = new Sprite(x+16, y, AnimationFilmHolder::GetFilm( std::string(BRICK_NAME) ));
		s4 = new Sprite(x+16, y+16, AnimationFilmHolder::GetFilm( std::string(BRICK_NAME) ));

		delay_t delay = 70;
		//p1
		Dim start1 = 12, start2 = 0;
		Dim xp = 5;
		for(offset_t i = 0, j= start1; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-1, -1, 0, delay);
				p1.push_back( pathEntry );
		}

		// p2
		for(offset_t i = 0, j= start1; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-1, 1, 0, delay);
				p2.push_back( pathEntry );
		}

		// p3
		for(offset_t i = 0, j= start1; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(1, -1, 0, delay);
				p3.push_back( pathEntry );
		}

		//p4
		for(offset_t i = 0, j= start1; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(1, 1, 0, delay);
				p4.push_back( pathEntry );
		}


		anim1 = new MovingPathAnimation(
								p1, 
								ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(BRICK_NAME))
						);
		anim2 = new MovingPathAnimation(
								p2, 
								ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(BRICK_NAME))
						);
		anim3 = new MovingPathAnimation(
								p3, 
								ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(BRICK_NAME))
						);
		anim4 = new MovingPathAnimation(
								p4, 
								ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(BRICK_NAME))
						);
		
		tor1 = (MovingPathAnimator*) new MovingPathAnimator(); 
		tor2 = (MovingPathAnimator*) new MovingPathAnimator(); 
		tor3 = (MovingPathAnimator*) new MovingPathAnimator(); 
		tor4 = (MovingPathAnimator*) new MovingPathAnimator(); 

		anim1->SetContinuous(false); anim2->SetContinuous(false);
		anim3->SetContinuous(false); anim4->SetContinuous(false);

		tor1->Start( s1, anim1, GetCurrTime());
		tor2->Start( s2, anim2, GetCurrTime());
		tor3->Start( s3, anim3, GetCurrTime());
		tor4->Start( s4, anim4, GetCurrTime());
		this->SetOnFinish(Destruction::FinishDestroy, NULL);
		currIndex = 0;
}

void Destruction::Progress (timestamp_t currTime) {
	while (currTime > lastTime && currTime - lastTime >= anim1->GetPath()[currIndex].delay){
				lastTime += anim1->GetPath()[currIndex].delay;
			
				s1->Move(anim1->GetPath()[currIndex].dx, anim1->GetPath()[currIndex].dy);
				s1->SetFrame(anim1->GetPath()[currIndex].frame);
				s2->Move(anim2->GetPath()[currIndex].dx, anim2->GetPath()[currIndex].dy);
				s2->SetFrame(anim2->GetPath()[currIndex].frame);
				s3->Move(anim3->GetPath()[currIndex].dx, anim3->GetPath()[currIndex].dy);
				s3->SetFrame(anim3->GetPath()[currIndex].frame);
				s4->Move(anim4->GetPath()[currIndex].dx, anim4->GetPath()[currIndex].dy);
				s4->SetFrame(anim4->GetPath()[currIndex].frame);

				
				currIndex +=1;
				if (currIndex == anim1->GetPath().size()){
						if(!anim1->GetContinuous()){
								state = ANIMATOR_FINISHED;
								lastTime = currTime; 
								currIndex = 0;
								NotifyStopped();
								return;
						}else
								currIndex = 0;
				}
		}

}

void Destruction::Display(Bitmap at) { 
		s1->Display(at);
		s2->Display(at);
		s3->Display(at);
		s4->Display(at);
}

void Destruction::Reset(Dim x, Dim y) {
		s1->SetX(x-8);	s2->SetX(x-8);
		s3->SetX(x+16); s4->SetX(x+16);
		s1->SetY(y);		s2->SetY(y+16);
		s3->SetY(y);		s4->SetY(y+16);
}