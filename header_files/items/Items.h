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
#include "../mario/Score.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <list>

#define ITEMS_TYLES "data/Items_1-1.txt"
#define BRICKS_POS "data/bricks_1-1.txt"

class Items {
		static std::map<std::string, std::list<Animator*> > suspending;
		static std::map<std::string, std::list<Animator*> > running;
		static std::list<Animator*> toDesrtuct;
		static Dim map[MAX_HEIGHT][MAX_WIDTH]; //Items
		static Dim brick[MAX_HEIGHT][MAX_WIDTH];
		static Index**	shortMap;
		static Index** shortBricks;

		static Index countBricks;
		static Index countItems;

		static void CreateScores();
		static void CreateABrickAnimation();
		static void CreateSprite(char* id, Dim index, offset_t dx, offset_t dy, Dim delay);
		static void CreateSprite(char* id, Dim start, Dim end, offset_t dx, offset_t dy, Dim delay);
		static void CreateBricks();
		static void SuspendBricks(const char* id);

		static void KillSprites(const char* id);

		static Dim GetFromMap(Dim x, Dim y) { return map[x][y]; }
		static void SetOnMap(Dim value, Dim x, Dim y) { map[x][y] = value; }

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
		
		static void ViewWindowMove(const char* id);

		static void IsByTube(const char* id);

		static void NotifyHit(MovingAnimator* g, const char* id, Dim x, Dim y);
		static void CreateCoinSprite(char* id);
		static void ShowSolidQuestion(MovingAnimator* prevAnim, Dim x, Dim y);
		static void CollisionMarioWithMushroom();
		static void CollisionMarioWithStar();
public:
		static void Init();
		static void ArtificialIntelligence();
		static void Throw100Coins(Dim x, Dim y);
		static void FinishItemAnimation(Animator*, void*);
		static void FinishCoinAmimation(Animator *g, void *a);
		
		static void ViewWindowMove();
		static void SuspendBricks();
		
		static bool BrickIsHit(MovingAnimator* g, const char* id, Dim x, Dim y);
		static bool IsMarioAboveBrick(Dim x, Dim y);
		static bool IsMarioLeft(Dim x, Dim y);
		static bool IsMarioRight(Dim x, Dim y);
		static void KillPipes();

		static bool IsOnBrick(const char* id);
		static bool IsEnemyOnBrick(const char* id, Dim x, Dim y);

		static void CommitDestructions();
};

#endif
