#include "header_files\animation\AnimationFilmHolder.h"

void AnimationFilmHolder::Create(const char* path) {
		;
}

void AnimationFilmHolder::Load(const std::string& catalogue) {
//		foreach entry <id, path, vector of rects> do {
//				Bitmap bmp = bitmaps.Load(path);
//				assert(!Get(id));
//				films[id] = new AnimationFilom(bmp, rects, id);
//		} 
}

void AnimationFilmHolder::CleanUp() {
		for(Films::iterator i = films.begin(); i != films.end(); ++i)
				delete(i->second);
		films.clear(); 
}

const AnimationFilm* AnimationFilmHolder::GetFilm (const std::string id) const {
		Films::const_iterator i = films.find(id);
		return i != films.end() ? i->second : NULL;
}