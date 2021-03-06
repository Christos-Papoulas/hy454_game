#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "../Objects.h"
#include "AnimationFilm.h"
#include "..\tiles\TileLayer.h"
#include "..\collision\Collision.h"
#include <assert.h>

//lecture10 slide24
class Sprite {
		byte frameNo;
		Rect frameBox;
		Dim x;
		Dim y; // hold the position of sprite at the map
		bool isVisible;
		AnimationFilm* currFilm;
		
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
				void Move(Dim x, Dim y); //right
				void Move(int x, int y);
				void MoveLeft(Dim x);
				void MoveUp(Dim y);
				Dim GetTileX();
				Dim GetTileY();
				void SetFilmAndReset(AnimationFilm*);
				AnimationFilm* GetCurrFilm();
				Rect GetFrameBox() { return frameBox; }
				static bool Overlap(Sprite* s1, Sprite* s2);
};

#endif