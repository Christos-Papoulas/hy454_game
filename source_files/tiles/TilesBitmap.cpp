#include "TilesBitmap.h"
#include <string>

TilesBitmap::TilesBitmap() {
	LoadTiles();
}

Bitmap TilesBitmap::LoadTiles() {
	tiles = al_load_bitmap(TILES_MAP_PATH);
	assert( tiles );
	al_convert_mask_to_alpha(tiles, al_map_rgba(0, 0, 0, 0));
	return tiles;
}

void TilesBitmap::PutTile(Bitmap at, Dim x, Dim y, Index tile, Dim scroll) const {
	assert(at);
	Dim pixel = x == 0 && scroll ? scroll : 0;
	if(tile > 0 && tile < TILES_COLUMNS*TILES_ROWS) {
		Dim tiley = divIndex[tile] << 4;
		Dim tilex = modIndex[tile] << 4;
		al_draw_bitmap_region(tiles, tilex + pixel, tiley, 16 - pixel, 16, x*16 - ((x > 0)?scroll:0), y*16, NULL); // @todo the real values
	}
}