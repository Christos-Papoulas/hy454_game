/*
 * Lecture 10 slide 17
 */

#ifndef _ANIMATIONFILMHOLDER_H_
#define _ANIMATIONFILMHOLDER_H_

#include "AnimationFilm.h"
#include "BitmapLoader.h"
#include "..\parsers\ParseMarioInfo.h"

#include <string>
#include <map>
#include <assert.h>

#define MARIO_SPRITES_BMP "./data/Bitmaps/Sprites/mario.bmp"

class AnimationFilmHolder {
		private:
				typedef std::map<std::string, AnimationFilm*> Films;
				Films						films;
				//BitmapLoader		bitmaps; //only for loading of film bitmaps
				static AnimationFilmHolder* holder; // sigleton
				AnimationFilmHolder(const char* path);
				~AnimationFilmHolder();
		
		public:
				static void Create(const char* path);
				void		CleanUp();
				void		Load(const std::string& catalogue);
				const		AnimationFilm* GetFilm (const std::string id) const;
};

#endif