#define ROW_MASK 0x0F
#define COL_MASK 0xF0
#define COL_SHIFT 4

#include "header_files\Objects.h"
#include "header_files\MarioBrosMain.h"

byte MakeIndex (byte row, byte col ) { 
	return (col<<COL_SHIFT) | row; 
}

byte GetCol (byte index) { 
	return index >> COL_SHIFT; 
}

byte GetRow (byte index) { 
	return index & ROW_MASK; 
}

Dim TileX (byte index){ 
	return GetCol(index)*TILE_WIDTH; 
}

Dim TileY (byte index){ 
	return GetRow(index)*TILE_HEIGHT; 
}

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i) ((i)<<4)

Dim TileX2 (byte index){ 
	return MUL_TILE_WIDTH(GetCol(index)); 
}

Dim TileY2 (byte index){ 
	return MUL_TILE_HEIGHT(GetRow(index)); 
}

typedef unsigned short Index; // [MSB X][LSB Y]
#define TILEX_MASK 0xFF00
#define TILEX_SHIFT 8
#define TILEY_MASK 0x00FF

Index MakeIndex2 (byte row, byte col) { 
	return (MUL_TILE_WIDTH(col) << TILEX_SHIFT) | MUL_TILE_HEIGHT(row); 
}

byte TileX3 (Index index) { 
	return index >> TILEX_SHIFT; 
}

byte TileY3 (Index index) { 
	return index & TILEY_MASK; 
}

typedef ALLEGRO_BITMAP * Bitmap;

void PutTile (Bitmap at, Dim x, Dim y, Bitmap tiles, Index tile) {
	blit(
	tiles, Rect(TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT),
	at, Point(x,y)
	);
}


#define MAX_WIDTH 1024
#define MAX_HEIGHT  256

typedef Index TileMap[MAX_WIDTH][MAX_HEIGHT];

TileMap map;

void SetTile (Dim col, Dim row, Index index){ 
	map[row][col] = index; 
}

Index GetTile (Dim col, Dim row){ 
	return map[row][col]; 
}

void WriteMap (FILE* fp){ 
	fwrite(map, sizeof(TileMap), 1, fp); 
}


unsigned tileSolitidy[MAX_WIDTH * MAX_HEIGHT / 32 + 1];

bool IsTileSolid (Dim row, Dim col) {
	unsigned bitChunk = (row * MAX_WIDTH + col) / 32;
	unsigned bitPos = (row * MAX_WIDTH + col) % 32; 
	return tileSolitidy[bitChunk] & (1 << bitPos);
}


#define MUL_MAX_WIDTH(i) ((i)<<10) // x1024
#define MUL_MAX_HEIGHT(i) ((i)<<8) // x 256
#define DIV_32(i) ((i)>>5) // / 32
#define MOD_32(i) ((i) & 31) // % 32

bool IsTileSolid2 (Dim row, Dim col) {
	unsigned tilePos = MUL_MAX_WIDTH(row) + col;
	return tileSolitidy[DIV_32(tilePos)] & (1 << MOD_32(tilePos));
}



