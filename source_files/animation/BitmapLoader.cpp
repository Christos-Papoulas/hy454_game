#include "BitmapLoader.h"

BitmapLoader *BitmapLoader::bitmapLoader = NULL;

BitmapLoader::BitmapLoader() {
		;
}

BitmapLoader::~BitmapLoader() {
		assert(bitmapLoader); delete bitmapLoader;
}

// @Maybe Just load the file with sprites
Bitmap	BitmapLoader::Load(const char* path) {
		Bitmap b = NULL;
		b = al_load_bitmap(path);
		assert(b);
		al_convert_mask_to_alpha(b, al_map_rgb(255, 255, 255)); // @todo the white is ok?
		return b;
}

void		BitmapLoader::Create() {
		if(!bitmapLoader)
				bitmapLoader = new BitmapLoader();
}

