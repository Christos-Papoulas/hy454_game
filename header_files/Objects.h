#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <allegro5\allegro5.h> 

typedef unsigned char byte;
typedef unsigned short Dim;
typedef unsigned short Index; // [ MSB X ] [ LSB Y ]
typedef ALLEGRO_BITMAP* Bitmap;
typedef ALLEGRO_DISPLAY* Display;


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

};

unsigned int CurrTime();

#endif