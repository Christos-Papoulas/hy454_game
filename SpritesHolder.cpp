#include "header_files\mario\SpritesHolder.h"


SpritesHolder::SpritesHolder() {
		Initializer::InitMario();
		//Sprite *spriteMario = new Sprite(100, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		//spriteMario->Display(AnimationFilmHolder::GetFilm( "mariowalking" )->GetBitmap());
}

SpritesHolder::~SpritesHolder() {
		;
}

void Initializer::InitMario() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		// @todo put & make sure the currect values
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(1u)
						);//new MovingAnimation(100, 100, 100, true, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); //(MovingAnimator*) new MovingAnimator(); // @todo implement Animator
		Sprite::CollisionCheck(spriteMario);
		Mario::Create(aMovAnimr);
		//((FrameRangeAnimation*) aMovAnimn)->start(spriteMario, aMovAnimn, currTime) ;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());				
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}