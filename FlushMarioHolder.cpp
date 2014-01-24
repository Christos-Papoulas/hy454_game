#include "header_files\mario\FlushMarioHolder.h"

void FlushMario::InitMario(){
		Walking();
		Waiting();
		StandJump();
		WalkJumnp();
		BackWalk();
		BackWalkJump();
}

MovingAnimator* FlushMario::marioWalking = NULL;
void FlushMario::Walking() {
		if(marioWalking){
				Mario::CreateWalking(marioWalking);
				return ;
		} 
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
																		AnimationFilmHolder::GetFilm( std::string("flushmariowalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 5, 
						4, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariowalking"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		marioWalking = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

MovingAnimator* FlushMario::marioWaiting = NULL;
void FlushMario::Waiting() {
		if(FlushMario::marioWaiting){ 
				Mario::CreateWaiting(FlushMario::marioWaiting);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("flushmariowaiting") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						0, 0, 120, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariowaiting"))
						);
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		
		Mario::CreateWaiting(aMovAnimr);
		FlushMario::marioWaiting = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinisWaiting, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* FlushMario::MarioStandJump = NULL;
void FlushMario::StandJump() {
		if(FlushMario::MarioStandJump) {
				Mario::CreateSjumping(FlushMario::MarioStandJump);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("flushmariojump") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, i % 2, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, 
				ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariojump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateSjumping(aMovAnimr);
		MarioStandJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* FlushMario::MarioWalkJump = NULL;
void FlushMario::WalkJumnp() {
		if(FlushMario::MarioWalkJump) {
				Mario::CreateWjumping(FlushMario::MarioWalkJump);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("flushmariojump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, i % 2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, i % 2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, 
				ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariojump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		Sprite::CollisionCheck(spriteMario);
		Mario::CreateWjumping(aMovAnimr);
		MarioWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingPathAnimator* FlushMario::backWalkJump = NULL;
void FlushMario::BackWalkJump() {
		if(backWalkJump) {
				Mario::CreateBackAndJump( backWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("flushmariobjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, i % 2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, i % 2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, 
				ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariobjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		Sprite::CollisionCheck(spriteMario);
		Mario::CreateBackAndJump( aMovAnimr );
		backWalkJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackJump, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* FlushMario::marioBackWalk = NULL;
void FlushMario::BackWalk() {
		if(marioBackWalk) {
				Mario::CreateBackWalking(marioBackWalk);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("flushmariobwalk") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 5, 
						-3, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushmariobwalk"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		marioBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

MovingAnimator* FlushMario::SuperFlushWalking = NULL;
MovingAnimator* FlushMario::SuperFlushWaiting = NULL;
MovingPathAnimator* FlushMario::SuperFlushStandJump = NULL;
MovingPathAnimator* FlushMario::SuperFlushWalkJump = NULL;
MovingPathAnimator* FlushMario::SuperFlushbackWalkJump = NULL;
MovingAnimator* FlushMario::SuperFlushBackWalk = NULL;

void FlushMario::InitSuperMario() {
		SuperWaiting();
		SuperWalking();
		SuperBackWalk();
		SuperWalkJump();
		SuperStandJump();
		SuperBackWalkJump();
}

void FlushMario::SuperWaiting() {
		if(SuperFlushWaiting){ 
				Mario::CreateWaiting(SuperFlushWaiting);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("superflushwaiting") ));
		
		MovingAnimation* aMovAnimn =new FrameRangeAnimation(
						0, 1, 
						0, 0, 90, false, 
						ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superflushwaiting"))
		);
		MovingAnimator* aMovAnimr =  new MovingAnimator(); 
		
		Mario::CreateWaiting(aMovAnimr);
		SuperFlushWaiting = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinisWaiting, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FlushMario::SuperWalking() {
		if(SuperFlushWalking){
				Mario::CreateWalking(SuperFlushWalking);
				return ;
		} 
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("flushsuperwalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 5, 
						4, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("flushsuperwalking"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateWalking(aMovAnimr);
		SuperFlushWalking = aMovAnimr;

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FlushMario::SuperBackWalk() {
		if(SuperFlushBackWalk) {
				Mario::CreateBackWalking(SuperFlushBackWalk);
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), 
				AnimationFilmHolder::GetFilm( std::string("superflushbwalk") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 5, 
						-3, 0, 90, false, 
						ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superflushbwalk"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Mario::CreateBackWalking(aMovAnimr);
		SuperFlushBackWalk  = aMovAnimr;
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackWalk, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FlushMario::SuperWalkJump() {
		if(SuperFlushWalkJump) {
				Mario::CreateWjumping( SuperFlushWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("superflushjump") ));
		std::vector<PathEntry> paths;
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, i % 2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, i % 2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(
				paths, 
				ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superflushjump"))
		);
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateWjumping( aMovAnimr );

		SuperFlushWalkJump = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishWjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FlushMario::SuperStandJump() {
		if(SuperFlushStandJump) {
				Mario::CreateSjumping(SuperFlushStandJump);
				return ;
		}

		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(),
				AnimationFilmHolder::GetFilm( std::string("superflushjump") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, i%2, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superflushjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateSjumping(aMovAnimr);
		SuperFlushStandJump = aMovAnimr;
		aMovAnimn->SetContinuous(false);

		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishSjumping, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void FlushMario::SuperBackWalkJump() {
		if(SuperFlushbackWalkJump) {
				Mario::CreateBackAndJump( SuperFlushbackWalkJump );
				return ;
		}
		Sprite* m = Mario::GetMarioCurrentSprite();
		Sprite * spriteMario = new Sprite(m->GetX(), m->GetY(), AnimationFilmHolder::GetFilm( std::string("superflushbjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, i%2, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, i%2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("superflushbjump")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		Mario::CreateBackAndJump( aMovAnimr );
		SuperFlushbackWalkJump = aMovAnimr;

		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( spriteMario, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Mario::MarioFinishBackJump, NULL);
		AnimatorHolder::Register( aMovAnimr );
}
