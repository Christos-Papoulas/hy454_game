#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/FrameRangeAnimation.h"
#include "../Objects.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../collision/Collision.h"
#include "../enemies/Enemies.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <list>

#define ITEMS_TYLES "data/Items_1-1.txt"

class Items {
		static std::map<std::string, std::list<MovingPathAnimator*> > suspending;
		static std::map<std::string, std::list<MovingPathAnimator*> > running;

		static Dim map[MAX_HEIGHT][MAX_WIDTH];
		static Index**	shortMap;
		static Index countItems;

		static void CreateScores();

		static Dim GetFromMap(Dim x, Dim y) { return map[x][y]; }
		static void SetOnMap(Dim value, Dim x, Dim y) { map[x][y] = value; }
		static void MoveItems();

		static void ReadMap();
		static void MakeShortMap();
		static void CreateIfAny();
		static void SetItemAsActive(Dim x, Dim y);
		static bool IsItemActive(Dim x, Dim y);
public:
		static void Init();
		static void ArtificialIntelligence();
		static void Throw100Coins(Dim x, Dim y);
		static void FinishItemAnimation(Animator*, void*);
		
};

#endif
