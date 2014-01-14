#ifndef _FULL_COLLISION_H_
#define _FULL_COLLISION_H_

#include "../Objects.h"
#include "../tiles/TileLayer.h"
#include "../terrain/terrain.h"

class FullCollision {
		private:
			FullCollision();
			~FullCollision();
		public:
			static void UpdateMap();
			static void SetValue(Dim x, Dim y, Dim value);
};


#endif