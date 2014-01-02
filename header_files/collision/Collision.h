#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Objects.h"
#include "../tiles/TileLayer.h"

class Collision{
		private:
			static Dim			Collision_map[MAX_HEIGHT][MAX_WIDTH];
			Collision();
			~Collision();
		public:
				static void Create() {  };
				static void SetValue(Dim x, Dim y, Dim value);
};
#endif