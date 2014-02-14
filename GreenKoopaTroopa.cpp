#include "header_files\enemies\GreenKoopaTroopa.h"

std::map<std::string,std::list<MovingAnimator*>> GreenKoopa::suspending;
std::map<std::string,std::list<MovingAnimator*>> GreenKoopa::running;
std::map<std::string,std::list<MovingAnimator*>> GreenKoopa::suspendingdead;
std::map<std::string,std::list<MovingAnimator*>> GreenKoopa::walkingdead;
Dim GreenKoopa::delay = 100;

void GreenKoopa::Create(const char* id) {
		Sprite *greenKoopaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						-2, 0, delay, true, ParseMarioInfo::GetIndexOf(id)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspending[id].push_back( aMovAnimr );
				
		aMovAnimr->Start( greenKoopaSprite, aMovAnimn, GetCurrTime());			
		//aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::ArtificialIntelligence() {
		CreateGreenKoopaIfAny();
		MoveKoopasInShells("greenkoopahit"); MoveKoopasInShells("redkoopahit"); 
		MoveGreenKoopas("greenkoopaleft"); 	MoveGreenKoopas("redkoopaleft");
		KoopasKillMario("greenkoopaleft"); KoopasKillMario("redkoopaleft");
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
								if(suspending["greenkoopaleft"].empty()) Create("greenkoopaleft");
								g = suspending["greenkoopaleft"].back();

								suspending["greenkoopaleft"].pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running["greenkoopaleft"].push_back(g);
						} else if(Enemies::GetFromMap(y, x) == 195) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;
								if(suspending["redkoopaleft"].empty()) Create("redkoopaleft");
								g = suspending["redkoopaleft"].back();

								suspending["redkoopaleft"].pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running["redkoopaleft"].push_back(g);
						}
				}
}

void GreenKoopa::MoveKoopasInShells(const char* id) {
		for (std::list<MovingAnimator*>::iterator it=walkingdead[id].begin(); it != walkingdead[id].end(); ++it) {
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
		MovingAnimator* g; char toCreate[20];
		const std::string id = ((MovingAnimator*)a)->GetSprite()->GetCurrFilm()->GetID();
		if(!strcmp(id.c_str(), "greenkoopahit"))
			strcpy(toCreate, "greenkoopaleft");
		else
			strcpy(toCreate, "redkoopaleft");

		AnimatorHolder::MarkAsSuspended(a);
		//AnimatorHolder::Cancel(a);
		suspendingdead[id].push_back((MovingAnimator*)a);

		if(suspending[toCreate].size() == 0) Create(id.c_str());
		g = suspending[toCreate].back();
		suspending[toCreate].pop_back();
		assert(g);
		g->GetSprite()->SetX( ((MovingAnimator*) a)->GetSprite()->GetX() );
		g->GetSprite()->SetY( ((MovingAnimator*) a)->GetSprite()->GetY() - 16 );
		g->SetLastTime(CurrTime());
		AnimatorHolder::MarkAsRunning(g);

		running[toCreate].push_back(g);
}

void GreenKoopa::Dead(const char* id) {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string(id) ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 10000, false,  
						ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf( id ) ) );
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		suspendingdead[id].push_back( aMovAnimr );
				
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(ComeOutFromShell, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void GreenKoopa::MoveGreenKoopas(const char* id) {
		CommitDestructions(id); // to destroy the lost koopas
		for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();
				
				if(Enemies::IsMarioAbove(TileX, TileY + 1)){
					char toCreate[20];
					const std::string id = g->GetSprite()->GetCurrFilm()->GetID();
					if(!strcmp(id.c_str(), "greenkoopaleft"))
						strcpy(toCreate, "greenkoopahit");
					else
						strcpy(toCreate, "redkoopahit");

						MovingAnimator* d; Dim x, y;
						if(suspendingdead[toCreate].size() == 0) 
								Dead(toCreate);
						d = suspendingdead[toCreate].back();
						d->GetMovingAnimation()->SetDx(0);
						d->GetMovingAnimation()->SetDelay(10000);
						d->GetMovingAnimation()->SetContinuous(false);
						d->SetLastTime(currTime);
						suspendingdead[toCreate].pop_back();
						assert(d);
						d->GetSprite()->SetX(x = g->GetSprite()->GetX());
						d->GetSprite()->SetY(y = g->GetSprite()->GetY() + 16);
						d->SetLastTime(CurrTime());
						AnimatorHolder::MarkAsRunning(d);
						walkingdead[toCreate].push_back(d);
						suspending[id].push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running[id].erase(it);
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

void GreenKoopa::ViewWindowMove(const char* id) {
		for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
		for (std::list<MovingAnimator*>::iterator it=walkingdead[id].begin(); it != walkingdead[id].end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
}

void GreenKoopa::CommitDestructions(const char* id) {
	Dim currPosX, currPosY, TileX, TileY;
	for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end();) {
			currPosX = (*it)->GetSprite()->GetX();
			currPosY = (*it)->GetSprite()->GetY();

			TileX = (*it)->GetSprite()->GetTileX();
			TileY = (*it)->GetSprite()->GetTileY();

			if(currPosX < 2 || currPosX > 16*16 || currPosY < 2 || currPosY > 15*16 ||TileX >= MAX_WIDTH || TileY >= MAX_HEIGHT) {
					std::list<MovingAnimator*>::iterator prev = it++;
					suspending[id].push_back(*prev);
					AnimatorHolder::MarkAsSuspended(*prev);
					running[id].erase(prev);
			} else
					++it;
	}
	for (std::list<MovingAnimator*>::iterator it=walkingdead[id].begin(); it != walkingdead[id].end();) {
			currPosX = (*it)->GetSprite()->GetX();
			currPosY = (*it)->GetSprite()->GetY();

			TileX = (*it)->GetSprite()->GetTileX();
			TileY = (*it)->GetSprite()->GetTileY();

			if(currPosX < 2 || currPosX > 15*16 || currPosY < 2 || currPosY > 15*16 ||TileX >= MAX_WIDTH || TileY >= MAX_HEIGHT) {
					std::list<MovingAnimator*>::iterator prev = it++;
					suspendingdead[id].push_back(*prev);
					AnimatorHolder::MarkAsSuspended(*prev);
					walkingdead[id].erase(prev);
			} else
					++it;
	}
}

void GreenKoopa::KoopasKillMario(const char* id) {
	for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
				MovingAnimator* g = *it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				if(Enemies::IsMarioLeftOrRight(x, y + 8))
						 Mario::Hited();
		}
}

void GreenKoopa::DeactivateAllKoopas(const char* id) {
	for (std::list<MovingAnimator*>::iterator it=running[id].begin(); it != running[id].end(); ++it) {
		suspending[id].push_back(*it);
		AnimatorHolder::MarkAsSuspended(*it);
	}	
	running[id].clear();

	for (std::list<MovingAnimator*>::iterator it=walkingdead[id].begin(); it != walkingdead[id].end(); ++it) {
		suspendingdead[id].push_back(*it);
		AnimatorHolder::MarkAsSuspended(*it);
	}	
	walkingdead[id].clear();
}
