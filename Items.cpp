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
		SuspendBricks();
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
								}	else {
										if(suspending["questionbrick"].size() == 0)
												CreateAQuestionAnimation();
										g = (MovingAnimator* ) suspending["questionbrick"].back();
										suspending["questionbrick"].pop_back();
								}
								
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								SetBrickAsActive(y,x);
								if(brick[y][x] == 2)
										running["bricks"].push_back((Animator*) g);
								else
										running["questionbrick"].push_back((Animator*) g);
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

 void Items::SuspendBricks() {
		for (std::list<Animator*>::iterator it=running["bricks"].begin(); it != running["bricks"].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();

				if(currPosX < 2 || TileX > MAX_WIDTH || TileY >= MAX_HEIGHT -1) {
						suspending["bricks"].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running["bricks"].erase(it);
						return ;
				}
		}
		for (std::list<Animator*>::iterator it=running["questionbrick"].begin(); it != running["questionbrick"].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();

				if(currPosX < 2 || TileX > MAX_WIDTH || TileY >= MAX_HEIGHT -1) {
						suspending["questionbrick"].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running["questionbrick"].erase(it);
						return ;
				}
		}
 }

 void Items::ViewWindowMove() {
		 MovingAnimator* g;
		 for (std::list<Animator*>::iterator it=running["bricks"].begin(); it != running["bricks"].end(); ++it) {
				g = (MovingAnimator*)(*it);
				g->GetSprite()->SetX(g->GetSprite()->GetX() - 1);
		 }
		 for (std::list<Animator*>::iterator it=running["questionbrick"].begin(); it != running["questionbrick"].end(); ++it) {
				g = (MovingAnimator*)(*it);
				g->GetSprite()->SetX(g->GetSprite()->GetX() - 1);
		 }
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
		
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		AnimatorHolder::Register( aMovAnimr );
}

bool Items::BrickIsHit(Dim x, Dim y) {
	Dim mi = Mario::GetMarioCurrentSprite()->GetX();
	Dim mj = Mario::GetMarioCurrentSprite()->GetY();
	Dim i = (x > mi) ? x - mi : mi - x;
	Dim j = (y > mj) ? y - mj : mj - y;
	std::cout << "i: " << i << " j: " << j << "\n";
	if(i < COLLISION_DETECT && ((mj - y) <= 17)) //@todo the right operation is equality check
		return true;
	return false;

}

void Items::BrickCollision() {
	for (std::list<Animator*>::iterator it=running["bricks"].begin(); it != running["bricks"].end(); ++it) {
				MovingAnimator* g = ( MovingAnimator* )*it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();
				if(Mario::GetState() == Jumping)
					if(Items::BrickIsHit(x, y))
						Mario::MarioFinishSjumping(NULL,NULL);
		}
}