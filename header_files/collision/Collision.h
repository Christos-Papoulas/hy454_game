#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../Objects.h"
#include "../tiles/TileLayer.h"
#include "Sprites.h"

class Collision{
		private:
			static Dim			Collision_map[MAX_HEIGHT][MAX_WIDTH];
			Collision();
			~Collision();
			static bool IsGravityAddicted;
			static void CheckGravity(Dim x_tile, Dim y_tile);
			static void MarioCollision(Dim x_tile, Dim y_tile);

		public:
			static void Create() {  }
			static void SetValue(Dim x, Dim y, Dim value);
			static Dim GetValue(Dim y, Dim x) {/*assert(x <= MAX_HEIGHT && y <= MAX_WIDTH);*/ return Collision_map[x][y]; }
			static void CheckCollision();
			static void SetGravity(bool x) { IsGravityAddicted = x; }
			static bool GetGravity() { return IsGravityAddicted; }
};

#endif