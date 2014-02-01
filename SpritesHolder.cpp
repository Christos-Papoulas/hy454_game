#include "header_files\mario\SpritesHolder.h"

SpritesHolder::SpritesHolder() {
		Initializer::InitMario();
}

SpritesHolder::~SpritesHolder() {
		;
}

MovingAnimator* marioWalking = NULL;
void Initializer::InitMarioWalking() {
		if(marioWalking){
				Mario::CreateWalking(marioWalking);
				return ;
		} 
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						4, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariowalking"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		marioWalking = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

MovingAnimator* marioWaiting = NULL;
void Initializer::InitMarioWaiting() {
		if(marioWaiting){ 
				Mario::CreateWaiting(marioWaiting);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowaiting") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariowaiting"))
						);
		
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		
		Mario::CreateWaiting(aMovAnimr);
		marioWaiting = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinisWaiting, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* MarioStandJump = NULL;
void Initializer::InitMarioStandJump() {
		if(MarioStandJump) {
				Mario::CreateSjumping(MarioStandJump);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariojumping") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, 0, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariojumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateSjumping(aMovAnimr);
		MarioStandJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* MarioWalkJump = NULL;
void Initializer::InitMarioWalkJumnp() {
		if(MarioWalkJump) {
				Mario::CreateWjumping(MarioWalkJump);
				return ;
		}
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariojumping") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariojumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateWjumping(aMovAnimr);
		MarioWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* backWalkJump = NULL;
void Initializer::BackWalkJump() {
		if(backWalkJump) {
				Mario::CreateBackAndJump( backWalkJump );
				return ;
		}
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariobackjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariobackjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateBackAndJump( aMovAnimr );
		backWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackJump, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* marioBackWalk = NULL;
void Initializer::InitMarioBackWalk() {
		if(marioBackWalk) {
				Mario::CreateBackWalking(marioBackWalk);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariobackwalk") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						-3, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariobackwalk"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		marioBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* marioDeathkeeper = NULL;
void Initializer::InitMarioDeath() {
		if(marioDeathkeeper)
				return ;

		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariodeading") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -2 : 2, 0, 250);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariodeading")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateDeath(aMovAnimr);
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishDeath, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitSuperMario(){ 
	SuperWaiting();
	SuperWalking();
	SuperBackWalk();
	SuperWalkJump();
	SuperStandJump();
	SuperBackWalkJump();
	SuperDown();
}

MovingAnimator* superWaiting = NULL;
void Initializer::SuperWaiting() {
		if(superWaiting) {
				Mario::CreateWaiting(superWaiting);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superwaiting") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superwaiting"))
						);
		MovingAnimator* aMovAnimr =  new MovingAnimator();
		Mario::CreateWaiting(aMovAnimr);
		superWaiting = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* superWalking = NULL;
void Initializer::SuperWalking() {
		if(superWalking) {
				Mario::CreateWalking(superWalking);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superwalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						4, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superwalking"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		superWalking = aMovAnimr;

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* superBackWalk = NULL;
void Initializer::SuperBackWalk() {
		if(superBackWalk) {
				Mario::CreateBackWalking(superBackWalk);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superbackwalk") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						-3, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superbackwalk"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		superBackWalk = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* superWalkJump = NULL;
void Initializer::SuperWalkJump() {
		if(superWalkJump) {
				Mario::CreateWjumping(superWalkJump);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY()  - 16, AnimationFilmHolder::GetFilm( std::string("superjumping") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, i%2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, i%2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superjumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateWjumping(aMovAnimr);
		superWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* superStandJump = NULL;
void Initializer::SuperStandJump() {
		if(superStandJump) {
				Mario::CreateSjumping(superStandJump);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superjumping") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, 0, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superjumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateSjumping(aMovAnimr);
		superStandJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* superBackWalkJump = NULL;
void Initializer::SuperBackWalkJump() {
		if(superBackWalkJump) {
				Mario::CreateBackAndJump( superBackWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superbackjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 16; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, i%2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 6; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, i%2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superbackjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Mario::CreateBackAndJump( aMovAnimr );
		superBackWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackJump, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* superDown = NULL;
void Initializer::SuperDown() {
		if(superDown) {
				Mario::CreateDown(superDown);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY() - 16, AnimationFilmHolder::GetFilm( std::string("superdown") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new MovingAnimation(
			0, 0, 160, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superdown"))
		);
		MovingAnimator* aMovAnimr =  new MovingAnimator();
		Mario::CreateDown(aMovAnimr);
		superDown = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::FinishDown, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMario() {
		InitMarioWalking();
		InitMarioWaiting();
		InitMarioStandJump();
		InitMarioWalkJumnp();
		InitMarioBackWalk();
		InitMarioDeath();
		BackWalkJump();
}