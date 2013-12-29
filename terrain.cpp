#include "header_files\terrain\terrain.h"

Terrain* Terrain::terrain;

Terrain::Terrain() {
		assert(0 && "Unimplemented");
}

Terrain::~Terrain() {
		assert(0 && "Unimplemented");
}

void Terrain::Create() {
		FILE* fp;
		terrain = new Terrain();
		TileLayer *tileLayerinstance = new TileLayer();

		fp = fopen(MAP_WORLD_1_1, "r");
		//if(tileLayer->ReadMap(fp))
				fprintf(stderr, "cannot read the map 1-1 file\n");
		fclose(fp);
}

void Terrain::CleanUp() {
		delete terrain;
}

void Terrain::DisplayTerrain(Bitmap bmp, timestamp_t tnow) {
		assert(0 && "Unimplemented");
		//lecture9 slide29
		/*
		for (Dim row = 0; row < viewWin.h; ++row)
				for (Dim col = 0; col < viewWin.w; ++col)
						PutTile(
								GetScreen(),
								displayArea.x + MUL_TILE_WIDTH(col),
								displayArea.y + MUL_TILE_HEIGHT(row),
								tileBitmap,
								map[row+ viewWin.y][col+ viewWin.x]
						);
		*/
}