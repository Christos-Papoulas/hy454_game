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
	SetX(GetX() + x);
	SetY(GetY() + y);
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

//lecture10 slide30
void Sprite::Display(Bitmap dest) {
		Rect visibleArea; /*
		Rect spriteArea(x, y, frameBox.w, frameBox.h);
		if (!ClippedEntirely(spriteArea, myLayer->GetPixelViewWindow(), &visibleArea)) {
				Rect clippedFrame(
						frameBox.x + (visibleArea.x -x),
						frameBox.y + (visibleArea.y -y),
						visibleArea.w,
						visibleArea.h
				);
				Point at(
						da.x + (visibleArea.x -myLayer->GetViewWinX()),
						da.y + (visibleArea.y -myLayer->GetViewWinY())
				);
				MaskedBlit(currFilm->GetBitmap(), clippedFrame,	dest, at);
		}*/
		al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.GetX(), frameBox.GetY(), 
			frameBox.GetWidth(), frameBox.GetHeight(), x, y, NULL);
}


Dim Sprite::GetX() {
		return x;
}

Dim Sprite::GetY() {
		return y;
}

void Sprite::SetX(Dim _x) {
		x = _x;
}

void Sprite::SetY(Dim _y) {
		y = _y;
}
