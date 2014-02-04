#include "header_files\mario\Mario.h"

Mario* Mario::mario = NULL;
Mario* Mario::super;
MovingAnimator* Mario::MarioAnimator = NULL;
MovingAnimator* Mario::MarioWaiting = NULL;
MovingPathAnimator* Mario::MarioSJump = NULL;
MovingPathAnimator* Mario::MarioWJump = NULL;
MovingAnimator* Mario::MarioBWalk = NULL;
MovingPathAnimator* Mario::BackJump = NULL;
MovingPathAnimator* Mario::MarioDeath = NULL;
MovingAnimator* Mario::Down = NULL;
bool Mario::isOnBrick = false;
Dim Coins::coins = 0;
Dim Coins::lifes = 3;
Dim Score::score = 0;
Dim Mario::checkpoints[3] = {0, 60, 145};

timestamp_t Mario::timeReturn2Small;
timestamp_t Mario::timeIsInvincible;
timestamp_t Mario::startBeInvincible = 0;

bool Mario::isRunningNow = false;

std::vector<PathEntry> Mario::paths;
std::vector<PathEntry> Mario::backpaths;

MarioState Mario::marioState = Walking;
MarioLevel Mario::marioLevel = MarioSmall;

bool	Mario::justReturn2Small = false;

Dim countScroll = 0;
bool  Mario::isUnderGround = false;
bool	swap = true;
static bool MoveViewWindow(Dim x) {
	Mario::FlushAnimation();
	Mario::CountTimeInvincibleMario(); 
	if(Mario::GetMarioCurrentSprite()->GetTileX()
		+ Terrain::GetTileLayer()->GetViewWindow().GetX() >= 198){
		countScroll = 0;
		(Terrain::GetTileLayer())->SetScrollviewWindow(0); 
		return false;
	}
	if( x > 85 && !Mario::isUnderGround) {
		(Terrain::GetTileLayer())->SetScrollviewWindow(countScroll);
			
		Goumbas::ViewWindowMove();
		GreenKoopa::ViewWindowMove();
		Items::ViewWindowMove();
		Piranhas::ViewWindowMove();
		countScroll++;
		if(countScroll == 16) {
			(Terrain::GetTileLayer())-> ScrollHorizBy(1);
			(Terrain::GetTileLayer())->SetScrollviewWindow(0); 
			countScroll = 0;
		}
		return true;
	}
	
	return false;
}

timestamp_t timeHited = 0;
timestamp_t waitUntilFlush;
void Mario::FlushAnimation() {
	if(Mario::justReturn2Small){
		if(timeHited == 0){
			waitUntilFlush = timeHited = GetTimeReturn2Small();
		}else if(currTime - timeHited > TIME_FLASH_MARIO) {
			timeHited = 0; justReturn2Small = false;
		}
		if(swap){
			if(currTime - waitUntilFlush > 20){
				swap = false;
				AnimatorHolder::MarkAsSuspended(Mario::GetAnimator());
				waitUntilFlush += 20;
			}
		} else {
			swap = true;
			AnimatorHolder::MarkAsRunning(Mario::GetAnimator());
		}
	}
}

void Mario::CountTimeInvincibleMario() {
	if(Mario::IsInvincible()){
		if(!GetTimeBeInvincible())
			StartBeInvincible(currTime);
		else if(currTime - GetTimeBeInvincible() > GetTime2BeInvincible()){
			StartBeInvincible(0);
			Return2Normal();
		}
	}
}

void Mario::MoveViewWin() {
		Sprite* m = Mario::GetMarioCurrentSprite();
		KeepInsideViewWin();
		if(MoveViewWindow(m->GetX()))
				m->SetX(m->GetX() - 1);
}

void Mario::KeepInsideViewWin() {
		Sprite* m = GetMarioCurrentSprite();
		Animator* mAnim = GetAnimator();
		Dim x = m->GetX();
		Dim y = m->GetY();

		if(x < 5){
			switch (marioState) {
				case backwalk:
						MarioBWalk->GetMovingAnimation()->SetDx(0);
						break;
				case BackAndJump:
						int currIndex = ((MovingPathAnimator*) mAnim)->GetCurrIndex();
						((MovingPathAnimator*) mAnim)->GetAnimation()->SetOnPath(currIndex, 0);
						break;
				}
		} else {
				MarioBWalk->GetMovingAnimation()->SetDx(-3);
		}
		if(y < 18){
				switch (marioState) {
						case WalkAndJump:
						case BackAndJump:
								int currIndex = ((MovingPathAnimator*) mAnim)->GetCurrIndex();
								((MovingPathAnimator*) mAnim)->GetAnimation()->SetDyOnPath(currIndex, 0);
								break;
				}
		}

}

Mario::Mario(MovingAnimator* mario_animator){
	assert(mario_animator);
	MarioAnimator = mario_animator;
}

Mario::~Mario() {
		delete mario; mario = NULL;
}

void Mario::CreateWalking(MovingAnimator* mario_animator) {
			MarioAnimator = mario_animator;
}

void Mario::CreateWaiting(MovingAnimator* mario_animator) {
		MarioWaiting = mario_animator;
}

void Mario::CreateBackWalking(MovingAnimator* mario_animator) {
		MarioBWalk = mario_animator;
}

void Mario::CreateSjumping(MovingPathAnimator* mario_animator) {
		MarioSJump = mario_animator;
} 

void Mario::CreateWjumping(MovingPathAnimator* mario_animator) {
		MarioWJump = mario_animator;
		paths.clear();
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(5, -j, 
						IsInvincible() ? i%2 : 0, 100);
				paths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(5, j, 
						IsInvincible() ? i%2 : 0, 100);
				paths.push_back( pathEntry );
		}
}

void Mario::CreateBackAndJump(MovingPathAnimator* mario_animator) {
		BackJump = mario_animator;
		backpaths.clear();
		for(offset_t i = 0, j= 20; i < 6; ++i, j-=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, -j, 
						IsInvincible() ? i%2 : 0, 100);
				backpaths.push_back( pathEntry );
		}

		for(offset_t i = 0, j= 10; i < 6; ++i, j+=2) { // @todo make the code better!		
				PathEntry pathEntry(-5, j, 
						marioLevel == InvincibleMario? i%2 : 0, 100);
				backpaths.push_back( pathEntry );
		}
}

void Mario::CreateDown(MovingAnimator* _m) {
	Down = _m;
}

void Mario::CreateDeath(MovingPathAnimator* mario_animator) {
		if(!MarioDeath)
				MarioDeath = mario_animator;
}

Sprite* Mario::GetMarioCurrentSprite() {
		switch (marioState) {
		case Waiting:
				return MarioWaiting->GetSprite();
		case Walking:
				return MarioAnimator->GetSprite();
		case backwalk:
				return MarioBWalk->GetSprite();
		case Jumping:
				return MarioSJump->GetSprite();
		case WalkAndJump:
				return MarioWJump->GetSprite();
		case BackAndJump:
				return BackJump->GetSprite();
		case Death:
				return MarioDeath->GetSprite();
		default: 
				assert(0);
		}
		return NULL;
}

void Mario::ChangeState(MarioState nextState) {
		if(marioState == nextState)
				return ;
		unsigned int curr = CurrTime();
		switch (nextState) {
				case Waiting:
						MarioWaiting->SetLastTime(curr);
						break;
				case Walking:
						MarioAnimator->SetLastTime(curr);
						break;
				case backwalk:
						MarioBWalk->SetLastTime(curr);
						break;
				case Jumping:
						MarioSJump->SetLastTime(curr);
						break;
				case WalkAndJump:
						MarioWJump->SetLastTime(curr);
						break;
				case BackAndJump:
						return BackJump->SetLastTime(curr);
				case Death:
						MarioDeath->SetLastTime(curr);

						break;
				default: 
						assert(0);
		}
		marioState = nextState;
		return ;
}

void Mario::MarioFinisWaiting(Animator*, void*){ 
		SetDimensions(MarioBWalk, MarioAnimator);
		return ;
}

void Mario::MarioMovesLeft() {
	if(isDead()) 
		return ;
	if(isStandingJumping())
			MarioFinishSjumping(0, 0);
	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsSuspended(MarioAnimator);
	AnimatorHolder::MarkAsSuspended(MarioSJump);
	AnimatorHolder::MarkAsRunning(MarioBWalk);
	if(MarioBWalk->GetSprite()->GetX() > 4)
		MarioBWalk->GetMovingAnimation()->SetDx(-3);

	ChangeState(backwalk);
}


void Mario::MarioMovesRight() {
	if(marioState == WalkAndJump || isDead())
			return ;
	else if(isStandingJumping())
			MarioFinishSjumping(0, 0);

	AnimatorHolder::MarkAsSuspended(MarioWaiting);
	AnimatorHolder::MarkAsSuspended(MarioBWalk);
	AnimatorHolder::MarkAsSuspended(MarioSJump);
	AnimatorHolder::MarkAsRunning(MarioAnimator);
	
	if(MarioAnimator->GetMovingAnimation()->GetDx() == 0)
		MarioAnimator->GetMovingAnimation()->SetDx(4);

	ChangeState(Walking);
}

void Mario::MarioFinishWalking(Animator* anmtr, void* param) {
		SetDimensions(MarioWaiting, MarioAnimator);
		SetDimensions(MarioSJump, MarioAnimator);
		SetDimensions(MarioBWalk, MarioAnimator);
		SetDimensions(MarioWJump, MarioAnimator);
		SetDimensions(BackJump, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);

		ChangeState(Waiting);
		return ;
}

void Mario::MarioStandingJump() {
		if(marioState == Jumping || isDead())
				return ;
		if(IsOnAir(GetMarioCurrentSprite()->GetTileX(), GetMarioCurrentSprite()->GetTileY()) && !Items::IsMarioOnBrick())
				return ;
		if(!Mario::IsInvincibleSuper() || !Mario::IsSuperMario())
			Sounds::Play("jump_small");
		else
			Sounds::Play("jump_super");
		SetDimensions(MarioSJump, MarioWaiting);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsRunning(MarioSJump);
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);
		MarioSJump->SetLastTime(currTime);
		ChangeState(Jumping);
		return ;
}

void Mario::MarioWalkingJump() {
		if(marioState == WalkAndJump  || isDead()){
				return ;
		}
		if(IsOnAir(GetMarioCurrentSprite()->GetTileX(), GetMarioCurrentSprite()->GetTileY()) && !Items::IsMarioOnBrick())
				return ;
		if(!Mario::IsInvincibleSuper() || !Mario::IsSuperMario())
			Sounds::Play("jump_small");
		else
			Sounds::Play("jump_super");
		SetDimensions(MarioWJump, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		
		MarioWJump->GetAnimation()->SetPath(paths);
		AnimatorHolder::MarkAsRunning(MarioWJump);
		
		ChangeState(WalkAndJump);
		return ;
}

void Mario::BackWalkAndJump() {
		if(marioState == BackAndJump || isDead()){
				return ;
		}
		if(!Mario::IsInvincibleSuper() || !Mario::IsSuperMario())
			Sounds::Play("jump_small");
		else
			Sounds::Play("jump_super");
		SetDimensions(BackJump, MarioAnimator);

		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioBWalk);
		BackJump->GetAnimation()->SetPath(backpaths);
		AnimatorHolder::MarkAsRunning(BackJump);
		
		ChangeState(BackAndJump);
		marioState = BackAndJump;
		return ;
}

void Mario::MovesDown() {
	EnterPipe();
	if(IsInvincibleSuper() || IsSuperMario()) {
		Animator *g = GetAnimator();
		AnimatorHolder::MarkAsSuspended(g);
		SetDimensions(Down, MarioWaiting);
		AnimatorHolder::MarkAsRunning(Down);
	}
}

void Mario::MarioDeading() {
		if(marioState == Death) 
			return ;
		Sprite *s = GetMarioCurrentSprite();
		SetDimensions(s->GetX(), s->GetY());
		
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsSuspended(MarioWaiting);
		AnimatorHolder::MarkAsSuspended(MarioWJump);
		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioBWalk);

		MarioDeath->SetLastTime(currTime);
		AnimatorHolder::MarkAsRunning(MarioDeath);
		ChangeState(Death);
		Sounds::Play("mario_death");
}

void Mario::MarioFinishBackWalk(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioBWalk);
		SetDimensions(MarioAnimator, MarioBWalk);
		SetDimensions(MarioSJump, MarioBWalk);
		SetDimensions(MarioWJump, MarioBWalk);
		SetDimensions(BackJump,MarioBWalk);

		AnimatorHolder::MarkAsSuspended(MarioBWalk);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		
		ChangeState(Waiting);

		return ;
}

void Mario::MarioFinishSjumping(Animator*, void*) {
		SetDimensions(MarioWaiting, MarioSJump);
		SetDimensions(MarioAnimator, MarioSJump);
		SetDimensions(MarioBWalk, MarioSJump);
		SetDimensions(BackJump, MarioSJump);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		MarioSJump->SetCurrIndex(0);
		ChangeState(Waiting);

		return ;
}

void Mario::MarioFinishWjumping(Animator* , void* ) {
		SetDimensions(MarioWaiting, MarioWJump);
		SetDimensions(MarioAnimator, MarioWJump);
		SetDimensions(MarioSJump, MarioWJump);
		SetDimensions(MarioBWalk, MarioWJump);
		SetDimensions(BackJump, MarioWJump);

		AnimatorHolder::MarkAsSuspended(MarioSJump);
		AnimatorHolder::MarkAsSuspended(MarioWJump);
		AnimatorHolder::MarkAsSuspended(MarioAnimator);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		MarioWJump->SetCurrIndex(0);
		ChangeState(Waiting);

		return ;
}

void Mario::MarioFinishBackJump(Animator*, void*) {
		SetDimensions(MarioWaiting, BackJump);
		SetDimensions(MarioAnimator, BackJump);
		SetDimensions(MarioSJump, BackJump);
		SetDimensions(MarioBWalk, BackJump);
		SetDimensions(MarioWJump, BackJump);

		AnimatorHolder::MarkAsSuspended(BackJump);
		AnimatorHolder::MarkAsRunning(MarioWaiting);
		BackJump->SetCurrIndex(0);
		ChangeState(Waiting);
}

void Mario::FinishDown(Animator*, void*) {
	if(al_key_down(&keyboardState, ALLEGRO_KEY_DOWN))
		return ;
	AnimatorHolder::MarkAsSuspended(Down);
	AnimatorHolder::MarkAsRunning(MarioWaiting);
	ChangeState(Waiting);
}

clock_t wai;
void Mario::MarioFinishDeath(Animator*a, void*v) {
	if(Coins::lifes == 2)
		TerrainStartScreen::CreateLifeScreen2();
	else if (Coins::lifes == 1)
		TerrainStartScreen::CreateLifeScreen1();
	else if (Coins::lifes == 0)
		TerrainStartScreen::CreateGameOver();

	MarioBrosMain::DeathRender();
	if(MarioBrosMain::GameIsPlay())
		MarioBrosMain::SetGamePause();
	wai = clock();
	while( clock() != wai + 3000 );
	if (Coins::lifes == 0)
		exit(0);
	MarioBrosMain::SetGamePlay();
	
	AnimatorHolder::MarkAsSuspended(a);
	if( Mario::GetMarioCurrentSprite()->GetTileX() + Terrain::GetTileLayer()->GetViewWindow().GetX() > checkpoints[2] )
			RestoreCheckpoint(checkpoints[2]);
	else if( Mario::GetMarioCurrentSprite()->GetTileX() + Terrain::GetTileLayer()->GetViewWindow().GetX() > checkpoints[1] )
		RestoreCheckpoint(checkpoints[1]);
	else 
		RestoreCheckpoint(checkpoints[0]);

	Items::ReactivateItems(0);
	Enemies::Reactivate(0);
}

void Mario::RestoreCheckpoint(Dim x) {
	Sprite * activeMario = Mario::GetMarioCurrentSprite();
	Rect viewWin;
	viewWin.SetX(x);
	countScroll = 0;
	viewWin.SetY(0);
	viewWin.SetHeight(15);
	viewWin.SetWidth(16);
	activeMario->SetX(76);
	activeMario->SetY(129);
	AnimatorHolder::MarkAsRunning(MarioAnimator);
	Terrain::GetTileLayer()->SetViewWindow(viewWin);
}

Animator* Mario::GetAnimator() {
	switch (marioState) {
		case Waiting:
				return MarioWaiting;
		case Walking:
				return MarioAnimator;
		case backwalk:
				return MarioBWalk;
		case Jumping:
				return MarioSJump;
		case WalkAndJump:
				return MarioWJump;
		case BackAndJump:
				return BackJump;
		case Death:
				return MarioDeath;
		default: 
				assert(0);
	}
	return NULL;
}

bool startScrolling = false;
void Mario::EnterPipe() {
	Sprite* activeMario = Mario::GetMarioCurrentSprite();
	Dim x = activeMario->GetTileX() + Terrain::GetTileLayer()->GetViewWindow().GetX();
	Dim y = activeMario->GetTileY();
	if(x == 47 || x == 48){
			Sounds::Play("enter_pipe");
			Sounds::Pause("music");
			Sounds::Play("underground");
			Rect viewWin;
			viewWin.SetX(209);
			countScroll = 0;
			Terrain::GetTileLayer()->SetScrollviewWindow(0);
			viewWin.SetY(0);
			viewWin.SetHeight(15);
			viewWin.SetWidth(16);
			Terrain::GetTileLayer()->SetViewWindow(viewWin);
			Mario::isUnderGround = true;
			activeMario->SetX(20);
			activeMario->SetY(20);
			Items::KillPipes();
			Goumbas::KillGoumbas();
	}
	return;
}

void Mario::GetOutFromPipe() {
	if(Mario::isUnderGround) {
		Sprite* activeMario = Mario::GetMarioCurrentSprite();
		Dim x = activeMario->GetTileX();
		if(x == 12){
			Sounds::Play("enter_pipe");
			Sounds::Pause("underground");
			Sounds::Play("music");
			Rect viewWin;
			viewWin.SetX(159);
			countScroll = 0;
			viewWin.SetY(0);
			viewWin.SetHeight(15);
			viewWin.SetWidth(16);
			/*activeMario->SetX(76);
			activeMario->SetY(129);*/
			MarioWaiting->GetSprite()->SetX(76);
			MarioWaiting->GetSprite()->SetY(150);
			MarioAnimator->GetSprite()->SetX(76);
			MarioAnimator->GetSprite()->SetY(150);
			MarioBWalk->GetSprite()->SetX(76);
			MarioBWalk->GetSprite()->SetY(150);
			MarioSJump->GetSprite()->SetX(76);
			MarioSJump->GetSprite()->SetY(150);
			MarioWJump->GetSprite()->SetX(76);
			MarioWJump->GetSprite()->SetY(150);
			BackJump->GetSprite()->SetX(76);
			BackJump->GetSprite()->SetY(150);
			Terrain::GetTileLayer()->SetViewWindow(viewWin);
			Mario::isUnderGround = false;
			Items::SuspendCoinsUnderGround();
		}
	}
}

Dim scrollX = 0;
#define PIPE_WINDOW 180
Dim Mario::PipeEnterScroll(Dim i) {
		return 0;
}

void Mario::SetDimensions(MovingAnimator* source, MovingAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingAnimator* dest) {
		SetDimensions(MarioAnimator, dest);
		SetDimensions(MarioWaiting, dest);
		SetDimensions(MarioSJump, dest);
		SetDimensions(MarioWJump, dest);
}

void Mario::SetDimensions(Dim x, Dim y) {
		MarioAnimator->GetSprite()->SetX(x);
		MarioAnimator->GetSprite()->SetY(y);

		MarioBWalk->GetSprite()->SetX(x);
		MarioBWalk->GetSprite()->SetY(y);

		MarioWaiting->GetSprite()->SetX(x);
		MarioWaiting->GetSprite()->SetY(y);

		MarioSJump->GetSprite()->SetX(x);
		MarioSJump->GetSprite()->SetY(y);

		MarioWJump->GetSprite()->SetX(x);
		MarioWJump->GetSprite()->SetY(y);

		MarioDeath->GetSprite()->SetX(x);
		MarioDeath->GetSprite()->SetY(y);
}

void Mario::SetDimensions(MovingPathAnimator* source, MovingAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingAnimator* source, MovingPathAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
		return ;
}

void Mario::SetDimensions(MovingPathAnimator* source, MovingPathAnimator* dest) {
		source->GetSprite()->SetX(dest->GetSprite()->GetX());
		source->GetSprite()->SetY(dest->GetSprite()->GetY());
}

bool Mario::IsOnAir(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();
		Dim mheight = Mario::GetMarioCurrentSprite()->GetFrameBox().GetHeight() >> 4;

		if(Collision::GetValue(x + i, y + j + mheight) == 0 || Collision::GetValue(x + i + 1, y + j + mheight) == 0)
				return true;
		return false;
}

bool Mario::CanGoLeft(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();;
		
		if(Collision::GetValue(x + i, y + j) != 0)
				return false;
		return true;
}

bool Mario::CanGoRight(Dim x, Dim y) {
	Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		
	x += (GetMarioCurrentSprite()->GetFrameBox().GetHeight() >> 4) - 1 ;
	if(Collision::GetValue(x + i + 1, y) != 0)
			return false;
	return true;
}

bool Mario::IsOnPipe(Dim x, Dim y) {
		Dim i = Terrain::GetTileLayer()->GetViewWindow().GetX();
		Dim j = Terrain::GetTileLayer()->GetViewWindow().GetY();;
		
		if(Collision::GetValue(x + i, y + j + 1) == 1 || Collision::GetValue(x + i, y + j + 1) == 1 || Collision::GetValue(x + i, y + j + 1) == 1)
				return true;
		return false;
}

void ChangeLevel(Animator* prev) {
	AnimatorHolder::MarkAsSuspended(prev);
	switch (Mario::marioState) {
		case Waiting:
				Mario::MarioFinisWaiting(0,0);
				break;
		case Walking:
				Mario::MarioFinishWalking(0,0);
				break;
		case backwalk:
				Mario::MarioFinishBackWalk(0,0);
				break;
		case Jumping:
				Mario::MarioFinishSjumping(0,0);
				break;
		case WalkAndJump:
				Mario::MarioFinishWjumping(0, 0);
				break;
		case BackAndJump:
				Mario::MarioFinishBackJump(0,0);
				break;
		case Death:
				break;
		default: 
				assert(0);
	}
	AnimatorHolder::MarkAsRunning(Mario::MarioWaiting);

	return ;
}
void Mario::SuperMario() {
		marioLevel = Super_Mario;
		Animator* prev = GetAnimator();
		Initializer::InitSuperMario();
		ChangeLevel(prev);
}

void Mario::FlashMario() {
		Animator* prev = GetAnimator();
		FlushMario::InitSuperMario();
		ChangeLevel(prev);
}

void Mario::SetSuperAsInvincible() {
	marioLevel = InvincibleSuper;
	FlushMario::InitSuperMario();	
}

void Mario::SetMarioAsInvincible() {
		Animator* prev = GetAnimator();
		switch (marioLevel) {
				case MarioSmall:
						marioLevel = InvincibleMario;
						FlushMario::InitMario();
						break;
				case Super_Mario:
						SetSuperAsInvincible();
						break;
		}
		StartBeInvincible(currTime);
		ChangeLevel(prev);
}

bool Mario::IsMarioSmall() {
	return marioLevel == MarioSmall;
}

bool Mario::IsInvincible() {
		return marioLevel == InvincibleMario || marioLevel == InvincibleSuper;
}

bool Mario::IsSuperMario() {
	return marioLevel == Super_Mario;
}

void Mario::Run() {
		isRunningNow = true;

		delay_t delay = MarioAnimator->GetMovingAnimation()->GetDelay();
		if(delay >= 50)
				MarioAnimator->GetMovingAnimation()->SetDelay(--delay);

}

 void Mario::isNotRunning(){
		isRunningNow = false;
		delay_t delay = MarioAnimator->GetMovingAnimation()->GetDelay();
		if( delay < 90)
				MarioAnimator->GetMovingAnimation()->SetDelay(++delay);
	
 }

 void Mario::Hited() {
	 if(IsMarioSmall() && !isDead() && !justReturn2Small){
		 Coins::RemoveLife();
		 MarioDeading();
	 } else if(IsSuperMario()) {
			 Dim x = Mario::GetMarioCurrentSprite()->GetX();
			 Dim y = Mario::GetMarioCurrentSprite()->GetY();
			 marioLevel = MarioSmall;
			 Animator* prev = GetAnimator();
			 Initializer::InitMario();
			 ChangeLevel(prev);
			 Mario::SetDimensions(x, y);
			 justReturn2Small = true;
			 SetTimeReturn2Small(currTime);
	 }
 }

 void Mario::Return2Normal() {
	Dim x = GetMarioCurrentSprite()->GetX();
	Dim y = GetMarioCurrentSprite()->GetY();
	Animator* prev = GetAnimator();
	switch (marioLevel){
		case InvincibleMario:
			marioLevel = MarioSmall; // change lever before Init is NECESSARY
			Initializer::InitMario();
			
			break;
		case InvincibleSuper:
			marioLevel = Super_Mario; // change lever before Init is NECESSARY
			Initializer::InitSuperMario();

			break;
	}
	ChangeLevel(prev);
	SetDimensions(x, y);
 }