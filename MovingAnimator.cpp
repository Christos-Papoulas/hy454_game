#include "header_files\animator\MovingAnimator.h"

// lecture11 slide28
void MovingAnimator::Progress (timestamp_t currTime) {
	if (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		sprite->Move(anim->GetDx(), anim->GetDy());
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
		else {
			lastTime += anim->GetDelay();
			Progress(currTime);  // Recursion (make it a loop)
		}
	}
}

void MovingAnimator::Display(Bitmap at) { 
		sprite->Display(at);
}

