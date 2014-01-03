#ifndef _MOVINGPATHANIMATION_H_
#define _MOVINGPATHANIMATION_H_

#include "Animation.h"
#include <vector>

typedef unsigned char frame_t;

// lecture 11 slide 14
struct PathEntry {
		offset_t		dx, dy;
		frame_t			frame;
		delay_t			delay;
		PathEntry () : dx(0), dy(0), frame(0xff), delay(0) {}
		PathEntry (int _dx, int _dy, frame_t _frame, delay_t _delay) 
				:	dx(_dx), dy(_dy), frame(_frame),delay(_delay) {}
		PathEntry (const PathEntry& p) :
				dx(p.dx), dy(p.dy), frame(p.frame), delay(p.delay) {}
};

class MovingPathAnimation : public Animation {
		private:
				std::vector<PathEntry>		path;
				bool											continuous;
		public:
				MovingPathAnimation( const std::vector<PathEntry>& _path, animid_t id) :
				path(_path), Animation(id) {}

				const std::vector<PathEntry>& GetPath() const { return path; }
				void SetPath( const std::vector<PathEntry>& p ) { path.clear(); path = p; }
				Animation* Clone(animid_t newId) const {
						return new MovingPathAnimation(path, newId);
				}
				bool GetContinuous() const { return continuous; }
				void SetContinuous(bool v) { continuous = v; }
};

#endif