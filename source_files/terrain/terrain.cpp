#include "terrain.h"

Terrain* Terrain::terrain;
TileLayer* Terrain::tileLayer;

Terrain::Terrain() {
		;
}

Terrain::~Terrain() {
		assert(0 && "Unimplemented");
}

void Terrain::Create() {
		FILE* fp;
		if(!terrain) {
				terrain = new Terrain();
				terrain->tileLayer = new TileLayer();

				fp = fopen(MAP_WORLD_1_1, "r");
				if(!terrain->tileLayer->ReadMap(fp))
						fprintf(stderr, "cannot read the map 1-1 file\n");
				fclose(fp);

				CalculateTilesPosition();
		}
}

void Terrain::CleanUp() {
		delete terrain;
}

void Terrain::DisplayTerrain(Bitmap bmp, timestamp_t tnow) {
		terrain->tileLayer->Display(bmp);

		//lecture9 slide29
		/*for (Dim row = 0; row < rowend; ++row)
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