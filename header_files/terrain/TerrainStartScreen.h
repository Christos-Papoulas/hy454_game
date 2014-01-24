#ifndef _TERRAIN_START_SCREEN_H_
#define _TERRAIN_START_SCREEN_H_

#include <assert.h>

#include "..\Objects.h"
#include "..\animator\Animator.h"
#include "..\tiles\TileLayerStartScreen.h"
#include "..\tiles\TilesBitmapStartScreen.h"

class TerrainStartScreen {
	private:
		TerrainStartScreen();
		~TerrainStartScreen();
		static TerrainStartScreen* terrainStartScreen; //sigleton
		static TileLayerStartScreen* tileLayerStartScreen;

	public:
		static void Create();
		static void CreatePause();
		static void CreateLifeScreen();
		static void CleanUp();
		static void DisplayTerrain(Bitmap, timestamp_t);
		static TileLayerStartScreen* GetTileLayer() { return tileLayerStartScreen; }
		static TerrainStartScreen* GetTerrain() { return terrainStartScreen; }
};

#endif