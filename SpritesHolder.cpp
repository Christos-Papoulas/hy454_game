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
						4, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(0u)
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
		
		MovingAnimation* aMovAnimn = new MovingAnimation(0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(3u));
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		Sprite::CollisionCheck(spriteMario);
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
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
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
				printf("%d ", -j);
				paths.push_back( pathEntry );
		}
		printf("\n");
		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 0, 100);
				printf("%d ", j);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWjumping(aMovAnimr);
		MarioWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}


void Initializer::BackWalkJump() {
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariobackjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 16; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 6; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(15u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateBackAndJump( aMovAnimr );
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
						-3, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(6u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		marioBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMarioDeath() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariodeading") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -2 : 2, 0, 200);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(2u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateDeath(aMovAnimr);
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishDeath, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

static MovingAnimator* superWaiting = NULL;
void Initializer::SuperWaiting() {
		if(superWaiting) {
				Mario::CreateWaiting(superWaiting);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("superwaiting") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(23u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWaiting(aMovAnimr);
		superWaiting = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

static MovingAnimator* superWalking = NULL;
void Initializer::SuperWalking() {
		if(superWalking) {
				Mario::CreateWalking(superWalking);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("superwalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						4, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(25u)
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
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("superbackwalk") ));
		
		/*MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						-3, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(6u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		superBackWalk = aMovAnimr;
		marioBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );*/
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