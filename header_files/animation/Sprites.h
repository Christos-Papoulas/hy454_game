#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "../Objects.h"
#include "AnimationFilm.h"
#include "..\tiles\TileLayer.h"
#include <assert.h>

//lecture10 slide24
class Sprite {
		byte frameNo;
		Rect frameBox;
		Dim x, y; // hold the position of sprite at the map
		bool isVisible;
		AnimationFilm* currFilm;
		TileLayer* myLayer;
		public:
				Sprite (Dim _x, Dim _y, AnimationFilm* film);
				Dim GetX();
				Dim GetY();
				void SetX(Dim _x);
				void SetY(Dim _y);
				void SetFrame (byte i);
				byte GetFrame () const;
				void SetVisibility (bool v);
				bool IsVisible () const;
				bool CollisionCheck (Sprite *s);
				void Display(Bitmap dest);
				void Move(Dim x,Dim y);
};

#endif