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
						0, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(1u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::Create(aMovAnimr);
		
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

void Initializer::InitMarioWaiting() {
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("mariowaiting") ));
		
		MovingAnimation* aMovAnimn = new MovingAnimation(0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(3u));/* new FrameRangeAnimation(
						0, 0, 
						0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(3u)
						);*/
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWaiting(aMovAnimr);

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
//		aMovAnimr->SetOnFinish(NULL, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Initializer::InitMario() {
		InitMarioWalking();
		InitMarioWaiting();
}