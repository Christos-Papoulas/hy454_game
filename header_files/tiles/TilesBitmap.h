#ifndef _TILES_BITMAP_H_
#define _TILES_BITMAP_H_

#include "..\Objects.h"
#include "..\terrain\TerrainUtils.h"

#define MAX_WIDTH 225
#define MAX_HEIGHT 15
#define SCREEN_WINDOW_WIDTH 16*16
#define SCREEN_WINDOW_HEIGHT 16*15
#define TILES_MAP_PATH ".\\Data\\Bitmaps\\Tiles\\map.png"

#include <string>

//lecture9 slide52
class TilesBitmap {
	public:
		TilesBitmap();
	private:
		unsigned tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
		Bitmap tiles;

		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string & path);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string & path);
		//bool LoadTiles (const std::string & path);
		Bitmap LoadTiles (void);

	public:
		void PutTile (Bitmap at, Dim x, Dim y, Index tile, Dim scroll) const;
		Index GetPointedTile (Dim x, Dim y) const;
		
};

#endif