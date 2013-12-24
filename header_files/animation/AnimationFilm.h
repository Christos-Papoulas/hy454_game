#ifndef _ANIMATIONFILM_H_
#define _ANIMATIONFILM_H_

#include <assert.h>
#include <vector>
#include <string>
#include "..\Objects.h"

class AnimationFilm {
		std::vector<Rect>		boxes;
		Bitmap							bitmap;
		std::string					id;
public:
		byte								GetTotalFrames() const { return boxes.size(); }
		Bitmap							GetBitmap() const {return bitmap; }
		const std::string		GetID() const { return id;} 
		const Rect					GetFrameBox(byte frameNo) const {
				assert(boxes.size() > frameNo);
				return boxes[frameNo];
		}
		void DisplayFrame(Bitmap d, const Point& at, byte frameNo) const;
		AnimationFilm(Bitmap, const std::vector<Rect>, const std::string& );
};

#endif