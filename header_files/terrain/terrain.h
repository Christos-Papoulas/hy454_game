#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <assert.h>

#include "..\Objects.h"
#include "..\animator\Animator.h"
#include "..\tiles\TileLayer.h"
#include "..\tiles\TilesBitmap.h"

class Terrain {
	private:
		Terrain();
		~Terrain();
		static Terrain* terrain; //sigleton
		static TileLayer* tileLayer;

	public:
		static void Create();
		static void CleanUp();
		static void DisplayTerrain(Bitmap, timestamp_t);
		static TileLayer* GetTileLayer() { return tileLayer; }
		static Terrain* GetTerrain() { return terrain; }
};

#endif