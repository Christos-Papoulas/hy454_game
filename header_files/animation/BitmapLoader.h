#ifndef _BITMAP_LOADER_H_
#define _BITMAP_LOADER_H_

#include <string>
#include <assert.h>

#include "..\Objects.h"

//Lecture10 slide19
class BitmapLoader {
		private:
				static	BitmapLoader* bitmapLoader; //singleton
				static	Bitmap	bitmaps;
				BitmapLoader();
				~BitmapLoader();
				Bitmap	GetBitmap(const std::string path);
				
		public:
				static	void		Create();

				// prefer to massively clear bitmaps at the end than
				// to destroy individual bitmaps during gameplay
				static	void		CleanUp();
				static	Bitmap	Load(const std::string& path);
};

#endif