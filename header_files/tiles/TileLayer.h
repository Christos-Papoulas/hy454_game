#ifndef _TILELAYER_H_
#define _TILELAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <utility> // for pair
#include <assert.h>
#include <windows.h>

#include "..\logs\logs.h"
#include "..\Objects.h"
#include "TilesBitmap.h"

#define MAX_HEIGHT 15 
#define MAX_WIDTH 225

#define VIEW_WINDOW_TILE_WIDTH 16
#define VIEW_WINDOW_TILE_HEIGHT 16

//lecture9 slide53
class TileLayer{
		private:
				Index		map[MAX_HEIGHT][MAX_WIDTH];
				Dim			Collision[MAX_HEIGHT][MAX_WIDTH];
				Rect		viewWindow;
				TilesBitmap* tilesBitmap;
		public:
				TileLayer();
				~TileLayer();
				void SetTile(Dim col, Dim row, Index index);
				Index GetTile(Dim col, Dim row);
				const std::pair<Dim, Dim> GetTileCoordinates(Dim mx, Dim my) const;
				Rect GetViewWindow(void) /*const*/;
				void SetViewWindow(const Rect&);
				void Display(Bitmap at/*, const Rect& displayArea*/);
				void Scroll(HorizScroll h, VertScroll v);
				void ScrollHorizBy(Dim dx) { viewWindow.IncreaseX(dx); }
				bool CanScroll(HorizScroll h) const;
				bool CanScroll(VertScroll v) const;
				//bool ProgressViewWindow(HorizScroll h);
				void WriteMap(FILE* fp);
				bool ReadMap(FILE* fp);
};

#endif