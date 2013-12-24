#include "header_files\animation\AnimationFilm.h"

AnimationFilm::AnimationFilm(Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id) :
 bitmap(_bitmap), boxes(_boxes), id(_id)
{
		assert(!_boxes.empty() && !_id.empty());
}
