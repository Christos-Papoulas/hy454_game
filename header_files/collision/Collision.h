#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Objects.h"

#define MAX_HEIGHT 15 
#define MAX_WIDTH 225

class Collision{
		private:
			Dim			Collision_map[MAX_HEIGHT][MAX_WIDTH];
		public:
			Collision();
			~Collision();
};
#endif