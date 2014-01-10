#include "header_files\enemies\Goumba.h"

std::list<MovingAnimator*> Goumbas::goumba;
std::list<MovingAnimator*> Goumbas::running;

void Goumbas::Create() {
		Sprite *goumbaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("goombawalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						0, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(7u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Goumbas::goumba.push_back( aMovAnimr );
				
		aMovAnimr->Start( goumbaSprite, aMovAnimn, GetCurrTime());			
		//aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Goumbas::ArtificialIntelligence() {
		CreateGoumbaifAny();
		MoveGoumbas();		
		//if(!goumbasCount) AnimatorHolder::MarkAsSuspended(g);
}

void Goumbas::CreateGoumbaifAny() {
		MovingAnimator* g = NULL;
		for(Dim i = 0; i < 15; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(Enemies::GetFromMap(y, x) == 161) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;
								if(goumba.empty()) Create();
								g = goumba.back();
								goumba.pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running.push_back(g);
						}
				}
}

void Goumbas::MoveGoumbas() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPos = g->GetSprite()->GetX();
				if(currPos == 0) {
						goumba.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);
						
						return ;
				}
				g->GetSprite()->SetX(currPos - 1);
		}
}
