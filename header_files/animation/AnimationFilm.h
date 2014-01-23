#ifndef _ANIMATIONFILM_H_
#define _ANIMATIONFILM_H_

#include <assert.h>
#include <vector>
#include <string>
#include "..\Objects.h"


class AnimationFilm {
		std::vector<Rect> boxes; //in the .png file
		Bitmap bitmap;
		std::string id;
public:
		AnimationFilm(Bitmap , const std::vector<Rect>, const std::string& );
		~AnimationFilm();
		byte GetTotalFrames() const { return boxes.size(); }
		Bitmap GetBitmap() const {return bitmap; }
		const std::string GetID() const { return id;} 
		const Rect GetFrameBox(byte frameNo) const {
				assert(boxes.size() > frameNo);
				return boxes[frameNo];
		}
		void SetHeightToFrame(byte frameNo, Dim height) {
				assert(boxes.size() > frameNo);
				boxes[frameNo].SetHeight(height);
		}
		byte GetFrameBoxSize(){ return boxes.size(); }
		void DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const;
};

#endif