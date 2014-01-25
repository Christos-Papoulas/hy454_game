#include "header_files\enemies\Goumba.h"

std::list<MovingAnimator*> Goumbas::goumbaSuspending;
std::list<MovingAnimator*> Goumbas::running;
std::list<MovingAnimator*> Goumbas::dead;
Dim Goumbas::delay = 100;

void Goumbas::Create() {
		Sprite *goumbaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("goombawalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						-2, 0, Goumbas::delay, true, ParseMarioInfo::GetAnimationIdOf(7u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Goumbas::goumbaSuspending.push_back( aMovAnimr );
				
		aMovAnimr->Start( goumbaSprite, aMovAnimn, GetCurrTime());			
		
		AnimatorHolder::Register( aMovAnimr );
}

void Goumbas::Dead() {
		Sprite *goumbaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("goombadead") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 0, 
						0, 0, 2500, false, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("goombadead"))
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Goumbas::dead.push_back( aMovAnimr );
				
		aMovAnimr->Start( goumbaSprite, aMovAnimn, GetCurrTime());			
		aMovAnimr->SetOnFinish(Finish, NULL);
		AnimatorHolder::Register( aMovAnimr );
}

void Goumbas::BadDeath(Dim x, Dim y) {
		Sprite *goumbaSprite = new Sprite(x, y, AnimationFilmHolder::GetFilm( std::string("goumbabaddeath") ));
		
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 20u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 6u) ? -5 : 5, 0, 70);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("mariojumping")));
		MovingPathAnimator* aMovAnimr = (MovingPathAnimator*) new MovingPathAnimator();
		
		Goumbas::dead.push_back( (MovingAnimator*)aMovAnimr );
				
		aMovAnimr->Start( goumbaSprite, aMovAnimn, GetCurrTime());		
		aMovAnimr->GetAnimation()->SetContinuous(false);
		aMovAnimr->SetOnFinish(Finish, NULL);
		AnimatorHolder::Register( aMovAnimr );
		AnimatorHolder::MarkAsRunning( aMovAnimr );
}

void Goumbas::ArtificialIntelligence() {
		CreateGoumbaifAny();
		MoveGoumbas();
		GoumbasKillMario();
}

void Goumbas::CreateGoumbaifAny() {
		MovingAnimator* g = NULL;
		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(Enemies::GetFromMap(y, x) == 161) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;
								if(goumbaSuspending.size() == 0) 
										Create();
								g = goumbaSuspending.back();
								goumbaSuspending.pop_back();
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

void Goumbas::Finish(Animator *a, void *f) {
		AnimatorHolder::MarkAsSuspended(a);
}

void Goumbas::MoveGoumbas() {
		Goumbas::SuspendGoumbas();
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim currPosX = g->GetSprite()->GetX();
				Dim currPosY = g->GetSprite()->GetY();

				Dim TileX = g->GetSprite()->GetTileX();
				Dim TileY = g->GetSprite()->GetTileY();

				if(Enemies::IsMarioAbove(TileX, TileY)){
						MovingAnimator* d; Dim x, y;
						if(dead.size() == 0) 
								Dead();
						d = dead.back();
						if(!d) return ;
						d->GetSprite()->SetX(x = g->GetSprite()->GetX());
						d->GetSprite()->SetY(y = g->GetSprite()->GetY() + 8);
						d->SetLastTime(CurrTime());
						AnimatorHolder::MarkAsRunning(d);

						goumbaSuspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
						running.erase(it);
						Sounds::Play("stomp");
						Items::Throw100Coins(x, y);
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

				if( Enemies::IsOnAir(TileX, TileY, 0) && !Enemies::IsOnBrick(currPosX, currPosY)) 
						g->GetMovingAnimation()->SetDy(3);
				else
						g->GetMovingAnimation()->SetDy(0);
		}
}

void Goumbas::ViewWindowMove() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
		for (std::list<MovingAnimator*>::iterator it=dead.begin(); it != dead.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
}

void Goumbas::GoumbasKillMario() {
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
				MovingAnimator* g = *it;
				Dim x = g->GetSprite()->GetX();
				Dim y = g->GetSprite()->GetY();

				if(Enemies::IsMarioLeftOrRight(x, y))
						 Mario::MarioDeading();
		}
}

void Goumbas::SuspendGoumbas(){
		for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end();) {
				Dim currPosX = (*it)->GetSprite()->GetX();
				Dim currPosY = (*it)->GetSprite()->GetY();

				Dim TileX = (*it)->GetSprite()->GetTileX();
				Dim TileY = (*it)->GetSprite()->GetTileY();

				if(currPosX < 2 || currPosX > 16*16 || TileX > MAX_WIDTH || TileY >= MAX_HEIGHT -1) {
						std::list<MovingAnimator*>::iterator prev = it++;
						goumbaSuspending.push_back(*prev);
						AnimatorHolder::MarkAsSuspended(*prev);
						running.erase(prev);
				} else
						++it;
		}
}

void Goumbas::KillGoumbas(){
	for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
						goumbaSuspending.push_back(*it);
						AnimatorHolder::MarkAsSuspended(*it);
		}	
	running.clear();
}

void Goumbas::CollicionWithKoopaInShells(Dim kx, Dim ky) {
	Dim gx, gy, dx, dy;
	for (std::list<MovingAnimator*>::iterator it=running.begin(); it != running.end(); ++it) {
			gx = (*it)->GetSprite()->GetX();
			gy = (*it)->GetSprite()->GetY();
			dx = (kx > gx) ? kx - gx : gx - kx;
			dy = (ky > gy) ? ky - gy : gy - ky;
			if(dx < COLLISION_DETECT && dy < COLLISION_DETECT){
					BadDeath(gx, gy);
					AnimatorHolder::MarkAsSuspended(*it);
					goumbaSuspending.push_back(*it);
					running.erase(it);
					return ;
			}
	}
}
