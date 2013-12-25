#include "header_files\terrain\TerrainUtils.h"

byte Terrain::MakeIndex(byte row, byte col) {
		return col << COL_SHIFT | row;
}

byte Terrain::GetCol(byte b) {
		return b >> COL_SHIFT;
}

byte Terrain::GetRow(byte b) {
		return b & ROW_MASK;
}

Dim Terrain::TileX(byte b) {
		return Terrain::GetCol(b)*TILE_WIDTH;
}

Dim Terrain::TileY(byte b) {
		return Terrain::GetRow(b)*TILE_HEIGHT;
}

Dim Terrain::TileX2(byte b) {
		return MUL_TILE_WIDTH(GetCol(b));
}

Dim Terrain::TileY2(byte b) {
		return MUL_TILE_HEIGHT(GetRow(b));
}