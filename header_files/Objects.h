#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <allegro5\allegro5.h> 

// All the useful defines!

#define TILES_COLUMNS 33
#define TILES_ROWS 28u

//Define file paths
#define MAP_WORLD_1_1		"data\\map_1-1.txt"

typedef unsigned char byte;
typedef unsigned short Dim;
typedef unsigned short Index; // [ MSB X ] [ LSB Y ]
typedef ALLEGRO_BITMAP* Bitmap;
typedef ALLEGRO_DISPLAY* Display;

extern Dim divIndex[TILES_COLUMNS*TILES_ROWS + 1];
extern Dim modIndex[TILES_COLUMNS*TILES_ROWS + 1];

//lecture9 slide31
enum HorizScroll { Left = -1, HorizIntact = 0, Right = +1 };
enum VertScroll{ Up = -1, VertIntact = 0, Down = +1 };

class Point {
		Dim x;
		Dim y;
		
		public:
				Point() : x(0), y(0) { }
				Point(Dim _x, Dim _y) : x(_x), y(_y) { }
				Point ( const Point & a ) { x = a.GetX(); y = a.GetY(); }

				~Point() { x = 0; y = 0; }

				Dim GetX() const { return x; } 
				Dim GetY() const { return y; }

				void SetX(Dim _x) { x = _x; }
				void SetY(Dim _y) { y = _y; }
};

class Rect {
		Point loc;
		Point wh;
		public:
				void SetX(Dim x) { loc.SetX(x); }
				void SetY(Dim y) { loc.SetY(y); }
				void SetHeight(Dim x) { wh.SetX(x); }
				void SetWidth(Dim y) { wh.SetY(y); }
				Dim GetX() { return loc.GetX(); }
				Dim GetY() { return loc.GetY(); }
				Dim GetHeight() { return wh.GetX(); }
				Dim GetWidth() { return wh.GetY(); }
				void IncreaseX(Dim x) { loc.SetX(loc.GetX() + x); }
				void IncreaseY(Dim y) { loc.SetY(loc.GetY() + y); }
};

void CalculateTilesPosition();

unsigned int CurrTime();
void SetGameTime();

#endif