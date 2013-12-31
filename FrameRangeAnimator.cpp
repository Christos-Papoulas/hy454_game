#include "header_files\animator\FrameRangeAnimator.h"

// lecture11 slide30
void FrameRangeAnimator::Progress (timestamp_t currTime) {
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

// lecture11 slide31
/*
#define DELAY_TYPES 7
byte delayDivShifts[DELAY_TYPES] = {
		4,5,6,7,8,9,10 // 16, 32, 64, 128, 256, 512, 1024
};

#define DIV_DELAY(x,d) ((x) >> delayDivShifts[d])
#define MUL_DELAY(x,d) ((x) << delayDivShifts[d])
byte i = DIV_DELAY(currTime - lastTime, anim->GetDelay());
if (i) {
		lastTime += MUL_DELAY(i, anim->GetDelay());
		while (i--) {
				// To prohgoumeno ektos apo tin aukshsh tou lastTime
		}
}
*/