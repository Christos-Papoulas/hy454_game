#include "header_files\animation\AnimationFilmHolder.h"

AnimationFilmHolder* AnimationFilmHolder::holder = NULL;

AnimationFilmHolder::AnimationFilmHolder(const char* path) {
		assert(path);
		BitmapLoader::Create();
		Bitmap btmp = BitmapLoader::Load(path); //path to mario.png
		//parse the info file!
		ParseMarioInfo::Create();
		ParseMarioInfo::ParseFile(MARIO_SPRITES_INFO);
		Index totalFrames = ParseMarioInfo::GetTotalFrames();
		for(Index i = 0; i < totalFrames; i++) {
				MarioInfo_t mInfo = ParseMarioInfo::GetNetMarioInfo(i);
				char* cid = ParseMarioInfo::GetNetMarioInfoId(i);
				std::vector<Rect> box;
				for(Index j = 0; j < mInfo.numOfmoves; j++) {
						Rect aRect; aRect.SetX(mInfo.moves[j].y); aRect.SetY(mInfo.moves[j].y);
						box.push_back(aRect);
				}
				AnimationFilm* aAnimFilm = new AnimationFilm(btmp, box, cid);
				
		}
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
