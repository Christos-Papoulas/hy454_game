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
		static void Register (Sprite* s1, Sprite* s2, CollisionCallBack c){
			Pair p(s1, s2);
			PairWithCallback pc(p, c);
			pairs.push_back(pc);
		}

		static void Cancel (Sprite* s1, Sprite* s2, CollisionCallBack c) {
			std::vector<PairWithCallback>::iterator it = std::find(pairs.begin(), pairs.end(), PairWithCallback(Pair(s1, s2), c));
			pairs.erase(it);
		}

		static void Check (void) {
 			std::for_each(
  					pairs.begin(), pairs.end(), CheckFunctor()
			); 
		}
};

#endif