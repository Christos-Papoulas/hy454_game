#include "MovingAnimator.h"

// lecture11 slide28
void MovingAnimator::Progress (timestamp_t currTime) {
	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		sprite->Move(anim->GetDx(), anim->GetDy());
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			lastTime = currTime;
		}
		else 
			lastTime += anim->GetDelay();
	}
}

void MovingAnimator::Display(Bitmap at) { 
		sprite->Display(at);
}

Sprite* MovingAnimator::GetSprite() {
	return sprite;
}
