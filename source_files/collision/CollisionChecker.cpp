#include "CollisionChecker.h"

std::vector< PairWithCallback > CollisionChecker::pairs;

void CollisionChecker::Register (Sprite* s1, Sprite* s2, CollisionCallBack c){
	Pair p(s1, s2);
	PairWithCallback pc(p, c);
	pairs.push_back(pc);
}

void CollisionChecker::Cancel (Sprite* s1, Sprite* s2, CollisionCallBack c) {
	std::vector<PairWithCallback>::iterator it = std::find(pairs.begin(), pairs.end(), PairWithCallback(Pair(s1, s2), c));
	if( it == pairs.end() ) return ;
	pairs.erase(it);
}

void CollisionChecker::Check (void) {
 	std::for_each(
  			pairs.begin(), pairs.end(), CheckFunctor()
	); 
}

