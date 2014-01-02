#include "header_files\animator\AnimatorHolder.h"

std::list<Animator*> AnimatorHolder::running, AnimatorHolder::suspended;

void AnimatorHolder::Progress(timestamp_t currTime) {
		for (std::list<Animator*>::const_iterator  it = running.begin(); it != running.end(); it++)
				(*it)->Progress(currTime);
}

void AnimatorHolder::Display(Bitmap at) {
		for (std::list<Animator*>::const_iterator  it = running.begin(); it != running.end(); it++)
				(*it)->Display(at);
}