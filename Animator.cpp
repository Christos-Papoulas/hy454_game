#include "header_files\animator\Animator.h"

// lecture11 slide25
void Animator::Stop (void) {
	if (!HasFinished()) {
		state = ANIMATOR_STOPPED;
		NotifyStopped();
	}
}

void Animator::NotifyStopped (void) {
	if (onFinish)
		(*onFinish)(this, finishClosure);
}

void Animator::TimeShift (timestamp_t offset) { 
	lastTime += offset; 
}

Animator::Animator (void) : lastTime(0), state(ANIMATOR_FINISHED), 
onFinish((FinishCallback) 0), finishClosure((void*) 0){}