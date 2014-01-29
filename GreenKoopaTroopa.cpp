#include "header_files\enemies\GreenKoopaTroopa.h"

std::list<MovingAnimator*> GreenKoopa::suspending;
std::list<MovingAnimator*> GreenKoopa::running;
std::list<MovingAnimator*> GreenKoopa::suspendingdead;
std::list<MovingAnimator*> GreenKoopa::walkingdead;
Dim GreenKoopa::delay = 100;

void GreenKoopa::Create(const char* id) {
		Sprite *greenKoopaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						-2, 0, delay, true, ParseMarioInfo::GetIndexOf(id)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending.push_back( aMovAnimr );
				
		aMovAnimr->Start( greenKoopaSprite, aMovAnimn, GetCurrTime());			
		//aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::ArtificialIntelligence() {
		CreateGreenKoopaIfAny();
		MoveKoopasInShells();
		MoveGreenKoopas();
		KoopasKillMario();
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
								if(suspending.empty()) Create("greenkoopaleft");
								g = suspending.back();

								suspending.pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running.push_back(g);
						} else if(Enemies::GetFromMap(y, x) == 195) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;
								if(suspending.empty()) Create("redkoopaleft");
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

void GreenKoopa::MoveKoopasInShells() {
		for (std::list<MovingAnimator*>::iterator it=walkingdead.begin(); it != walkingdead.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();
				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				if(g->GetMovingAnimation()->GetDx() != 0)
						Goumbas::CollicionWithKoopaInShells(currPosX, currPosY);
				if(Enemies::IsMarioLeft(currPosX, currPosY)) {
						g->GetMovingAnimation()->SetDx(4);
						g->GetMovingAnimation()->SetDelay(40);
						g->GetMovingAnimation()->SetContinuous(true);
						g->SetLastTime(currTime);
				}
				else if(Enemies::IsMarioRight(currPosX, currPosY)) {
						g->GetMovingAnimation()->SetDx(-4);
						g->GetMovingAnimation()->SetDelay(40);
						g->GetMovingAnimation()->SetContinuous(true);
						g->SetLastTime(currTime);
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
		}
}
void GreenKoopa::ComeOutFromShell(Animator* a, void* v) {
		MovingAnimator* g;

		AnimatorHolder::MarkAsSuspended(a);
		AnimatorHolder::Cancel(a);
		suspendingdead.push_back((MovingAnimator*)a);

		if(suspending.size() == 0) Create("greenkoopaleft");
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
						0, 0, 10000, false, ParseMarioInfo::GetAnimationIdOf(14u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspendingdead.push_back( aMovAnimr );
				
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(ComeOutFromShell, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::MoveGreenKoopas() {
		CommitDestructions(); // to destroy the lost koopas
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				
				if(Enemies::IsMarioAbove(TileX, TileY + 1)){
						MovingAnimator* d; Dim x, y;
						if(suspendingdead.size() == 0) 
								Dead();
						d = suspendingdead.back();
						d->GetMovingAnimation()->SetDx(0);
						d->GetMovingAnimation()->SetDelay(10000);
						d->GetMovingAnimation()->SetContinuous(false);
						d->SetLastTime(currTime);
						suspendingdead.pop_back();
						assert(d);
						d->GetSprite()->SetX(x = g->GetSprite()->GetX());
						d->GetSprite()->SetY(y = g->GetSprite()->GetY() + 16);
						d->SetLastTime(CurrTime());
						AnimatorHolder::MarkAsRunning(d);
						walkingdead.push_back(d);
						suspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);
						Sounds::Play("stomp");

						//jump mario:
						Dim mx = Mario::GetMarioCurrentSprite()->GetX();
						Dim my = Mario::GetMarioCurrentSprite()->GetY();
						Mario::SetDimensions(mx, my);

						AnimatorHolder::MarkAsSuspended( Mario::GetAnimator());
						Mario::SetDimensions(mx, my);
						Mario::ChangeState(Jumping);
						MovingPathAnimator* g = Mario::GetStandJump();
						g->SetCurrIndex(0);
						g->SetLastTime(currTime);
						AnimatorHolder::MarkAsRunning(g);

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
				if( Enemies::IsOnAir(TileX, TileY, f-1) && !Enemies::IsOnBrick(currPosX, currPosY))  
						g->GetMovingAnimation()->SetDy(3);
				else
						g->GetMovingAnimation()->SetDy(0);
		}
}

void GreenKoopa::ViewWindowMove() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
		for (std::list<MovingAnimator*>::iterator it=walkingdead.begin(); it != walkingdead.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
}

void GreenKoopa::CommitDestructions() {
	Dim currPosX, currPosY, TileX, TileY;
	for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end();) {
			currPosX = (*it)->GetSprite()->GetX();
			currPosY = (*it)->GetSprite()->GetY();

			TileX = (*it)->GetSprite()->GetTileX();
			TileY = (*it)->GetSprite()->GetTileY();

			if(currPosX < 2 || currPosX > 16*16 || currPosY < 2 || currPosY > 15*16 ||TileX >= MAX_WIDTH || TileY >= MAX_HEIGHT) {
					std::list<MovingAnimator*>::iterator prev = it++;
					suspending.push_back(*prev);
					AnimatorHolder::MarkAsSuspended(*prev);
					running.erase(prev);
			} else
					++it;
	}
	for (std::list<MovingAnimator*>::iterator it=walkingdead.begin(); it != walkingdead.end();) {
			currPosX = (*it)->GetSprite()->GetX();
			currPosY = (*it)->GetSprite()->GetY();

			TileX = (*it)->GetSprite()->GetTileX();
			TileY = (*it)->GetSprite()->GetTileY();

			if(currPosX < 2 || currPosX > 15*16 || currPosY < 2 || currPosY > 15*16 ||TileX >= MAX_WIDTH || TileY >= MAX_HEIGHT) {
					std::list<MovingAnimator*>::iterator prev = it++;
					suspendingdead.push_back(*prev);
					AnimatorHolder::MarkAsSuspended(*prev);
					walkingdead.erase(prev);
			} else
					++it;
	}
}

void GreenKoopa::KoopasKillMario() {
	for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				if(Enemies::IsMarioLeftOrRight(x, y + 8))
						 Mario::Hited();
		}
}

void GreenKoopa::DeactivateAllKoopas() {
	for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
		suspending.push_back(*it);
		AnimatorHolder::MarkAsSuspended(*it);
	}	
	running.clear();

	for (std::list<MovingAnimator*>::iterator it=walkingdead.begin(); it != walkingdead.end(); ++it) {
		suspendingdead.push_back(*it);
		AnimatorHolder::MarkAsSuspended(*it);
	}	
	walkingdead.clear();
}