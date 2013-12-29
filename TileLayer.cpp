#include "header_files\tiles\TileLayer.h"


bool TileLayer::ReadMap(FILE* fp) {
		//to do
		return false;
}

//lecture9 slide 14
void TileLayer::SetTile(Dim col, Dim row, Index index) {
		map[row][col] = index;
}

Index TileLayer::GetTile(Dim col, Dim row) { 
	return map[row][col]; 
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
