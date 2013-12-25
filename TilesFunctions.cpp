/*void PutTile (Bitmap at, Dim x, Dim y, Bitmap tiles, Index tile) {
	blit(
	tiles, Rect(TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT),
	at, Point(x,y)
	);
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


*/