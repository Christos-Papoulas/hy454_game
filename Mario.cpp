#include "header_files\mario\Mario.h"

Mario::Mario(MovingAnimator* mario_animator){
	assert(mario_animator);

}

Mario::~Mario() {
		delete mario; mario = NULL;
}

void Mario::Create(MovingAnimator* mario_animator) {
		if(!mario)
				mario = new Mario(mario_animator);
}