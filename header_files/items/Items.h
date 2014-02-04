#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "../animator/MovingAnimator.h"
#include "../animator/FrameRangeAnimator.h"
#include "../animator/MovingPathAnimator.h"
#include "../animator/AnimatorHolder.h"
#include "../animation/AnimationFilmHolder.h"
#include "../animation/MovingPathAnimation.h"
#include "../animation/FrameRangeAnimation.h"
#include "../Objects.h"
#include "../terrain/terrain.h"
#include "../tiles/TileLayer.h"
#include "../tiles/TilesBitmap.h"
#include "../collision/Collision.h"
#include "../enemies/Enemies.h"
#include "../mario/Score.h"
#include "../sounds/Sounds.h"
#include "DestructionAnimation.h"

#include <stdlib.h>
#include <string>
#include <map>
#include <list>


#define ITEMS_TYLES "data/Items_1-1.txt"
#define BRICKS_POS "data/bricks_1-1.txt"

#define DESTROY_BRICK "brickbreak"

class Items {
		static std::map<std::string, std::list<Animator*> > suspending;
		static std::map<std::string, std::list<Animator*> > running;

		static std::list<Destruction*> suspendingDestruction;
		static std::list<Destruction*> runningDestruction;

		static std::list<Animator*> toDesrtuct;
		static Dim map[MAX_HEIGHT][MAX_WIDTH]; //Items
		static Dim brick[MAX_HEIGHT][MAX_WIDTH];
		static Index**	shortMap;
		static Index** shortBricks;

		static Index countBricks;
		static Index countItems;

		static const char* strItems[];

		static void CreateScores();
		static void CreateABrickAnimation();
		static void CreateSprite(char* id, Dim index, offset_t dx, offset_t dy, Dim delay);
		static void CreateSprite(char* id, Dim start, Dim end, offset_t dx, offset_t dy, Dim delay);
		static void CreateSpriteWithPath(char* id, Dim start, Dim end, offset_t dx, offset_t dy, Dim delay);
		static void CreateBricks();
		static void CreateDestroyBrick(Dim x, Dim y);
		static void SuspendBricks(const char* id);

		static void KillSprites(const char* id);
		static void SuspendSprites(const char* id);
		static void RegenerateSprites(const char* id);

		static Dim GetFromMap(Dim x, Dim y) { return map[x][y]; }
		static void SetOnMap(Dim value, Dim x, Dim y) { map[x][y] = value; }

		static void ReadMap();
		static void ReadBrickMap();
		static void MakeShortMap();
		
		static void SetItemAsActive(Dim x, Dim y);
		static bool IsItemActive(Dim x, Dim y);

		static void SetOnBricks(Dim value, Dim x, Dim y) { assert(x < MAX_HEIGHT && y < MAX_WIDTH); brick[x][y] = value; }
		
		static void MakeShortBricks();
		static bool IsBrickActive(Dim x, Dim y);
		static void SetBrickAsActive(Dim x, Dim y);

		static void CreateAQuestionAnimation();
		static void BrickCollision();
		
		static void ViewWindowMove(const char* id);

		static void IsByTube(const char* id);

		static void NotifyHit(Animator* g, const char* id, Dim x, Dim y);
		static void CreateCoinSprite(char* id, bool moving);
		static void CoinCollision();
		static void ShowSolidQuestion(MovingAnimator* prevAnim, Dim x, Dim y);
		static void CollisionMarioWithMushroom();
		static void CollisionMarioWithStar();
		static void MoveStars();

		static void CreateAJumpingBrick(MovingPathAnimator* mpa);
		friend void Destruction::FinishDestroy(Animator* a, void* v);
public:
		static void Init();
		static void ArtificialIntelligence();
		static void Throw100Coins(Dim x, Dim y);
		static void FinishItemAnimation(Animator*, void*);
		static void FinishCoinAmimation(Animator *g, void *a);
		
		static void ViewWindowMove();
		static void SuspendBricks();

		static Dim GetFromBricks(Dim x, Dim y) { return brick[x][y]; }
		
		static bool BrickIsHit(Animator* g, const char* id, Dim x, Dim y);
		static bool IsMarioAboveBrick(Dim x, Dim y);
		static bool IsMarioLeft(Dim x, Dim y);
		static bool IsMarioRight(Dim x, Dim y);
		static void KillPipes();
		static void KillBricks();
		static void RegenerateBricks();

		static bool IsOnBrick(const char* id);
		static bool IsEnemyOnBrick(const char* id, Dim x, Dim y);

		static void CommitDestructions();
		static void CommitDestructions(char* id);

		static void FinishMoveBrick(Animator* a, void* v);

		static void DestroyBrick(MovingPathAnimator* prevAnim);
		static void FinishDestroy(Animator* a, void* v);

		static void ReactivateItems(Dim x);
		static bool IsMarioOnBrick();
		static bool IsPipeOnLeft(Sprite *En);
		static bool IsPipeOnRight(Sprite *En);

		static void SuspendCoinsUnderGround();
};

#endif
