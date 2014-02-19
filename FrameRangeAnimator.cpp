#include "header_files\animator\FrameRangeAnimator.h"

// lecture11 slide30
void FrameRangeAnimator::Progress (timestamp_t currTime) {
	assert(anim);
	//assert(lastTime <= currTime);
	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
		else
			++currFrame;
		sprite->Move(anim->GetDx(), anim->GetDy());
		sprite->SetFrame(currFrame);
		lastTime += anim->GetDelay();
		if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

void FrameRangeAnimator::Display(Bitmap at){
	sprite->Display(at);
}
