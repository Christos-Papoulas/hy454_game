#include "header_files/animator/MovingPathAnimator.h"

MovingPathAnimator::MovingPathAnimator() : sprite(NULL), anim(NULL), currIndex(0), totalReplays(0){
		;
}

MovingPathAnimator::~MovingPathAnimator() {
		;
}

MovingPathAnimation* MovingPathAnimator::GetAnimation(void) {
		return anim; 
}

Sprite* MovingPathAnimator::GetSprite(void){
		return sprite; 
}

void MovingPathAnimator::Progress (timestamp_t currTime) {
		currIndex = 0u;
		assert(lastTime <= currTime); 
		assert(anim->GetPath().size());
		while (currTime > lastTime && currTime - lastTime >= anim->GetPath()[currIndex].delay){
				sprite->Move(anim->GetPath()[currIndex].dx, anim->GetPath()[currIndex].dy);

				sprite->SetFrame(anim->GetPath()[currIndex].frame);
				lastTime += anim->GetPath()[currIndex].delay;
				currIndex +=1;
				if (currIndex == anim->GetPath().size()){
						if(!anim->GetContinuous()){
								state = ANIMATOR_FINISHED;
								NotifyStopped();
								return;
						}else
								currIndex = 0;
				}
		}
}

void MovingPathAnimator::Start (Sprite* s, MovingPathAnimation* a, timestamp_t t) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		sprite->SetFrame(anim->GetPath()[currIndex].frame);
		return ;
}

void MovingPathAnimator::Display(Bitmap at) {
		sprite->Display(at);
}
