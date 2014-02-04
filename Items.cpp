#include "header_files\items\Items.h"

std::map<std::string, std::list<Animator*> > Items::suspending;
std::map<std::string, std::list<Animator*> > Items::running;
std::list<Animator*> Items::toDesrtuct;
std::list<Animator*> toDesrtuctBricks;

Dim Items::map[MAX_HEIGHT][MAX_WIDTH];
Index**	Items::shortMap;
Index** Items::shortBricks;
Index Items::countItems;

Index Items::countBricks;
Dim Items::brick[MAX_HEIGHT][MAX_WIDTH];

std::list<Destruction*> Items::suspendingDestruction;
std::list<Destruction*> Items::runningDestruction;

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

		shortMap = (Index**) malloc(sizeof(Index*)*countItems);
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

void Items::CreateBricks() { //and coins!
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
								running["bricks"].push_back((Animator*) g);
						}	else if(brick[y][x] == 25) {
								if(suspending["questionbrick"].size() == 0)
										CreateAQuestionAnimation();
								g = (MovingAnimator* ) suspending["questionbrick"].back();

								suspending["questionbrick"].pop_back();
								running["questionbrick"].push_back((Animator*) g);
						} else if(brick[y][x] == 265) {
								if(suspending["leftuppipe"].size() == 0)
										CreateSprite("leftuppipe", 16, 0, 0, 0);
								g = (MovingAnimator* ) suspending["leftuppipe"].back();

								suspending["leftuppipe"].pop_back();
								running["leftuppipe"].push_back((Animator*) g);
						} else if(brick[y][x] == 298) {
								if(suspending["leftpipe"].size() == 0)
										CreateSprite("leftpipe", 16, 0, 0, 0);
								g = (MovingAnimator* ) suspending["leftpipe"].back();

								suspending["leftpipe"].pop_back();
								running["leftpipe"].push_back((Animator*) g);
						} else if(brick[y][x] == 266) {
								if(suspending["rightuppipe"].size() == 0)
										CreateSprite("rightuppipe", 16, 0, 0, 0);
								g = (MovingAnimator* ) suspending["rightuppipe"].back();

								suspending["rightuppipe"].pop_back();
								running["rightuppipe"].push_back((Animator*) g);
						} else if(brick[y][x] == 299) {
								if(suspending["rightpipe"].size() == 0)
										CreateSprite("rightpipe", 16, 0, 0, 0);
								g = (MovingAnimator* ) suspending["rightpipe"].back();

								suspending["rightpipe"].pop_back();
								running["rightpipe"].push_back((Animator*) g);										
						} else if(brick[y][x] == 34) {
								if(suspending["solidbrick"].size() == 0)
										CreateSprite("solidbrick", 20, 0, 0, 0);
								g = (MovingAnimator* ) suspending["solidbrick"].back();
										
								suspending["solidbrick"].pop_back();
								running["solidbrick"].push_back((Animator*) g);
						}
						assert(g);

						g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
						g->GetSprite()->SetY(y * 16);
						g->SetLastTime(CurrTime());
						AnimatorHolder::MarkAsRunning(g);
						SetBrickAsActive(y,x);
				}
				if(GetFromMap(y, x) == 124) {
					MovingPathAnimator* g;
					if(IsItemActive(y, x)) continue;
					std::vector<PathEntry> paths;
					for(Dim k = 0u; k < 10u; ++k) { // @todo make the code better!		
						PathEntry pathEntry(0, 0, k % 3, 80);
						paths.push_back( pathEntry );
					}
					if(suspending["coinanimation"].size() == 0)
						CreateCoinSprite("coinanimation", false);
					g = (MovingPathAnimator* ) suspending["coinanimation"].back();
					assert(g);
					suspending["coinanimation"].pop_back();	
					g->GetSprite()->SetX(j * 16);
					g->GetSprite()->SetY(i * 16);
					g->SetLastTime(CurrTime());
					g->GetAnimation()->SetPath(paths);
					g->GetAnimation()->SetContinuous(true);
					AnimatorHolder::MarkAsRunning(g);
					running["coinanimation"].push_back(g);
					SetItemAsActive(y, x);
				}
		}
}

void Items::CreateABrickAnimation() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("brick") ));
		
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 1u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, 0, 0, 1000);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariojumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
		
		suspending["bricks"].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateAJumpingBrick(MovingPathAnimator* mpa) {
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 10u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i<5) ? -2 : 2, 0, 40);
				paths.push_back( pathEntry );
		}
		mpa->GetAnimation()->SetPath(paths);
		mpa->GetAnimation()->SetContinuous(false);
		mpa->SetOnFinish(FinishMoveBrick);
}

void Items::CreateDestroyBrick(Dim x, Dim y) {
		Destruction* destr;
		suspendingDestruction.push_back( destr = new Destruction(x, y));
		AnimatorHolder::Register( destr );
}

void Items::DestroyBrick(MovingPathAnimator* prevAnim) {
		if(suspendingDestruction.size() == 0)
				CreateDestroyBrick(prevAnim->GetSprite()->GetX(), prevAnim->GetSprite()->GetY());
		Destruction* destr = suspendingDestruction.back();
		destr->Reset(prevAnim->GetSprite()->GetX(), prevAnim->GetSprite()->GetY());
		suspendingDestruction.pop_back();
		runningDestruction.push_back(destr);
		destr->SetLastTime(currTime);
		AnimatorHolder::MarkAsRunning( destr );
		
		toDesrtuctBricks.push_back(prevAnim);
}

void Items::FinishMoveBrick(Animator* a, void* v) {
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 1u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, 0, 0, 1000);
				paths.push_back( pathEntry );
		}
		((MovingPathAnimator*)a)->GetAnimation()->SetPath(paths);
}

//index is unused
void Items::CreateSprite(char* id, Dim index, offset_t dx, offset_t dy, Dim delay) {
		Sprite *sprite = new Sprite(20, 100,
				AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						dx, dy, (delay)?delay:10000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(id))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[id].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateSprite(char* id, Dim start, Dim end, offset_t dx, offset_t dy, Dim delay) {
		Sprite *sprite = new Sprite(20, 100,
				AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						start, end, 
						dx, dy, (delay)?delay:10000, true, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(id))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[id].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateSpriteWithPath(char* id, Dim start, Dim end, offset_t dx, offset_t dy, Dim delay) {
		Sprite *sprite = new Sprite(20, 100,
				AnimationFilmHolder::GetFilm( std::string(id) ));
		
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 10u) ? -3 : 3, i%4, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf(id)));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator();
		
		suspending[id].push_back( (Animator*) aMovAnimr );
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CreateCoinSprite(char* id, bool moving) {
		Sprite * sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(id) ));
		std::vector<PathEntry> paths;
		
		for(Dim i = 0u; i < 10u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, moving ? ((i < 5u) ? -6 : 6) : 0, i % 3, 80);
				paths.push_back( pathEntry );
		}
		
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(21u));
		aMovAnimn->SetContinuous(moving ? false : true);
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
		MovingAnimator* g;
		Dim currPosX, currPosY, TileX, TileY;
		for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end();) {
				g = ( MovingAnimator* )*it;
				currPosX = g->GetSprite()->GetX();
				currPosY = g->GetSprite()->GetY();

				TileX = g->GetSprite()->GetTileX();
				TileY = g->GetSprite()->GetTileY();

				if(currPosX < 2 || currPosX > 16*16 || currPosY < 2 || currPosY > 15*16 ||TileX >= MAX_WIDTH || TileY >= MAX_HEIGHT) {
						std::list<Animator*>::iterator prev = it++;
						suspending[id].push_back(*prev);
						AnimatorHolder::MarkAsSuspended(*prev);
						running[id].erase(prev);
				} else
						++it;
		}
}

void Items::KillSprites(const char* id) {
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				suspending[id].push_back(*it);
				AnimatorHolder::MarkAsSuspended(*it);
	}
	running[id].clear();
}

void Items::SuspendSprites(const char* id){
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				suspending[id].push_back(*it);
				AnimatorHolder::MarkAsSuspended(*it);
	}
}

void Items::RegenerateSprites(const char* id){
	for (std::list<Animator*>::iterator it=suspending[id].begin(); it != running[id].end(); ++it) {
				AnimatorHolder::MarkAsRunning(*it);
	}
}

void Items::KillBricks(){
	SuspendSprites("questionbrick");
	SuspendSprites("solidbrick");
	SuspendSprites("bricks");
}

void Items::RegenerateBricks(){
	RegenerateSprites("questionbrick");
	RegenerateSprites("solidbrick");
	RegenerateSprites("bricks");
}

void Items::KillPipes() {
	KillSprites("leftuppipe");
	KillSprites("leftpipe");
	KillSprites("rightuppipe");
	KillSprites("rightpipe");
}

#define NUM_OF_ITEMS 11
const char* Items::strItems[] = {
	"bricks", "questionbrick", "leftuppipe", "leftpipe", "rightuppipe", "rightpipe",
	"solidbrick", "coinanimation", "questionfinish", "mushroom", "star"
};

void Items::SuspendBricks() {
	for(Dim i= 0; i < NUM_OF_ITEMS; ++i)
		SuspendBricks(strItems[i]);
 }

 void Items::ViewWindowMove(const char* id) {
		MovingAnimator* g;
		 for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				g = (MovingAnimator*)(*it);
				g->GetSprite()->SetX(g->GetSprite()->GetX() - 1);
		 }
 }
 void Items::ViewWindowMove() {
	 for(Dim i= 0; i < NUM_OF_ITEMS; ++i)
		 ViewWindowMove(strItems[i]);
 }

void Items::ArtificialIntelligence() {
		CreateBricks();
		BrickCollision();
		MoveStars();
		CoinCollision();
}

void Items::SetItemAsActive(Dim x, Dim y) {
		for(Dim i = 0; i < countItems; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y) {
						shortMap[i][ISACTIVE] = 1; return ;
				}
				assert(0);
}

bool Items::IsItemActive(Dim x, Dim y) {
		assert(x <= MAX_HEIGHT && y <= MAX_WIDTH);
		for(Dim i = 0; i < countItems; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y)
						return shortMap[i][ISACTIVE] == 1;
		assert(0);
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
		Score::ScoreAdd(100);
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
		
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 3u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, 0, i%3, 1000);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariojumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator(); 
				
		suspending["questionbrick"].push_back( (Animator*) aMovAnimr );
		aMovAnimn->SetContinuous(false);
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

void Items::CommitDestructions() {
		for (std::list<Animator*>::iterator del=toDesrtuct.begin(); del != toDesrtuct.end(); ++del) {
				std::list<Animator*>::iterator it = running["questionbrick"].begin();
				while (it != running["questionbrick"].end()){
						if((*it) == (MovingPathAnimator*)  *del) {
								suspending["questionbrick"].push_back( *it );
								AnimatorHolder::MarkAsSuspended( *it );
								running["questionbrick"].erase( it );
								return ;
						}
						else
								 ++it;
				}
		}
		toDesrtuct.clear();
}

void Items::CommitDestructions(char* id) {
	for (std::list<Animator*>::iterator del=toDesrtuctBricks.begin(); del != toDesrtuctBricks.end(); ++del) {
		std::list<Animator*>::iterator it = running[id].begin();
		while (it != running[id].end()){
			if((*it) == (MovingPathAnimator*)  *del) {
				std::list<Animator*>::iterator prev = it++;
				suspending[id].push_back(*prev);
				AnimatorHolder::MarkAsSuspended(*prev);
				running[id].erase(prev);
			}
			else
					++it;
			}
	}
	toDesrtuctBricks.clear();
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
		toDesrtuct.push_back(prevAnim);
}

void Items::NotifyHit(Animator* prevAnim, const char* id, Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		Dim xi = i + (x >> 4) + 1;
		Dim xj = j + (y >> 4);
		Dim res = GetFromMap(xj, xi);
		Dim brick =  GetFromBricks(xj, xi - 1);
		FrameRangeAnimator* fra = dynamic_cast<FrameRangeAnimator*>(prevAnim);
		MovingPathAnimator* mpa = dynamic_cast<MovingPathAnimator*>(prevAnim);

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
				ShowSolidQuestion((MovingAnimator*)prevAnim, x, y);
				Sounds::Play("powerup_appears");
		}else if(res == 29){
				CreateSpriteWithPath("star", 0, 3, 0, 0, 100);
				MovingPathAnimator* star = (MovingPathAnimator*) suspending["star"].back();
				assert(star);
				star->GetSprite()->SetX(x+3);
				star->GetSprite()->SetY(y-16);
				suspending["star"].pop_back();
				running["star"].push_back(star);
				AnimatorHolder::MarkAsRunning(star);
				SetOnMap(0, xj, xi);
				Sounds::Play("powerup_appears");
		}else if(!strcmp(id, "questionbrick")){
				MovingPathAnimator* g;
				if(suspending["coinanimation"].size() == 0)
						CreateCoinSprite("coinanimation", true);
				g = (MovingPathAnimator* ) suspending["coinanimation"].back();
				suspending["coinanimation"].pop_back();	
				std::vector<PathEntry> paths;
				for(Dim k = 0u; k < 10u; ++k) { // @todo make the code better!		
					PathEntry pathEntry(0, k < 5 ? -6 : 6, k % 3, 80);
					paths.push_back( pathEntry );
				}
				g->GetSprite()->SetX(x + 3);
				g->GetSprite()->SetY(y - 16);
				g->SetLastTime(CurrTime());
				g->GetAnimation()->SetPath(paths);
				AnimatorHolder::MarkAsRunning(g);
				running["coinanimation"].push_back(g);
				ShowSolidQuestion((MovingAnimator*)prevAnim, x, y);
				Coins::CheckCoins();
				Score::ScoreAdd(200);
				Sounds::Play("coin");
		} else if(mpa ) {
				if(Mario::IsSuperMario() || Mario::IsInvincibleSuper()){
						DestroyBrick( (MovingPathAnimator*) prevAnim);
				} else
						CreateAJumpingBrick((MovingPathAnimator*)prevAnim);
		}
		
}

bool Items::BrickIsHit(Animator* g, const char* id, Dim x, Dim y) {
	Dim mi = Mario::GetMarioCurrentSprite()->GetX();
	Dim mj = Mario::GetMarioCurrentSprite()->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	Dim j = (y > mj) ? y - mj : mj - y;
	if(mj > y && i < (COLLISION_DETECT + 3 )&& (j <= 17)){ //@todo the right operation is equality check
		NotifyHit(g, id, x, y);
		Sounds::Play("hit_brick");
		return true;
	}
		
	return false;

}

bool Items::IsMarioAboveBrick(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	Dim mheight = Mario::GetMarioCurrentSprite()->GetFrameBox().GetHeight();
	if((mj < y && y - mj < mheight) && ( i < 16 )){ 
		return true;
	}
	return false;
}

static bool IsMarioAboveBrickPrivate(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	Dim mheight = m->GetFrameBox().GetHeight();
	if((mj < y && y - mj < 9+mheight) && ( i < 16 )){ 
		return true;
	}
	return false;
}

bool Items::IsOnBrick(const char* id) {
	bool active = false;
	// this function genarates segmentation fault
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); it != running[id].end() && ++it != running[id].end()) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();
				if(Mario::GetState() == Jumping ){
					if(Items::BrickIsHit(g, id, x, y))
						Mario::MarioFinishSjumping(NULL,NULL);
					return active;
				}

				if(IsMarioAboveBrickPrivate(x, y) && 
						(Mario::isWalkingJump() || Mario::isBackJumping()) && 
						((MovingPathAnimator*) Mario::GetAnimator())->GetCurrIndex() > 1) {
							if(Mario::isWalkingJump())
									Mario::MarioFinishWjumping(NULL,NULL);
							else
								Mario::MarioFinishBackJump(0, 0);
				}
				if(Items::BrickIsHit(g, id, x, y) && 
						(Mario::isWalkingJump() || Mario::isBackJumping()) && 
						((MovingPathAnimator*) Mario::GetAnimator())->GetCurrIndex() > 1) {
							if(Mario::isWalkingJump())
									Mario::MarioFinishWjumping(NULL,NULL);
							else
								Mario::MarioFinishBackJump(0, 0);
							return active;
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
				Dim mi = Mario::GetMarioCurrentSprite()->GetX();
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
					if(mi > x){
						if(Items::IsMarioRight(x, y)){
							((MovingAnimator*) marioAnimator)->GetMovingAnimation()->SetDx(0);
							break;
						}
					}
				}
		}
}

bool Items::IsMarioLeft(Dim x, Dim y) {
	Sprite* m = Mario::GetMarioCurrentSprite();
	Dim mi = m->GetX();
	Dim mj = m->GetY();
	if(Mario::IsSuperMario() || Mario::IsInvincibleSuper()){
		mj += 16;
		mi +=5;
	}
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
	if(Mario::IsSuperMario() || Mario::IsInvincibleSuper()){
		mj += 16;
		mi -= 8;
	}
	Dim i = (x > mi) ? x - mi : mi - x;
	if((mi > x && mi - x < 16) && ( i < 16 ) && mj >= y){ 
		return true;
	}
	return false;
}

void Items::BrickCollision() {
	if( !IsOnBrick("bricks") && !IsOnBrick("questionbrick") && 
		!IsOnBrick("leftuppipe") && !IsOnBrick("questionfinish") &&
		 !IsOnBrick("rightuppipe") && !IsOnBrick("solidbrick")
		)
			Mario::SetOnBrick(false);

  IsByTube("leftpipe");
  IsByTube("rightpipe");
  IsByTube("solidbrick");

	CollisionMarioWithMushroom();
	CollisionMarioWithStar();
}

bool Items::IsMarioOnBrick(){
		if( IsOnBrick("bricks") || IsOnBrick("questionbrick") || 
		IsOnBrick("leftuppipe") || IsOnBrick("questionfinish") ||
		  IsOnBrick("rightuppipe") || IsOnBrick("solidbrick")
		)
				return true;
		return false;
}

bool Items::IsEnemyOnBrick(const char* id, Dim x, Dim y){
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
			MovingAnimator *g = (MovingAnimator *) (*it);
			Dim gx = g->GetSprite()->GetX();
			Dim gy = g->GetSprite()->GetY();

			Dim i = (x > gx) ? x - gx : gx - x;
			if(y < gy && gy - y < 16 && i < 16)
					return true;
	}
	return false;
}

void Items::CollisionMarioWithMushroom() {
		for (std::list<Animator*>::iterator it=running["mushroom"].begin(); it != running["mushroom"].end(); ++it) {
				MovingAnimator* g = (MovingAnimator*)*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();
				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				if(Enemies::IsMarioLeftOrRight(x, y)){
						suspending["mushroom"].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running["mushroom"].erase(it);
						if(!Mario::IsInvincibleSuper())
							Mario::SuperMario();
						else if(Mario::IsInvincibleSmall())
							Mario::SetSuperAsInvincible();
						Score::ScoreAdd(1000);
						Sounds::Play("powerup");
						return ;
				}
				if(Enemies::CanGoLeft(TileX, TileY) && g->GetMovingAnimation()->GetDx() < 0)
						g->GetMovingAnimation()->SetDx(-2);
				else if(!Enemies::CanGoLeft(TileX, TileY) && g->GetMovingAnimation()->GetDx() < 0)
						g->GetMovingAnimation()->SetDx(2);
				else if( Enemies::CanGoRight(TileX, TileY) && g->GetMovingAnimation()->GetDx() > 0)
						g->GetMovingAnimation()->SetDx(2);
				else if( !Enemies::CanGoRight(TileX, TileY) && g->GetMovingAnimation()->GetDx() > 0)
						g->GetMovingAnimation()->SetDx(-2);
				else
						g->GetMovingAnimation()->SetDx(0);

				if( Enemies::IsOnAir(TileX, TileY, 0) && !Enemies::IsOnBrick(x, y)) 
						g->GetMovingAnimation()->SetDy(3);
				else
						g->GetMovingAnimation()->SetDy(0);
		}
}

void Items::CollisionMarioWithStar() {
		for (std::list<Animator*>::iterator it=running["star"].begin(); it != running["star"].end(); ++it) {
				MovingAnimator* g = (MovingAnimator*)*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				if(Enemies::IsMarioLeftOrRight(x, y)){
						suspending["star"].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running["star"].erase(it);
						Mario::SetMarioAsInvincible();
						Score::ScoreAdd(1000);
						Sounds::Play("powerup");
						Sounds::Pause("music");
						Sounds::Play("Invincible");
						return ;
				}
		}
}

void Items::MoveStars() {
		for (std::list<Animator*>::iterator it=running["star"].begin(); it != running["star"].end(); ++it){
				MovingPathAnimator* g = (MovingPathAnimator*)*it;
				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				Dim dx = g->GetSprite()->GetX();

				int currIndex = g->GetCurrIndex();
				break;		
				if(Enemies::CanGoLeft(TileX, TileY) && dx < 0)
						g->GetAnimation()->SetOnPath(currIndex, -2);
				else if(!Enemies::CanGoLeft(TileX, TileY) && dx < 0)
						g->GetAnimation()->SetOnPath(currIndex, 2);
				else if( Enemies::CanGoRight(TileX, TileY) && dx > 0)
						g->GetAnimation()->SetOnPath(currIndex, 2);
				else if( !Enemies::CanGoRight(TileX, TileY) && dx > 0)
						g->GetAnimation()->SetOnPath(currIndex, -2);
				else
						g->GetAnimation()->SetOnPath(currIndex, 0);
				
				
		}
}
 
void Destruction::FinishDestroy(Animator* a, void* v) {
		AnimatorHolder::MarkAsSuspended(a);
		Items::suspendingDestruction.push_back((Destruction*) a);
		((Destruction*) a)->SetCurrIndex(0);
		std::list<Destruction*>::iterator it = Items::runningDestruction.begin();
		while (it != Items::runningDestruction.end()){
				if((*it) == (Destruction*)  a) {
						Items::runningDestruction.erase( it );
						return ;
				}
				else
						 ++it;
		}
}

void Items::ReactivateItems(Dim x) {
		Dim en = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(map[i][j]) {
								shortMap[en][X_INDEX] = i;
								shortMap[en][Y_INDEX] = j;
								shortMap[en++][ISACTIVE] = 0;
						}
		en = 0;
		for(Dim i = 0; i < MAX_HEIGHT; ++i)
				for(Dim j = 0; j < MAX_WIDTH; ++j)
						if(brick[i][j] != 0) {
								shortBricks[en][X_INDEX] = i;
								shortBricks[en][Y_INDEX] = j;
								shortBricks[en++][ISACTIVE] = 0;
						}
		KillPipes();
		KillSprites("bricks");
		KillSprites("questionbrick");
		KillSprites("solidbrick");
}

void Items::CoinCollision() {
	Dim mx = Mario::GetMarioCurrentSprite()->GetX();
	Dim my = Mario::GetMarioCurrentSprite()->GetY();
	Dim mw = Mario::GetMarioCurrentSprite()->GetFrameBox().GetWidth();
	Dim mh = Mario::GetMarioCurrentSprite()->GetFrameBox().GetHeight();
	Dim x, y, w, h;
	std::list<Animator*>::iterator it = running["coinanimation"].begin();
	while (it != running["coinanimation"].end()){
		x = ((MovingPathAnimator*)*it)->GetSprite()->GetX();
		y = ((MovingPathAnimator*)*it)->GetSprite()->GetY();
		w = ((MovingPathAnimator*)*it)->GetSprite()->GetFrameBox().GetWidth();
		h = ((MovingPathAnimator*)*it)->GetSprite()->GetFrameBox().GetHeight();
		if(  ( ( mx <= x && x <= (mx + mw) ) || ( x <= mx && mx <= (x + w) ) ) 
						&&
				 ( ( my <= y && y <= (my + mh) ) || ( y <= my && my <= (y + h) ) )
			) {
				suspending["coinanimation"].push_back( *it );
				AnimatorHolder::MarkAsSuspended( *it );
				running["coinanimation"].erase( it );
				Coins::CheckCoins();
				Score::ScoreAdd(200);
				Sounds::Play("coin");
				return ;
		}
		else
					++it;
	}
	return ;
}

bool Items::IsPipeOnLeft(Sprite* En) {
	char *id = "rightpipe";
	Dim PipeX;
	Dim EnX = En->GetX();
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
		PipeX = ((MovingAnimator*) *it)->GetSprite()->GetX();
		
		if(EnX > PipeX)
			continue;
		else {
			return Sprite::Overlap(En, ((MovingAnimator*) *it)->GetSprite());
		}
	}
	return false;
}

bool Items::IsPipeOnRight(Sprite *En) {
	char *id = "leftpipe";
	Dim PipeX;
	Dim EnX = En->GetX();
	for (std::list<Animator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
		PipeX = ((MovingAnimator*) *it)->GetSprite()->GetX();
		
		if(PipeX > EnX)
			continue;
		else {
			return Sprite::Overlap(En, ((MovingAnimator*) *it)->GetSprite());
		}
	}
	return false;
}

void Items::SuspendCoinsUnderGround() {
	std::vector<PathEntry> paths;
	for(Dim i = 0u; i < 10u; ++i) { // @todo make the code better!		
			PathEntry pathEntry(0, (i < 5u) ? -6 : 6, i % 3, 80);
			paths.push_back( pathEntry );
	}

	for (std::list<Animator*>::iterator it=running["coinanimation"].begin(); it != running["coinanimation"].end(); ++it) {
		MovingPathAnimator* g = ( MovingPathAnimator* )*it;
		g->SetCurrIndex(0);
		g->GetAnimation()->SetContinuous(false);
		g->GetAnimation()->SetPath(paths);
		suspending["coinanimation"].push_back(g);
		AnimatorHolder::MarkAsSuspended(g);
	}
	running["coinanimation"].clear();
}