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
		Sprite *spriteMario = new Sprite(20, 100, 
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
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("flushmariowaiting") ));
		
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
		if(MarioStandJump) {
				Mario::CreateSjumping(MarioStandJump);
				return ;
		}
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("flushmariojump") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -5 : 5, 0, 70);
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
		if(MarioWalkJump) {
				Mario::CreateWjumping(MarioWalkJump);
				return ;
		}
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("flushmariojump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 0, 100);
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
		Sprite * spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("flushmariobjump") ));
		std::vector<PathEntry> paths;
		
		for(offset_t i = 0, j= 28; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 18; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, 0, 100);
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
		Sprite *spriteMario = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("flushmariobwalk") ));
		
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