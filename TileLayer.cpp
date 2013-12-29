#include "header_files\tiles\TileLayer.h"

TileLayer::TileLayer() {
		tilesBitmap = new TilesBitmap();
}

bool TileLayer::ReadMap(FILE* fp) {
	assert(fp != NULL);
	
	for(int i = 0; i < MAX_HEIGHT; ++i)
			for(int j = 0; j < MAX_WIDTH; ++j)
					fscanf(fp, "%d", &map[i][j]);
	
	/*log_write(__FILE__, __LINE__, "read map successfuly.");
	for(int i = 0; i < MAX_HEIGHT; ++i) {
			for(int j = 0; j < MAX_WIDTH; ++j)
					map[i][j]--;
			
	}*/
					
	return true;
}

//lecture9 slide 14
void TileLayer::SetTile(Dim col, Dim row, Index index) {
		map[row][col] = index;
}

Index TileLayer::GetTile(Dim col, Dim row) { 
		return map[row][col + viewWindow.GetY()]; 
}

void TileLayer::WriteMap(FILE* fp) { 
	fwrite(map, sizeof(map[MAX_HEIGHT][MAX_WIDTH]), 1, fp); 
}

//lecture9 slide31
void TileLayer::Scroll(HorizScroll h, VertScroll v) {
		viewWindow.IncreaseX(h);
		viewWindow.IncreaseY(v);
}

bool TileLayer::CanScroll(HorizScroll h) const {
		return true;
		//return viewWin.x >= -(int) h && viewWin.x + ((int) h) + viewWin.w <= MAX_WIDTH;
}

bool TileLayer::CanScroll(VertScroll v) const {
	return true;
	//return viewWin.y >= -(int) v && viewWin.y + ((int) v) + viewWin.h <= MAX_HEIGHT;
}

void TileLayer::Display(Bitmap at/*, const Rect& displayArea*/) {
		assert(at);

		al_set_target_bitmap(at);
		al_clear_to_color(al_map_rgb(0,0,0));

		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_HEIGHT; j++)
						tilesBitmap->PutTile(at, i, j, GetTile(i, j));
}