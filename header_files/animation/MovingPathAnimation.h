#ifndef _MOVINGPATHANIMATION_H_
#define _MOVINGPATHANIMATION_H_

#include "Animation.h"
#include <list>

typedef unsigned char frame_t;
// lecture 11 slide 14
struct PathEntry {
		offset_t		dx, dy;
		frame_t			frame;
		delay_t			delay;
		PathEntry () : dx(0), dy(0), frame(0xff), delay(0) {}
		PathEntry (const PathEntry& p) :
				dx(p.dx), dy(p.dy), frame(p.frame), delay(p.delay) {}
};

class MovingPathAnimation : public Animation {
		private:
				std::list<PathEntry> path;
		
		public:
				const std::list<PathEntry>& GetPath() const { return path; }
				void SetPath( const std::list<PathEntry>& p ) { path.clear(); path = p; }
				Animation* Clone(animid_t newId) const {
						return new MovingPathAnimation(path, newId);
				}
				MovingPathAnimation( const std::list<PathEntry>& path, animid_t id) :
				path(_path), Animation(id) {}
};

#endif