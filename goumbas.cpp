#include "header_files\enemies\Goumba.h"

std::list<MovingAnimator*> Goumbas::goumba;

void Goumbas::Create() {
		Sprite *goumbaSprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("goombawalking") ));
		
		MovingAnimation* aMovAnimn = (MovingAnimation*) new FrameRangeAnimation(
						0, 1, 
						0, 0, 90, false, ParseMarioInfo::GetAnimationIdOf(7u)
						);
		MovingAnimator* aMovAnimr =  (MovingAnimator*)new FrameRangeAnimator(); 
		
		Goumbas::goumba.push_back( aMovAnimr );
				
		aMovAnimr->Start( goumbaSprite, aMovAnimn, GetCurrTime());			
		//aMovAnimr->SetOnFinish(Mario::MarioFinishWalking, NULL);
		AnimatorHolder::Register( aMovAnimr );				
}

void Goumbas::ArtificialIntelligence() {
		Dim goumbasCount = 0;
		MovingAnimator* g = NULL;
		for(Dim i = 0; i < 15; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim x = i;
						Dim y = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						
						if(Enemies::GetFromMap(x, y) != 0) {
								g = goumba.back();
								g->GetSprite()->SetX((x % VIEW_WINDOW_TILE_HEIGHT) * 16);
								g->GetSprite()->SetY((y % VIEW_WINDOW_TILE_HEIGHT) * 16);
								AnimatorHolder::MarkAsRunning(g); goumbasCount++;
						}
				}
		if(!goumbasCount) AnimatorHolder::MarkAsRunning(g);
}