#include "header_files\animation\Sprites.h"

void Sprite::SetFrame (byte i) {
		if(i != frameNo) {
				assert(i < currFilm->GetTotalFrames());
				frameBox = currFilm->GetFrameBox(frameNo = i);
		}
}

byte Sprite::GetFrame () const {
		return frameNo;
}

void Sprite::SetVisibility (bool v) {
		isVisible = v;
}

bool Sprite::IsVisible() const {
		return isVisible;
}

bool Sprite::CollisionCheck (Sprite *s) {
		assert(0 && "unimplemented");
		return false;
}


void Sprite::Move (Dim x,Dim y) {
	assert(0 && "unimplemented");
	return ;
	/*Apply the movement;
	if (gravityAddicted) {
		Check the terrain tiles just below;
		if (over solid terrain) {
			if (isFalling) {
				isFalling = false;
				NotifyStopFalling();
			}
		}
		else
			if (!isFalling) {
				isFalling = true; 
				NotifyStartFalling(); 
			}
	}*/
}

Sprite::Sprite(Dim _x, Dim _y, AnimationFilm* film) : 
		x(_x), y(_y), currFilm(film), isVisible(true)
{
		frameNo = currFilm->GetTotalFrames();
		SetFrame(0);
}