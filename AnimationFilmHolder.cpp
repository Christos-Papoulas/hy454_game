#include "header_files\animation\AnimationFilmHolder.h"

AnimationFilmHolder* AnimationFilmHolder::holder = NULL;

AnimationFilmHolder::AnimationFilmHolder(const char* path) {
		assert(path);
		BitmapLoader::Create();
		Bitmap btmp = BitmapLoader::Load(path); //path to mario.png
		//parse the info file!
		ParseMarioInfo::Create();
		ParseMarioInfo::ParseFile(MARIO_SPRITES_INFO);
		

}

AnimationFilmHolder::~AnimationFilmHolder() {
		delete holder; holder = NULL;
}

void AnimationFilmHolder::Create(const char* path) {
		if(!holder)
				holder = new AnimationFilmHolder(path);
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
