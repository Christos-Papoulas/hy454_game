#include "header_files\enemies\Piranhas.h"

std::list<HiddenAnimator*> Piranhas::suspending;
std::list<HiddenAnimator*> Piranhas::running;
std::list<HiddenAnimator*> Piranhas::dead;

void Piranhas::CreateIfAny() {
		HiddenAnimator* g = NULL;
		for(Dim i = 0; i < VIEW_WINDOW_TILE_HEIGHT; i++)
				for(Dim j = 0; j < VIEW_WINDOW_TILE_WIDTH; j++){
						Dim y = i;
						Dim x = j + Terrain::GetTileLayer()->GetViewWindow().GetX();
						Rect view = Terrain::GetTileLayer()->GetViewWindow();
						if(Enemies::GetFromMap(y, x) == 1012) {
								if(Enemies::IsEnemyActive(y, x)) 
										continue;

								if(suspending.size() == 0) 
										Create();

								g = suspending.back();
								suspending.pop_back();
								if(!g) return ;
								g->GetSprite()->SetX((j % VIEW_WINDOW_TILE_HEIGHT) * 16 + 8);
								g->GetSprite()->SetY(y * 16);
								g->SetLastTime(CurrTime());
								AnimatorHolder::MarkAsRunning(g);
								Enemies::SetEnemyAsActive(y,x);
								running.push_back(g);
						}
				}
} 

void Piranhas::Create() {
		Sprite *sprite = new Sprite(20, 100, AnimationFilmHolder::GetFilm( std::string("piranhaplant") ));
		
		std::vector<PathEntry> paths;
		for(Dim i = 0u; i < 14u; ++i) { // @todo make the code better!		
				PathEntry pathEntry(0, (i < 7u) ? -3 : 3, i%2, 100);
				paths.push_back( pathEntry );
		}
		MovingPathAnimation* aMovAnimn = (MovingPathAnimation*) new MovingPathAnimation(paths, ParseMarioInfo::GetAnimationIdOf(ParseMarioInfo::GetIndexOf("piranhaplant")));
		HiddenAnimator* aMovAnimr = new HiddenAnimator(); 
		
		suspending.push_back( aMovAnimr );
				
		aMovAnimr->Start( sprite, aMovAnimn, GetCurrTime());
		AnimatorHolder::Register( aMovAnimr );
}

void Piranhas::ArtificialIntelligence(){
		CreateIfAny();
}

void Piranhas::ViewWindowMove() {
		for (std::list<HiddenAnimator*>::iterator it=running.begin(); it != running.end(); ++it)
				(*it)->GetSprite()->SetX((*it)->GetSprite()->GetX() - 1);
}