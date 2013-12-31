#include "header_files\mario\SpritesHolder.h"

SpritesHolder::SpritesHolder() {
		Sprite *spriteMario = new Sprite(100, 100, AnimationFilmHolder::GetFilm( std::string("mariowalking") ));
		//spriteMario->Display(AnimationFilmHolder::GetFilm( "mariowalking" )->GetBitmap());
}

SpritesHolder::~SpritesHolder() {
		;
}