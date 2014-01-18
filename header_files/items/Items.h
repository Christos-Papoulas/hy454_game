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
#include "../tiles/TilesBitmap.h"
#include "../collision/Collision.h"
#include "../enemies/Enemies.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <list>

#define ITEMS_TYLES "data/Items_1-1.txt"
#define BRICKS_POS "data/bricks_1-1.txt"

class Items {
		static std::map<std::string, std::list<Animator*> > suspending;
		static std::map<std::string, std::list<Animator*> > running;

		static Dim map[MAX_HEIGHT][MAX_WIDTH];
		static Dim brick[MAX_HEIGHT][MAX_WIDTH];
		static Index**	shortMap;
		static Index** shortBricks;

		static Index countBricks;
		static Index countItems;

		static void CreateScores();
		static void CreateABrickAnimation();
		static void CreateSprite(char* id, const Dim index);
		static void CreateBricks();
		static void SuspendBricks();
		static Dim GetFromMap(Dim x, Dim y) { return map[x][y]; }
		static void SetOnMap(Dim value, Dim x, Dim y) { map[x][y] = value; }
		static void MoveItems();

		static void ReadMap();
		static void ReadBrickMap();
		static void MakeShortMap();
		static void CreateIfAny();
		static void SetItemAsActive(Dim x, Dim y);
		static bool IsItemActive(Dim x, Dim y);

		static void SetOnBricks(Dim value, Dim x, Dim y) { assert(x < MAX_HEIGHT && y < MAX_WIDTH); brick[x][y] = value; }
		static Dim GetFromBricks(Dim x, Dim y) { return brick[x][y]; }
		static void MakeShortBricks();
		static bool IsBrickActive(Dim x, Dim y);
		static void SetBrickAsActive(Dim x, Dim y);

		static void CreateAQuestionAnimation();
		static void BrickCollision();
		static bool IsOnBrick(const char* id);
		static void ViewWindowMove(const char* id);
public:
		static void Init();
		static void ArtificialIntelligence();
		static void Throw100Coins(Dim x, Dim y);
		static void FinishItemAnimation(Animator*, void*);
		static void ViewWindowMove();

		static bool BrickIsHit(Dim x, Dim y);
		static bool IsMarioAboveBrick(Dim x, Dim y);
		
		
};

#endif
