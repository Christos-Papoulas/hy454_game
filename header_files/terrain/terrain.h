#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <assert.h>
#include "..\Objects.h"
#include "..\animator\Animator.h"

class Terrain {
	private:
		Terrain();
		~Terrain();
		static Terrain* terrain;

	public:
		static void Create();
		static void CleanUp();
		static void DisplayTerrain(Bitmap, timestamp_t);
};

#endif