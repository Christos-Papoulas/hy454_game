#include "header_files\items\Items.h"

std::map<std::string, std::list<MovingPathAnimator*> > Items::suspending;
std::map<std::string, std::list<MovingPathAnimator*> > Items::running;

Dim Items::map[MAX_HEIGHT][MAX_WIDTH];
Index**	Items::shortMap;
Index Items::countItems;

void Items::Init() {
		ReadMap();
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

void Items::MoveItems() {
		;
}

void Items::ArtificialIntelligence() {
		CreateIfAny();
		MoveItems();	
}

void Items::SetItemAsActive(Dim x, Dim y) {
		for(Dim i = 0; i < countItems; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y) {
						shortMap[i][ISACTIVE] = 1; return ;
				}
				assert(0);
}

bool Items::IsItemActive(Dim x, Dim y) {
		for(Dim i = 0; i < countItems; i++)
				if(shortMap[i][X_INDEX] == x && shortMap[i][Y_INDEX] == y)
						return shortMap[i][ISACTIVE] == 1;
		assert(0);
		return 0;
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
		
		suspending["onehundred"].push_back( aMovAnimr );

		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(FinishItemAnimation, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Items::Throw100Coins(Dim x, Dim y) {
		MovingPathAnimator *coin = NULL;
		if(suspending["onehundred"].size() == 0)
				CreateScores();
		coin = suspending["onehundred"].back(); assert(coin);
		coin->GetSprite()->SetX(x);
		coin->GetSprite()->SetY(y);
		coin->SetLastTime(CurrTime());

		AnimatorHolder::MarkAsRunning(coin);
		running["onehundred"].push_back(coin);
		suspending["onehundred"].pop_back();
}

void Items::FinishItemAnimation(Animator* a, void* l) {
		std::list<MovingPathAnimator*>::iterator it = running["onehundred"].begin();
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