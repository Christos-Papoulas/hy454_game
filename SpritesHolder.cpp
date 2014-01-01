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
		Sprite *spriteMario = new Sprite(100, 100, AnimationFilmHolder::GetFilm( std::string("mariowaiting") ));
		// @todo put & make sure the currect values
		MovingAnimation* aMovAnimn = new MovingAnimation(100, 100, 100, true, ParseMarioInfo::GetAnimationIdOf(1u));
		MovingAnimator* aMovAnimr = (MovingAnimator*) new MovingAnimator(); // @todo implement Animator
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());				
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}