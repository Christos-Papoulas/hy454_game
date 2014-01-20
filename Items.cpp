#include "header_files\items\Items.h"

std::map<std::string, std::list<Animator*> > Items::suspending;
std::map<std::string, std::list<Animator*> > Items::running;

Dim Items::map[MAX_HEIGHT][MAX_WIDTH];
Index**	Items::shortMap;
Index** Items::shortBricks;
Index Items::countItems;

Index Items::countBricks;
Dim Items::brick[MAX_HEIGHT][MAX_WIDTH];

void Items::Init() {
		ReadMap();
		ReadBrickMap();
}

void Items::ReadMap() {
		using namespace std;

		ifstream read(ITEMS_TYLES);

		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j){
						Index tmp;
						read >> tmp;
						SetOnMap(tmp, i, j);
				}
		read.close();
		MakeShortMap();
}

void Items::MakeShortMap() {
		countItems = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j]) countItems++;

		shortMap = (Index**) malloc(sizeof(Index)*countItems);
		for(Dim i = 0; i < countItems; i++)
				shortMap[i] = (Index*) malloc(sizeof(Index)*3);
		
		Dim en = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j]) {
								shortMap[en][X_INDEX] = i;
								shortMap[en][Y_INDEX] = j;
								shortMap[en++][ISACTIVE] = 0;
						}
}

void Items::ReadBrickMap() { 
		using namespace std;

		ifstream read(BRICKS_POS);

		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j){
						Index tmp;
						read >> tmp;
						brick[i][j] = tmp;
				}
		read.close();
		MakeShortBricks();
}

void Items::MakeShortBricks() {
		countBricks = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(brick[i][j]) countBricks++;

		shortBricks = (Index**) malloc(sizeof(Index*)*countBricks);
		for(Dim i = 0; i < countBricks; i++)
				shortBricks[i] = (Index*) malloc(sizeof(Index)*3);
		
		Dim en = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(brick[i][j] != 0) {
								shortBricks[en][X_INDEX] = i;
								shortBricks[en][Y_INDEX] = j;
								shortBricks[en++][ISACTIVE] = 0;
						}
}


const char* strItems[] = {"bricks", "questionbrick", "leftuppipe", "leftpipe", "rightuppipe", "rightpipe",
												"solidbrick"}; // unused
void Items::CreateBricks() {
		MovingAnimator* g = NULL;
		
		for(Dim i = 0; i < VIEW_WINDOW_TILE_WIDTH; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_HEIGHT; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(brick[y][x]) {
								if(IsBrickActive(y, x)) 
										continue;
								if(brick[y][x] == 2){
										if(suspending["bricks"].size() == 0) { 
												CreateABrickAnimation();
										}
										g = (MovingAnimator* ) suspending["bricks"].back();
										suspending["bricks"].pop_back();
								}	else if(brick[y][x] == 25) {
										if(suspending["questionbrick"].size() == 0)
												CreateAQuestionAnimation();
										g = (MovingAnimator* ) suspending["questionbrick"].back();
										suspending["questionbrick"].pop_back();
								} else if(brick[y][x] == 265) {
										if(suspending["leftuppipe"].size() == 0)
												CreateSprite("leftuppipe", 16, 0, 0, 0);
										g = (MovingAnimator* ) suspending["leftuppipe"].back();
										suspending["leftuppipe"].pop_back();								
								} else if(brick[y][x] == 298) {
										if(suspending["leftpipe"].size() == 0)
												CreateSprite("leftpipe", 16, 0, 0, 0);
										g = (MovingAnimator* ) suspending["leftpipe"].back();
										suspending["leftpipe"].pop_back();								
								} else if(brick[y][x] == 266) {
										if(suspending["rightuppipe"].size() == 0)
												CreateSprite("rightuppipe", 16, 0, 0, 0);
										g = (MovingAnimator* ) suspending["rightuppipe"].back();
										suspending["rightuppipe"].pop_back();								
								} else if(brick[y][x] == 267) {
										if(suspending["leftpipe"].size() == 0)
												CreateSprite("leftpipe", 16, 0, 0, 0);
										g = (MovingAnimator* ) suspending["leftpipe"].back();
										suspending["leftpipe"].pop_back();								
								} else if(brick[y][x] == 299) {
										if(suspending["rightpipe"].size() == 0)
												CreateSprite("rightpipe", 16, 0, 0, 0);
										g = (MovingAnimator* ) suspending["rightpipe"].back();
										suspending["rightpipe"].pop_back();								
								} else if(brick[y][x] == 34) {
										if(suspending["solidbrick"].size() == 0)
												CreateSprite("solidbrick", 20, 0, 0, 0);
										g = (MovingAnimator* ) suspending["solidbrick"].back();
										suspending["solidbrick"].pop_back();		
								}
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								SetBrickAsActive(y,x);
								if(brick[y][x] == 2)
										running["bricks"].push_back((Animator*) g);
								else if(brick[y][x] == 25)
										running["questionbrick"].push_back((Animator*) g);
								else if(brick[y][x] == 265)
										running["leftuppipe"].push_back((Animator*) g);
								else if(brick[y][x] == 266)
										running["rightuppipe"].push_back((Animator*) g);
								else if(brick[y][x] == 267)
										running["leftpipe"].push_back((Animator*) g);
								else if(brick[y][x] == 299)
										running["rightpipe"].push_back((Animator*) g);
								else if(brick[y][x] == 34)
										running["solidbrick"].push_back((Animator*) g);
								else 
										running["rightpipe"].push_back((Animator*) g);
						}
				}
}

void Items::CreateABrickAnimation() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("brick") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 9000, true, ParseMarioInfo::GetAnimationIdOf(12u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending["bricks"].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateSprite(char* id, Dim index, offset_t dx, offset_t dy, Dim delay) {
		Sprite *sprite = new Sprite(20, 100,
				AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						dx, dy, (delay)?delay:10000, true, ParseMarioInfo::GetAnimationIdOf(index)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[id].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateCoinSprite(char* id) {
		Sprite * sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(id) ));
		std::vector<PathEntry> paths;
		
		for(Dim i = 0u; i < 10u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 5u) ? -6 : 6, 0, 70);
				paths.push_back( pathEntry );
		}
		
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(21u));
		aMovAnimn->SetContinuous(false);
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 

		suspending[id].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());
		aMovAnimr->SetOnFinish( FinishCoinAmimation );
		AnimatorHolder::Register( aMovAnimr );
}

void Items::FinishCoinAmimation(Animator *g, void *a) {
		std::list<Animator*>::iterator it = running["coinanimation"].begin();
		while (it != running["coinanimation"].end()){
				if((*it) == (MovingPathAnimator*)  g) {
						suspending["coinanimation"].push_back( *it );
						AnimatorHolder::MarkAsSuspended( *it );
						running["coinanimation"].erase( it );
						return ;
				}
				else
						 ++it;
		}
		return ;
}

bool Items::IsBrickActive(Dim  x, Dim y) {
		assert(x < MAX_HEIGHT && y < MAX_WIDTH);
		for(Dim i = 0; i < countBricks; i++)
				if(shortBricks[i][X_INDEX] == x && shortBricks[i][Y_INDEX] == y)
						return shortBricks[i][ISACTIVE] == 1;
		assert(0);
		return false;
}

void Items::SetBrickAsActive(Dim x, Dim y) {
		for(Dim i = 0; i < countBricks; i++)
				if(shortBricks[i][X_INDEX] == x && shortBricks[i][Y_INDEX] == y) {
						shortBricks[i][ISACTIVE] = 1; return ;
				}
				assert(0);
}

void Items::SuspendBricks(const char* id) {
		for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();

				if(currPosX < 2 || currPosX > SCREEN_WINDOW_WIDTH|| TileX > MAX_WIDTH || TileY >= MAX_HEIGHT -1) {
						suspending[id].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running[id].erase(it);
						return ;
				}
		}		
}

void Items::SuspendBricks() {
		SuspendBricks("bricks");
		SuspendBricks("questionbrick");
		SuspendBricks("leftuppipe");
		SuspendBricks("leftpipe");
		SuspendBricks("rightuppipe");
		SuspendBricks("rightpipe");
		SuspendBricks("solidbrick");
		SuspendBricks("coinanimation");
		SuspendBricks("questionfinish");
 }

 void Items::ViewWindowMove(const char* id) {
		MovingAnimator* g;
		 for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				g = (MovingAnimator*)(*it);
				g->GetSprite()->SetX(g->GetSprite()->GetX() - 1);
		 }
 }
 void Items::ViewWindowMove() {
		 ViewWindowMove("bricks");
		 ViewWindowMove("questionbrick");
		 ViewWindowMove("leftuppipe");
		 ViewWindowMove("leftpipe");
		 ViewWindowMove("rightuppipe");
		 ViewWindowMove("rightpipe");
		 ViewWindowMove("mushroom");
		 ViewWindowMove("solidbrick");
		 ViewWindowMove("coinanimation");
		 ViewWindowMove("questionfinish");
 }

void Items::MoveItems() {
		;
}

void Items::CreateIfAny() {
		MovingAnimator* g = NULL;
		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(GetFromMap(y, x) == 161) {
								if(IsItemActive(y, x)) 
										continue;
								//if(suspending.empty()) 
									//	Create();
							//	g = suspending.back();
							//	suspending.pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								SetItemAsActive(y,x);
								//running.push_back(g);
						}
				}
}

void Items::ArtificialIntelligence() {
		CreateBricks();
		CreateIfAny();
		MoveItems();
		BrickCollision();
		SuspendBricks();
}

void Items::SetItemAsActive(Dim x, Dim y) {
		for(Dim i = 0; i < countItems; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y) {
						shortMap[i][ISACTIVE] = 1; return ;
				}
				assert(0);
}

bool Items::IsItemActive(Dim x, Dim y) {
		return false;
}

void Items::CreateScores() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("onehundred") ));
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 8u; ++i) { // @todo make the code better!		
				PathEntry pathEntry((i % 2) ? -4*((i+1)/2) : +4*((i+1)/2), -2, 0, 250);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(11u));
		aMovAnimn->SetContinuous(false);
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator();
		
		suspending["onehundred"].push_back( (Animator*) aMovAnimr );

		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(FinishItemAnimation, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Items::Throw100Coins(Dim x, Dim y) {
		MovingPathAnimator *coin = NULL;
		if(suspending["onehundred"].size() == 0)
				CreateScores();
		coin = (MovingPathAnimator*)suspending["onehundred"].back(); assert((Animator*)coin);
		coin->GetSprite()->SetX(x);
		coin->GetSprite()->SetY(y);
		coin->SetLastTime(CurrTime());

		AnimatorHolder::MarkAsRunning(coin);
		running["onehundred"].push_back(coin);
		suspending["onehundred"].pop_back();
}

void Items::FinishItemAnimation(Animator* a, void* l) {
		std::list<Animator*>::iterator it = running["onehundred"].begin();
		while (it != running["onehundred"].end()){
				if((*it) == (MovingPathAnimator*)  a) {
						suspending["onehundred"].push_back( *it );
						AnimatorHolder::MarkAsSuspended( *it );
						running["onehundred"].erase( it );
						return ;
				}
				else
						 ++it;
		}
		return ;
}

void Items::CreateAQuestionAnimation() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("questionbrick") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 2, 
						0, 0, 200, true, ParseMarioInfo::GetAnimationIdOf(13u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending["questionbrick"].push_back( (Animator*) aMovAnimr );
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::ShowSolidQuestion(MovingAnimator* prevAnim, Dim x, Dim y) {
		MovingAnimator *g;
		if(suspending["questionfinish"].size() == 0)
				CreateSprite("questionfinish", 22, 0, 0, 0);
		g = (MovingAnimator* ) suspending["questionfinish"].back();
		suspending["questionfinish"].pop_back();	
		g->GetSprite()->SetX(x);
		g->GetSprite()->SetY(y);
		g->SetLastTime(CurrTime());
		AnimatorHolder::MarkAsRunning(g);
		running["questionfinish"].push_back(g);
		AnimatorHolder::MarkAsSuspended(prevAnim);
		std::list<Animator*>::iterator it = running["questionbrick"].begin();
		while (it != running["questionbrick"].end()){
				if((*it) == (MovingPathAnimator*)  g) {
						suspending["questionbrick"].push_back( *it );
						AnimatorHolder::MarkAsSuspended( *it );
						running["questionbrick"].erase( it );
						return ;
				}
				else
						 ++it;
		}
		suspending["questionbrick"].push_back(prevAnim);

}

void Items::NotifyHit(MovingAnimator* prevAnim, const char* id, Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		Dim xi = i + (x >> 4) + 1;
		Dim xj = j + (y >> 4);
		Dim res = GetFromMap(xj, xi);
		if(res == 323){
				MovingAnimator *g;
				if(suspending["mushroom"].size() == 0)
						CreateSprite("mushroom", 10, 3, 0, 120);
				g = (MovingAnimator* ) suspending["mushroom"].back();
				suspending["mushroom"].pop_back();	
				g->GetSprite()->SetX(x);
				g->GetSprite()->SetY(y - 16);
				g->SetLastTime(CurrTime());
				AnimatorHolder::MarkAsRunning(g);
				running["mushroom"].push_back(g);
				SetOnMap(0, xj, xi);
				ShowSolidQuestion(prevAnim, x, y);
		} else if(!strcmp(id, "questionbrick")){
				MovingPathAnimator* g;
				if(suspending["coinanimation"].size() == 0)
						CreateCoinSprite("coinanimation");
				g = (MovingPathAnimator* ) suspending["coinanimation"].back();
				suspending["coinanimation"].pop_back();	
				g->GetSprite()->SetX(x + 3);
				g->GetSprite()->SetY(y - 16);
				g->SetLastTime(CurrTime());
				AnimatorHolder::MarkAsRunning(g);
				running["coinanimation"].push_back(g);
				ShowSolidQuestion(prevAnim, x, y);
		}
}

bool Items::BrickIsHit(MovingAnimator* g, const char* id, Dim x, Dim y) {
	Dim mi = Mario::GetMarioCurrentSprite()->GetX();
	Dim mj = Mario::GetMarioCurrentSprite()->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	
	if(mj > y && i < COLLISION_DETECT && ((mj - y) <= 17)){ //@todo the right operation is equality check
		NotifyHit(g, id, x, y);
		return true;
	}
		
	return false;

}

bool Items::IsMarioAboveBrick(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	if((mj < y && y - mj < 16) && ( i < 16 )){ 
		return true;
	}
	return false;
}

static bool IsMarioAboveBrickPrivate(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	
	if(Mario::isWalkingJump()){
		if(y + 16 <= mj && i < 16){
			return true;
		}
	}

	if((mj < y && y - mj < 25) && ( i < 16 )){ 
		return true;
	}
	return false;
}

bool Items::IsOnBrick(const char* id) {
	bool active = false;
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();
				if(Mario::GetState() == Jumping){
					if(Items::BrickIsHit(g, id, x, y) && !Items::IsMarioAboveBrick(x,y))
						Mario::MarioFinishSjumping(NULL,NULL);
				}
				if(IsMarioAboveBrickPrivate(x, y) && 
						Mario::isWalkingJump() && 
						((MovingPathAnimator*) Mario::GetAnimator())->GetCurrIndex() > 1) {
							Mario::MarioFinishWjumping(NULL,NULL);
				}

				if(Items::IsMarioAboveBrick(x,y)) {
					Mario::SetOnBrick(true);
					active = true;
				}
		}
	return active;
}

void Items::IsByTube(const char* id) {
	bool active = false;
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Animator* marioAnimator = Mario::GetAnimator();
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();
				if(Mario::GetState() == Walking){
					if(Items::IsMarioLeft(x, y)){
						((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(0);
						break;
					}
					else{
						((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(4);
					}
					
				}
				else if(Mario::GetState() == backwalk){
					if(Items::IsMarioRight(x, y)){
						((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(0);
						break;
					}
					else {
						((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(-3);
					}
				}
		}
}

bool Items::IsMarioLeft(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	if((mi < x && x - mi < 16) && ( i < 16 ) && mj >= y){ 
		return true;
	}
	return false;
}

bool Items::IsMarioRight(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	if((mi > x && mi - x < 16) && ( i < 16 ) && mj >= y){ 
		return true;
	}
	return false;
}

void Items::BrickCollision() {
	if( !IsOnBrick("bricks") && !IsOnBrick("questionbrick") && 
		!IsOnBrick("leftuppipe") &&
		 !IsOnBrick("rightuppipe") && !IsOnBrick("solidbrick")
		)
			Mario::SetOnBrick(false);
	IsByTube("leftpipe");
	IsByTube("rightpipe");
	IsByTube("solidbrick");

	CollisionMarioWithMushroom();
}

void Items::CollisionMarioWithMushroom() {
		for (std::list<Animator*>::iterator it=running["mushroom"].begin(); it != running["mushroom"].end(); ++it) {
				MovingAnimator* g = (MovingAnimator*)*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				if(Enemies::IsMarioLeftOrRight(x, y)){
						suspending["mushroom"].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running["mushroom"].erase(it);

						Mario::SuperMario();
						return ;
				}
		}
}
