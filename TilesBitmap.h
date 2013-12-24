#include "header_files\Objects.h"

#define MAX_WIDTH 1024
#define MAX_HEIGHT  256

class TilesBitmap {
	private:
		unsigned tileTransparency[MAX_WIDTH * MAX_HEIGHT / 32 + 1];
		Bitmap tiles;
		bool IsTileTransparent (Dim row, Dim col) const;
		bool LoadTransparencyInfo (const std::string & path);
		void ProduceTransparencyInfo (void);
		bool WriteTransparencyInfo (const std::string & path);
		bool LoadTiles (const std::string & path);
	public:
		void PutTile (Bitmap at, Dim x, Dim y, Index tile) const;
		Index GetPointedTile (Dim x, Dim y) const;
}