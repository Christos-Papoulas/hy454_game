#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <assert.h>

#include "..\Objects.h"
#include "..\animator\Animator.h"
#include "..\tiles\TileLayer.h"
#include "..\tiles\TilesBitmap.h"


//Rect		displayArea;
//Bitmap		tileBitmap;

class Terrain {
	private:
		Terrain();
		~Terrain();
		static Terrain* terrain;
		TileLayer* tileLayer;

	public:
		static void Create();
		static void CleanUp();
		static void DisplayTerrain(Bitmap, timestamp_t);
		TileLayer* GetTileLayer() { return tileLayer; }
		static Terrain* GetTerrain() { return terrain; }
};

#endif