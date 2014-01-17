#include "header_files\enemies\GreenKoopaTroopa.h"

std::list<MovingAnimator*> GreenKoopa::suspending;
std::list<MovingAnimator*> GreenKoopa::running;
std::list<MovingAnimator*> GreenKoopa::dead;

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
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running.push_back(g);
						}
				}
}

void GreenKoopa::ComeOutFromShell(Animator* a, void* v) {
		MovingAnimator* g;

		AnimatorHolder::MarkAsSuspended(a);
		AnimatorHolder::Cancel(a);
		dead.push_back((MovingAnimator*)a);

		if(suspending.empty()) Create();
		g = suspending.back();
		suspending.pop_back();
		assert(g);
		g->GetSprite()->SetX( ((MovingAnimator*) a)->GetSprite()->GetX() );
		g->GetSprite()->SetY( ((MovingAnimator*) a)->GetSprite()->GetY() - 16 );
		g->SetLastTime(CurrTime());
		AnimatorHolder::MarkAsRunning(g);

		running.push_back(g);
}

void GreenKoopa::Dead() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("greenkoopahit") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 3000, false, ParseMarioInfo::GetAnimationIdOf(14u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		dead.push_back( aMovAnimr );
				
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(ComeOutFromShell, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::MoveGreenKoopas() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPos = g->GetSprite()->GetX();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				
				if(currPos < 2 || TileX > MAX_WIDTH) {
						suspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);
						
						return ;
				}

				if(Enemies::IsMarioAbove(TileX, TileY)){
						MovingAnimator* d; Dim x, y;
						if(dead.size() == 0) 
								Dead();
						d = dead.back();
						if(!d) return ;
						d->GetSprite()->SetX(x = g->GetSprite()->GetX());
						d->GetSprite()->SetY(y = g->GetSprite()->GetY() + 16);
						d->SetLastTime(CurrTime());
						AnimatorHolder::MarkAsRunning(d);

						suspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);

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
				Rect r = g->GetSprite()->GetCurrFilm()->GetFrameBox(g->GetSprite()->GetFrame());
				Dim f = r.GetHeight();
				if( Enemies::IsOnAir(TileX, TileY, f) ) 
						g->GetMovingAnimation()->SetDy(1);
				else
						g->GetMovingAnimation()->SetDy(0);
		}
}

void GreenKoopa::ViewWindowMove() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
}
