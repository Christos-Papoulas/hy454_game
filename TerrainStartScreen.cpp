#include "header_files\terrain\TerrainStartScreen.h"

TerrainStartScreen* TerrainStartScreen::terrainStartScreen;
TileLayerStartScreen* TerrainStartScreen::tileLayerStartScreen;

TerrainStartScreen::TerrainStartScreen() {
		;
}

TerrainStartScreen::~TerrainStartScreen() {
		assert(0 && "Unimplemented");
}


void TerrainStartScreen::Create() {
		FILE* fp_new;
		if(!terrainStartScreen) {
				terrainStartScreen = new TerrainStartScreen();
				terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

				fp_new = fopen(START_SCREEN_MAP, "r");
				if(!tileLayerStartScreen->ReadMap(fp_new))
						fprintf(stderr, "cannot read start_screen file\n");
				fclose(fp_new);

				CalculateTilesPositionStartScreen();
		}
}

void TerrainStartScreen::CreatePause() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(PAUSE_SCREEN_MAP, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CleanUp() {
		delete terrainStartScreen;
}

void TerrainStartScreen::DisplayTerrain(Bitmap bmp, timestamp_t tnow) {
		terrainStartScreen->tileLayerStartScreen->Display(bmp);
}