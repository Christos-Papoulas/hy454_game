/*
 * Lecture 10 slide 17
 */

#ifndef _ANIMATIONFILMHOLDER_H_
#define _ANIMATIONFILMHOLDER_H_

#include "AnimationFilm.h"
#include <string>


class AnimationFilmHolder {
		private:
				typedef std::map<std::string, AnimationFilm*> Films;
				Films films;
				BitmapLoader bitmaps; //only for loading of film bitmaps
				static AnimationFilmHolder holder; // sigleton
				AnimationFilmHolder();
				~AnimationFilmHolder();
		public:
				static const AnimationFilmHolder& Get() {return holder; }
				static AnimationFilmHolder& Get() { return holder; }
				void Load(const std::string& catalogue) {
					/*	foreach entry <id, path, vector of rects> do {
								Bitmap bmp = bitmaps.Load(path);
								assert(!Get(id);
								films[id] = new AnimationFilom(bmp, rects, id);
						} */
				}
				void CleanUp() {
						/*for(Films::iterator i = films.begin(); i != films.end(); ++i)
								delete(i->second);
						films.clear(); */
				}
				const AnimationFilm* GetFilm (const std::string id) const {
						Films::const_iterator i = films.find(id);
						return i != films.end() ? i->second : (const AnimationFilm*) 0;
				}
};

#endif