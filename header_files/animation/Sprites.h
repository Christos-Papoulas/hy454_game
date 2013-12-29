#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "../Objects.h"
#include "AnimationFilm.h"
#include "..\tiles\TileLayer.h"
#include <assert.h>

class Sprite {
		byte frameNo;
		Rect frameBox;
		Dim x, y;
		bool isVisible;
		AnimationFilm* currFilm;
		TileLayer* myLayer;
		public:
				void SetFrame (byte i);
				byte GetFrame () const;
				void SetVisibility (bool v);
				bool IsVisible () const;
				bool CollisionCheck (Sprite *s);
				Sprite (Dim _x, Dim _y, AnimationFilm* film);
				void Display(Bitmap dest);
				void Move(Dim x,Dim y);
};

#endif