#ifndef _TILES_BITMAP_START_SCREEN_H_
#define _TILES_BITMAP_START_SCREEN_H_

#include "..\Objects.h"
#include "..\terrain\TerrainUtils.h"

#define MAX_WIDTH 225
#define MAX_HEIGHT 15
#define SCREEN_WINDOW_WIDTH 16*16
#define SCREEN_WINDOW_HEIGHT 16*15
#define TILES_START_SCREEN_PATH ".\\Data\\Bitmaps\\Tiles\\Game_Start.jpg"

#include <string>

//lecture9 slide52
class TilesBitmapStartScreen {
	public:
		TilesBitmapStartScreen();
	private:
		unsigned tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
		Bitmap start_screen_tiles;

		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string & path);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string & path);
		Bitmap StartScreenLoadTiles (void);

	public:
		void PutTile (Bitmap at, Dim x, Dim y, Index tile) const;
		Index GetPointedTile (Dim x, Dim y) const;
		
};

#endif