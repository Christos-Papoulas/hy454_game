#include "Animation.h"

void Animation::Animate(AnimationFilm& film, const Point at) {
		unsigned int t = 0;
		for(byte i = 0; i< film.GetTotalFrames(); )
				if(CurrTime() >= t)
						t = CurrTime();// + FRAME_DELAY;
						//VSync(); Clear(GetScreen());
						//film.DisplayFrame(GetScreen(), at, i++);
}
