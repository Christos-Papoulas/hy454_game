#include "header_files\tiles\TilesBitmap.h"
#include <string>

TilesBitmap::TilesBitmap() {
	LoadTiles();
	assert(tiles);
}

Bitmap TilesBitmap::LoadTiles() {
	tiles = al_load_bitmap(TILES_MAP_PATH);
	al_convert_mask_to_alpha(tiles, al_map_rgba(0, 0, 0, 0));
	assert( tiles );
	return tiles;
}

void TilesBitmap::PutTile(Bitmap at, Dim x, Dim y, Index tile) const {
	assert(at);
	if(tile)
			al_draw_bitmap_region(tiles, TerrainUtils::TileX(tile), TerrainUtils::TileY(tile), TILE_WIDTH, TILE_HEIGHT, x, y, NULL); // @todo the real values

}