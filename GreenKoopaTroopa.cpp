#include "header_files\enemies\GreenKoopaTroopa.h"

std::list<MovingAnimator*> GreenKoopa::suspending;
std::list<MovingAnimator*> GreenKoopa::running;

void GreenKoopa::Create() {
		Sprite *greenKoopaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("greenkoopaleft") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						-2, 0, 100, true, ParseMarioInfo::GetAnimationIdOf(9u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending.push_back( aMovAnimr );
				
		aMovAnimr->Start( greenKoopaSprite, aMovAnimn, GetCurrTime());			
		//aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::ArtificialIntelligence() {
		CreateGreenKoopaIfAny();
		MoveGreenKoopas();
}

void GreenKoopa::CreateGreenKoopaIfAny() {
		MovingAnimator* g = NULL;
		for(Dim i = 0; i < 15; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(Enemies::GetFromMap(y, x) == 194) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;
								if(suspending.empty()) Create();
								g = suspending.back();
								suspending.pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running.push_back(g);
						}
				}
}

void GreenKoopa::MoveGreenKoopas() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPos = g->GetSprite()->GetX();
				if(currPos < 2) {
						suspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);
						
						return ;
				}
		}
}

void GreenKoopa::ViewWindowMove() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 16);
}
