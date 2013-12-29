#include "header_files\tiles\TilesBitmap.h"
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

void TilesBitmap::PutTile(Bitmap at, Dim x, Dim y, Index tile) const {
	assert(at);
	if(tile > 0 && tile < TILES_COLUMNS*TILES_ROWS) {
		Dim tiley = divIndex[tile] << 4;//TerrainUtils::TileX2(33);
		Dim tilex = modIndex[tile] << 4;//TerrainUtils::TileY2(33);
		al_draw_bitmap_region(tiles, tilex, tiley, 16, 16, x*16, y*16, NULL); // @todo the real values
	}
}