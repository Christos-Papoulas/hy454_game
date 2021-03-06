#include "TerrainStartScreen.h"

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

void TerrainStartScreen::CreateLifeScreen() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(LIFE_SCREEN_MAP, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CreateLifeScreen2() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(LIFE_SCREEN2_MAP, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CreateLifeScreen1() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(LIFE_SCREEN1_MAP, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CreateBlackScreen() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(BLACK_SCREEN_MAP, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CreateGameOver() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(GAME_OVER_SCREEN, "r");
	if(!tileLayerStartScreen->ReadMap(fp_new))
		fprintf(stderr, "cannot read start_screen file\n");
	fclose(fp_new);
	CalculateTilesPositionStartScreen();
}

void TerrainStartScreen::CreateWin() {
	FILE* fp_new;
	terrainStartScreen = new TerrainStartScreen();
	terrainStartScreen->tileLayerStartScreen = new TileLayerStartScreen();

	fp_new = fopen(GAME_WIN, "r");
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