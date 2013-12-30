#include "header_files\animation\BitmapLoader.h"

BitmapLoader *BitmapLoader::bitmapLoader = NULL;

BitmapLoader::BitmapLoader() {
		;
}

BitmapLoader::~BitmapLoader() {
		assert(bitmapLoader); delete bitmapLoader;
}

Bitmap	BitmapLoader::Load(const std::string& path) {
		Bitmap b = NULL;

		return b;
}

void		BitmapLoader::Create() {
		if(!bitmapLoader)
				bitmapLoader = new BitmapLoader();
}

