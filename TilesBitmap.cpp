#include "header_files\tiles\TilesBitmap.h"
#include <string>

Bitmap TilesBitmap::LoadTiles () {
	Bitmap b;
	b = al_load_bitmap(TILES_MAP_PATH);
	//al_convert_mask_to_alpha(b, BB_ELECTRIC_BLUE);
	//DASSERT( b );
	return b;
}
