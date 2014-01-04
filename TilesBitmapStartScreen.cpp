#include "header_files\tiles\TilesBitmapStartScreen.h"
#include <string>

TilesBitmapStartScreen::TilesBitmapStartScreen() {
	StartScreenLoadTiles();
}

Bitmap TilesBitmapStartScreen::StartScreenLoadTiles() {
	start_screen_tiles = al_load_bitmap(TILES_START_SCREEN_PATH);
	assert( start_screen_tiles );
	al_convert_mask_to_alpha(start_screen_tiles, al_map_rgba(0, 0, 0, 0));
	return start_screen_tiles;
}

void TilesBitmapStartScreen::PutTile(Bitmap at, Dim x, Dim y, Index tile) const {
	assert(at);
	if(tile > 0 && tile < TILES_COLUMNS_START_SCREEN*TILES_ROWS_START_SCREEN) {
		Dim tiley = divIndex_start_screen[tile] << 4;
		Dim tilex = modIndex_start_screen[tile] << 4;
		al_draw_bitmap_region(start_screen_tiles, tilex, tiley, 16, 16, x*16, y*16, NULL); // @todo the real values
	}
}