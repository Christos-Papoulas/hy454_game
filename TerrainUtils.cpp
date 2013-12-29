#include "header_files\terrain\TerrainUtils.h"

byte TerrainUtils::MakeIndex(byte row, byte col) {
		return col << COL_SHIFT | row;
}

byte TerrainUtils::GetCol(byte b) {
		return b >> COL_SHIFT;
}

byte TerrainUtils::GetRow(byte b) {
		return b & ROW_MASK;
}

Dim TerrainUtils::TileX(byte b) {
		return TerrainUtils::GetCol(b)*TILE_WIDTH;
}

Dim TerrainUtils::TileY(byte b) {
		return TerrainUtils::GetRow(b)*TILE_HEIGHT;
}

Dim TerrainUtils::TileX2(byte b) {
		return MUL_TILE_WIDTH(GetCol(b));
}

Dim TerrainUtils::TileY2(byte b) {
		return MUL_TILE_HEIGHT(GetRow(b));
}