#include "FireMario.h"

MovingAnimator* FireMario::marioWalking = NULL;
MovingAnimator* FireMario::marioWaiting = NULL;
MovingPathAnimator* FireMario::MarioStandJump = NULL;
MovingPathAnimator* FireMario::MarioWalkJump = NULL;
MovingPathAnimator* FireMario::backWalkJump = NULL;
MovingAnimator* FireMario::marioBackWalk = NULL;
MovingAnimator* FireMario::marioDown = NULL;

void FireMario::FireMario() {
	Waiting();
	Walking();
	BackWalk();
	WalkJump();
	StandJump();
	BackWalkJump();
	Down();
}

void FireMario::Waiting() {
		if(marioWaiting){ 
				Mario::CreateWaiting(marioWaiting);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("firewaiting") ));
		
		MovingAnimation* aMovAnimn =new FrameRangeAnimation(
						0, 0, 
						0, 0, 90, false, 
						ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firewaiting"))
		);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator();
		
		Mario::CreateWaiting(aMovAnimr);
		marioWaiting = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinisWaiting, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::Walking() {
		if(marioWalking){
				Mario::CreateWalking(marioWalking);
				return ;
		} 
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("firewalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						4, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firewalking"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		marioWalking = aMovAnimr;

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::BackWalk() {
		if(marioBackWalk) {
				Mario::CreateBackWalking(marioBackWalk);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), 
				AnimationFilmHolder::GetFilm( std::string("firebackwalk") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						-3, 0, 90, false, 
						ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firebackwalk"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		marioBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::WalkJump() {
		if(MarioWalkJump) {
				Mario::CreateWjumping( MarioWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("firejump") ));
		std::vector<PathEntry> paths;
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(
				paths, 
				ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firejump"))
		);
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateWjumping( aMovAnimr );

		MarioWalkJump = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::StandJump() {
		if(MarioStandJump) {
				Mario::CreateSjumping(MarioStandJump);
				return ;
		}

		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("firejump") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, 0, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firejump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateSjumping(aMovAnimr);
		MarioStandJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::BackWalkJump() {
		if(backWalkJump) {
				Mario::CreateBackAndJump( backWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("firebjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firebjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateBackAndJump( aMovAnimr );
		backWalkJump = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackJump, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FireMario::Down() {
		if(marioDown){
				Mario::CreateDown(marioDown);
				return ;
		} 
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
																		AnimationFilmHolder::GetFilm( std::string("firedown") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("firedown"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateDown(aMovAnimr);
		marioDown = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::FinishDown, NULL);
		AnimatorHolder::Register( aMovAnimr );				
}