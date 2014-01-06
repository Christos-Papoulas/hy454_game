#include "header_files\mario\SpritesHolder.h"

SpritesHolder::SpritesHolder() {
		Initializer::InitMario();
}

SpritesHolder::~SpritesHolder() {
		;
}

void Initializer::InitMarioWalking() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						0, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(0u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

void Initializer::InitMarioWaiting() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowaiting") ));
		
		MovingAnimation* aMovAnimn = new MovingAnimation(0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(3u));
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWaiting(aMovAnimr);

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinisWaiting, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMarioStandJump() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariojumping") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, 0, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateSjumping(aMovAnimr);
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMarioWalkJumnp() {
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariojumping") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 20; i < 10; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, 0, 300);
				printf("%d ", -j);
				paths.push_back( pathEntry );
		}
		printf("\n");
		for(offset_t i = 0, j= 2; i < 10; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 0, 300);
				printf("%d ", j);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWjumping(aMovAnimr);
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMario() {
		InitMarioWalking();
		InitMarioWaiting();
		InitMarioStandJump();
		InitMarioWalkJumnp();
}