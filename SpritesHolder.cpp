#include "header_files\mario\SpritesHolder.h"


SpritesHolder::SpritesHolder() {
		Initializer::InitMario();
}

SpritesHolder::~SpritesHolder() {
		;
}
void Initializer::InitMarioWalking() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		// @todo put & make sure the currect values
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						0, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(1u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		//Sprite::CollisionCheck(spriteMario);
		Mario::Create(aMovAnimr);
		//((FrameRangeAnimation*) aMovAnimn)->start(spriteMario, aMovAnimn, currTime) ;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

void Initializer::InitMarioWaiting() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowaiting") ));
		// @todo put & make sure the currect values
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						0, 0, 100, false, ParseMarioInfo::GetAnimationIdOf(4u)
						);//new MovingAnimation(100, 100, 100, true, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); //(MovingAnimator*) new MovingAnimator(); // @todo implement Animator
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWaiting(aMovAnimr);
		//((FrameRangeAnimation*) aMovAnimn)->start(spriteMario, aMovAnimn, currTime) ;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(NULL, NULL);
		AnimatorHolder::Register( aMovAnimr );
		//AnimatorHolder::MarkAsSuspended( aMovAnimr );
}

void Initializer::InitMario() {
		InitMarioWalking();
		InitMarioWaiting();
}