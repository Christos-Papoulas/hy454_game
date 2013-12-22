#ifndef _OBJECTS_H_
#define _OBJECTS_H_

typedef unsigned char byte;
typedef unsigned int Dim;
typedef unsigned char Index;

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

				void SetX(Dim _x) : x(_x) { }
				void SetY(Dim _y) : y(_y) { }
};

#endif