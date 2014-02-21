#include "Sprites.h"

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

#define COLLISION_OFFSET 8
bool Sprite::CollisionCheck (Sprite *s) {
	Dim h = frameBox.GetHeight() - COLLISION_OFFSET;
	Dim w = frameBox.GetWidth() - COLLISION_OFFSET;
	Dim x = this->x + COLLISION_OFFSET; 
	Dim y = this->y + COLLISION_OFFSET;

	Dim sh = s->GetFrameBox().GetHeight() - COLLISION_OFFSET;
	Dim sw = s->GetFrameBox().GetWidth() - COLLISION_OFFSET;
	Dim sx = s->GetX() + COLLISION_OFFSET;	Dim sy = s->GetY() + COLLISION_OFFSET;

	return	(
						( ( sx <= x && x <= (sx + sw) ) || ( x <= sx && sx <= (x + w) ) ) 
						&&
						( ( sy <= y && y <= (sy + sh) ) || ( y <= sy && sy <= (y + h) ) )
					);
}


void Sprite::Move (Dim x,Dim y) {
	SetX(GetX() + x);
	SetY(GetY() + y);
	return ;
}

void Sprite::Move(int x, int y){
	SetX(GetX() + x);
	SetY(GetY() + y);
	return ;
}

Sprite::Sprite(Dim _x, Dim _y, AnimationFilm* film) : 
		x(_x), y(_y), currFilm(film), isVisible(true)
{
		frameNo = currFilm->GetTotalFrames();
		SetFrame(0);
}

//lecture10 slide30
void Sprite::Display(Bitmap dest) {
		Rect visibleArea; 
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

void Sprite::MoveLeft(Dim x) {
		if(GetX() > x)
				SetX(GetX() - x);
}

void Sprite::MoveUp(Dim y) {
	if(GetY() > y)
		SetY(GetY() - y);
}

Dim Sprite::GetTileX() {
	return x/16;
}

Dim Sprite::GetTileY() {
	return y/16;
}

void Sprite::SetFilmAndReset(AnimationFilm* flm) {
		assert(flm);
		currFilm = flm; 
		frameNo = currFilm->GetTotalFrames();
		SetFrame(0u);
}

AnimationFilm* Sprite::GetCurrFilm() {
		return currFilm;
}

bool Sprite::Overlap(Sprite* s1, Sprite* s2) {//s1 is enemy , s2 is pipe
	Dim mx = s1->GetX();
	Dim my = s1->GetY();
	Dim mw = s1->GetFrameBox().GetWidth() + COLLISION_OFFSET;
	Dim mh = s1->GetFrameBox().GetHeight() + COLLISION_OFFSET;
	Dim x = s2->GetX() ;
	Dim y = s2->GetY() ;
	Dim w = s2->GetFrameBox().GetWidth();
	Dim h = s2->GetFrameBox().GetHeight();
	Dim Dy = (my > y) ? my - y : y - my;
	return (((x + 16 )>= mx && x - mx < 3) && Dy < 8)
					||
				 (((mx + 16) <= x && mx - x < 3) && Dy < 8);
}