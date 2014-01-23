#include "header_files\animator\HiddenAnimator.h"

// lecture11 slide28
void HiddenAnimator::Progress (timestamp_t currTime) {
		assert(anim->GetPath().size());
		while (currTime > lastTime && currTime - lastTime >= anim->GetPath()[currIndex].delay){
				sprite->Move(anim->GetPath()[currIndex].dx, anim->GetPath()[currIndex].dy);

				sprite->SetFrame(anim->GetPath()[currIndex].frame);
				lastTime += anim->GetPath()[currIndex].delay;
				
				sprite->GetCurrFilm()->SetHeightToFrame(0, show += -anim->GetPath()[currIndex].dy);
				sprite->GetCurrFilm()->SetHeightToFrame(1, show);
				currIndex +=1;
				if (currIndex == anim->GetPath().size()){
						if(!anim->GetContinuous()){
								state = ANIMATOR_FINISHED;
								lastTime = currTime; //@todo working?
								currIndex = 0;
								NotifyStopped();
								return;
						}else
								currIndex = 0;
						show = 0;
				}
		}
}

void HiddenAnimator::Display(Bitmap at) { 
		sprite->Display(at);
}

Sprite* HiddenAnimator::GetSprite() {
	return sprite;
}

void HiddenAnimator::Start(Sprite* s, MovingPathAnimation* a, timestamp_t t) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		sprite->SetFrame(anim->GetPath()[currIndex].frame);
		return ;
}