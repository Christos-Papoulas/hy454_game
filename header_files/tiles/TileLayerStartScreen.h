#ifndef _TILELAYER_START_SCREEN_H_
#define _TILELAYER_START_SCREEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <utility> // for pair
#include <assert.h>
#include <windows.h>

#include "..\logs\logs.h"
#include "..\Objects.h"
#include "TilesBitmapStartScreen.h"
#include "../collision/Collision.h"
#include "TileLayer.h"

#define MAX_HEIGHT 15 
#define MAX_WIDTH_ 16



//lecture9 slide53
class TileLayerStartScreen{
		private:
				Index		start_screen[MAX_HEIGHT][MAX_WIDTH_];
				Rect		viewStartScreenWindow;
				TilesBitmapStartScreen* start_screen_tiles;
		public:
				TileLayerStartScreen();
				~TileLayerStartScreen();
				void SetTile(Dim col, Dim row, Index index);
				Index GetTile(Dim col, Dim row);
				const std::pair<Dim, Dim> GetTileCoordinates(Dim mx, Dim my) const;
				Rect GetViewWindow(void) /*const*/;
				void SetViewWindow(const Rect&);
				void Display(Bitmap at/*, const Rect& displayArea*/);
				void WriteMap(FILE* fp);
				bool ReadMap(FILE* fp);
};

#endif