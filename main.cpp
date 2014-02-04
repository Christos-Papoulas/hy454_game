#include "header_files\MarioBrosMain.h"

GameState gameState = Start;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_EVENT events;

ALLEGRO_KEYBOARD_STATE keyboardState;
bool redraw = true;

const float FPS = 90;
int z_pressed = 0;
int space_pressed = 0;
clock_t wait;

bool MarioBrosMain::InitAllegro(){
		if(!al_init()){
				al_show_native_message_box(NULL, "Error", NULL, "Game can not Initialize Graphics.\n", NULL, NULL);
				return false;
		}
		timer = al_create_timer(1.0 / FPS);
		if(!timer) {
				al_show_native_message_box(NULL, "Error", NULL, "Game can not Initialize FPS timer\n", NULL, NULL);
				return false;
		}
		display = al_create_display(SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
		if(!display) {
				al_show_native_message_box(NULL, "Error", NULL, "Game can not create display\n", NULL, NULL);
				al_destroy_timer(timer);
				return false;
		}
		al_set_window_position(display, 0, 0);

		al_install_keyboard();
		al_init_image_addon();

		if(!al_install_audio()){
				al_show_native_message_box(NULL, "Error", NULL, "Game can not initialize audio\n", NULL, NULL);
				al_destroy_display(display);
				al_destroy_timer(timer);
				return false;
		}

		if(!al_init_acodec_addon()){
				al_show_native_message_box(NULL, "Error", NULL, "Game can not initialize audio codecs\n", NULL, NULL);
				al_destroy_display(display);
				al_destroy_timer(timer);
				return false;
		}

		if(!Sounds::InitSounds())
			return false;

		queue = al_create_event_queue();
		if(!queue) {
				al_show_native_message_box(NULL, "Error", NULL, "Game can not create game events\n", NULL, NULL);
				al_destroy_display(display);
				al_destroy_timer(timer);
				return false;
		}
		al_register_event_source(queue, al_get_display_event_source(display));
		al_register_event_source(queue, al_get_timer_event_source(timer));
	
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_flip_display();

		return true;
}

 void MarioBrosMain::Rendering(timestamp_t now) {

	 if(!al_is_event_queue_empty(queue)) 
				return ;
		 
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		StartScreen(now);

		if(gameState == Play){
			Terrain::DisplayTerrain(al_get_backbuffer(display), now);
			AnimatorHolder::Display(al_get_backbuffer(display)); 		// @todo working properly;
		}
		
		if(gameState == Pause){
			TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
			AnimatorHolder::Display(al_get_backbuffer(display)); 		// @todo working properly;
		}

		if(gameState == Over){
			TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
			al_flip_display();
			wait = clock();
			while( clock() != wait + 3000 );
			exit(0);
		}

		
		al_flip_display(); // is blocking depending on defines?
}

//game loop logic
void MarioBrosMain::MainLoopOneIteration() {
	InputManagement(); //just reads from local input queue
	if(gameState == Play){
		ArtificialIntelligence(); // to stop mario at pipes
		CollisionChecking(); // to stop mario at tiles
		AnimationProgress();
		
		
		Mario::MoveViewWin();

		NumbersHolder::PrintNumberCoins(Coins::coins);
		NumbersHolder::PrintScore(Score::score);
		ManageTime();

		CommitDestructions();
		FPSCalculation();
	}
}

void MarioBrosMain::DeathRender() {
	TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), currTime);
	al_flip_display();
}
bool flag = true;
void MarioBrosMain::ManageTime() {
	Time::clock();
	if(Time::time == 100 && flag) {
		if(!Mario::isUnderGround){
			Sounds::Pause("music");
			Sounds::Play("warning");
			wait = clock();
			while( clock() != wait + 2000 );
			Sounds::Play("hurry_up");
			flag = false;
		}else{
			Sounds::Pause("music");
			Sounds::Play("warning");
			wait = clock();
			while( clock() != wait + 2000 );
			Sounds::Play("underground_hurry_up");
			flag = false;
		}
	}
	if(Time::time == 0){
		TerrainStartScreen::CreateGameOver();
		Sounds::Pause("music");
		Sounds::Pause("hurry_up");
		Sounds::Pause("underground_hurry_up");
		MarioBrosMain::SetGameOver();
	}
	NumbersHolder::PrintNumberTime(Time::time);
}

void MarioBrosMain::InputManagement(){
	if(!al_key_down(&keyboardState, ALLEGRO_KEY_LEFT))
		z_pressed = 0;
	if(!al_key_down(&keyboardState, ALLEGRO_KEY_SPACE))
		space_pressed = 0;

	if(gameState == Pause){
		if(al_key_down(&keyboardState, ALLEGRO_KEY_SPACE)){ // space
			if(!space_pressed){
				Sounds::Play("pause");
				GamePause(currTime);
				space_pressed = 1;
			}
		}
		return ;
	}

	if(!Mario::isWalkingJump() && !Mario::isBackJumping() &&  gameState == Play) {
				if(al_key_down(&keyboardState, ALLEGRO_KEY_Z) && al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)){
						if(Mario::isWalking() && !Mario::isWalkingJump()){
							return Mario::MarioWalkingJump();
						}
				}
				if(al_key_down(&keyboardState, ALLEGRO_KEY_Z) && al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)){
						if(Mario::isBackWalk() && !Mario::isBackJumping() ){
							return Mario::BackWalkAndJump();
						}
				}

				if(al_key_down(&keyboardState, ALLEGRO_KEY_X) && Mario::isWalking()){
						Mario::Run();
				}
				if(!al_key_down(&keyboardState, ALLEGRO_KEY_X))
						Mario::isNotRunning();

				if(al_key_down(&keyboardState, ALLEGRO_KEY_DOWN)){ // down
						return Mario::MovesDown(); // @todo something
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)){ // right
						Mario::GetOutFromPipe();
						return Mario::MarioMovesRight();
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)){ // lest
						return Mario::MarioMovesLeft();
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_SPACE)){ // space
					if(!space_pressed){
						Sounds::Play("pause");
						GamePause(currTime);
						space_pressed = 1;
					}
					return ;
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_Z)){ // z
					if(!z_pressed){
						
						z_pressed = 1;
					}
					if(!Mario::isStandingJumping()){
						return Mario::MarioStandingJump();
					}
				}
				al_flush_event_queue(queue);

				if(al_key_down(&keyboardState, ALLEGRO_KEY_C))
					Mario::SuperMario();
				if(al_key_down(&keyboardState, ALLEGRO_KEY_V))
					Mario::SetMarioAsInvincible();
		}
}

void MarioBrosMain::StartScreen(timestamp_t now) {
	TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
	if((al_key_down(&keyboardState, ALLEGRO_KEY_ENTER)) && gameState == Start){ // enter
		TerrainStartScreen::CreateLifeScreen();
		TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
		al_flip_display();
		wait = clock();
	while( clock() != wait + 3000 );
		GameStarting();
	}
}


void MarioBrosMain::GameStarting() {

	gameState = Play;
	Sounds::Play("music");
}

void MarioBrosMain::GamePause(timestamp_t now) {
	if(gameState == Play){
		gameState = Pause;
		TerrainStartScreen::CreatePause();
		Items::KillBricks();
	}else if(gameState == Pause){
		gameState = Play;
		AnimatorHolder::SetTime(now);
		Items::RegenerateBricks();
	}
}

void MarioBrosMain::AnimationProgress(){
		AnimatorHolder::Progress(GetCurrTime());
		return ;
}

void MarioBrosMain::ArtificialIntelligence(){
		Goumbas::ArtificialIntelligence();
		GreenKoopa::ArtificialIntelligence();
		Items::ArtificialIntelligence();
		Piranhas::CreateIfAny();
		return ;
}


void MarioBrosMain::CollisionChecking(){
		Collision::CheckCollision();
		CollisionChecker::Check();
		return ;
}

void MarioBrosMain::CommitDestructions(){
		Goumbas::SuspendGoumbas();
		Items::SuspendBricks();
		Items::CommitDestructions();
		Items::CommitDestructions("bricks");
		GreenKoopa::CommitDestructions();
		Piranhas::CommitDestructions();
		return ;
}

unsigned int prevMili = 0;
unsigned int fps = 0;
void MarioBrosMain::FPSCalculation(){
		SYSTEMTIME st; GetSystemTime(&st);
		unsigned int mili = st.wMilliseconds;
		
		fps++;
		
		if(prevMili == 0){
				prevMili = mili;
		}
		else if(mili - prevMili > 1000) {
				prevMili = 0;
				fps = 0;
		}
		return ;
}

void MarioBrosMain::InitializeGame() {
		al_start_timer(timer);
		currTime =  CurrTime();
		Terrain::Create();
		TerrainStartScreen::Create();
		AnimationFilmHolder::Create(MARIO_SPRITES_BMP);
		
		SpritesHolder* sh = new SpritesHolder();
		
		gameState = Start;

		Items::Init();
		NumbersHolder::Init();
		NumbersHolder::InitTime();
		NumbersHolder::InitMario();
		NumbersHolder::InitWorld();
		NumbersHolder::InitEpi();
		NumbersHolder::InitCoin();
		
		Enemies::Create();
		new Configurator("mario.conf");
		Enemies::MakeShortMap();		

		redraw = true;
}

void ManageGameLoop() {
		using namespace MarioBrosMain;
		
		while(true) {
				currTime =  CurrTime();
				al_wait_for_event(queue, &events);
				al_get_keyboard_state(&keyboardState);
				Rendering(currTime);
				MainLoopOneIteration();
		}
}


int main() {
		using namespace MarioBrosMain;
		
		if(InitAllegro()){
				InitializeGame();
				ManageGameLoop();
		}
		system("PAUSE");
		return 0;
}
