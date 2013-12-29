#ifndef _TERRAINUTILS_H_
#define _TERRAINUTILS_H_


#include "..\Objects.h"

// lecture9 slide11
#define ROW_MASK 0x0F
#define COL _MAS 0XF0
#define COL_SHIFT 4

#define MUL_TILE_WIDTH(i)		((i)<<4)
#define MUL_TILE_HEIGHT(i)	((i)<<4)

#define TILE_WIDTH 16 //@todo is this value real? YES
#define TILE_HEIGHT 16 //@todo is this value real? YES

namespace TerrainUtils {
		extern byte MakeIndex (byte row, byte col);
		extern byte GetCol (byte b);
		extern byte GetRow (byte b);
		extern Dim TileX (byte b);
		extern Dim TileY (byte b);
		extern Dim TileX2 (byte b);
		extern Dim TileY2 (byte b);
}

#endif