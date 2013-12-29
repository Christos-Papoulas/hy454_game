#include "header_files\terrain\TerrainUtils.h"

byte TerrainUtils::MakeIndex(byte row, byte col) {
		return col << COL_SHIFT | row;
}

byte TerrainUtils::GetCol(byte b) {
		return b & ROW_MASK;
}

byte TerrainUtils::GetRow(byte b) {
		return b >> 4;
}

Dim TerrainUtils::TileX2(byte b) {
		return MUL_TILE_WIDTH(GetCol(b));
}

Dim TerrainUtils::TileY2(byte b) {
		return MUL_TILE_HEIGHT(GetRow(b));
}