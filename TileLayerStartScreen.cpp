#include "header_files\tiles\TileLayerStartScreen.h"

TileLayerStartScreen::TileLayerStartScreen() {
		start_screen_tiles = new TilesBitmapStartScreen();
}

Rect TileLayerStartScreen::GetViewWindow(void) /*const*/ {
		return viewStartScreenWindow;
}

bool TileLayerStartScreen::ReadMap(FILE* fp) {
	assert(fp != NULL);
	
	for(int i = 0; i < MAX_HEIGHT; ++i)
			for(int j = 0; j < MAX_WIDTH_; ++j)
					fscanf(fp, "%d", &start_screen[i][j]);
					
	log_write(__FILE__, __LINE__, "read start screen successfuly.");

	return true;
}

//lecture9 slide 14
void TileLayerStartScreen::SetTile(Dim col, Dim row, Index index) {
		start_screen[row][col] = index;
}

Index TileLayerStartScreen::GetTile(Dim col, Dim row) { 
		Dim y = viewStartScreenWindow.GetY();
		
		return start_screen[row][col + y]; 
}

void TileLayerStartScreen::WriteMap(FILE* fp) { 
	fwrite(start_screen, sizeof(start_screen[MAX_HEIGHT][MAX_WIDTH_]), 1, fp); 
}

void TileLayerStartScreen::Display(Bitmap at/*, const Rect& displayArea*/) {
		assert(at);

		al_set_target_bitmap(at);
		al_clear_to_color(al_map_rgb(0,0,0));

		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_HEIGHT; j++)
						start_screen_tiles->PutTile(at, i, j, GetTile(viewStartScreenWindow.GetX() + i, viewStartScreenWindow.GetY() + j));
}
