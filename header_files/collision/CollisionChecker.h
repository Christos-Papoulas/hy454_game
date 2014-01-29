#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_

#include "Objects.h"
#include "Sprites.h"

#include <vector>
#include <utility>
#include <algorithm>

typedef void (*CollisionCallBack)(void);
typedef std::pair<Sprite*, Sprite*> Pair;
typedef std::pair<Pair,CollisionCallBack> PairWithCallback;

class CollisionChecker {
	static std::vector< PairWithCallback > pairs;

  struct CheckFunctor : public std::unary_function<PairWithCallback, void> {
      void operator()(const PairWithCallback& p) const { 
				if(p.first.first->CollisionCheck(p.first.second))
					p.second();
			}
  };

  public:
		static void Register (Sprite* s1, Sprite* s2, CollisionCallBack c);
		static void Cancel (Sprite* s1, Sprite* s2, CollisionCallBack c);
		static void Check (void);
};

#endif