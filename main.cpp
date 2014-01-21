#include "header_files\MarioBrosMain.h"
GameState gameState = Start;

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

		if (!al_reserve_samples(7)){
			fprintf(stderr, "failed to reserve samples!\n");
			return false;
		}

		music = al_load_sample(MUSIC_PATH);
		jump_small = al_load_sample(JUMP_SMALL_PATH);
		pause = al_load_sample(PAUSE_PATH);
		hit_brick = al_load_sample(HIT_BRICK);
		red_mushroom_spawn = al_load_sample(RED_MUSHROOM_SPAWN);
		red_mushroom_get = al_load_sample(RED_MUSROOM_GET);
		mario_death = al_load_sample(MARIO_DEATH);
		if (!music || !jump_small || !pause || !hit_brick || !red_mushroom_spawn || !red_mushroom_get || !mario_death) {
			printf( "Audio clip sample not loaded!\n" ); 
			return false;
		}

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
		}

		
		al_flip_display(); // is blocking depending on defines?
}

//game loop logic
void MarioBrosMain::MainLoopOneIteration() {
	InputManagement(); //just reads from local input queue
	if(gameState == Play){
		AnimationProgress();
		CollisionChecking();
		ArtificialIntelligence();
		Mario::MoveViewWin();
		CommitDestructions();
		//FPSCalculation();
	}
}

void MarioBrosMain::InputManagement(){
	if(!al_key_down(&keyboardState, ALLEGRO_KEY_LEFT))
		z_pressed = 0;
	if(!al_key_down(&keyboardState, ALLEGRO_KEY_SPACE))
		space_pressed = 0;

	if(gameState == Pause){
		if(al_key_down(&keyboardState, ALLEGRO_KEY_SPACE)){ // space
			if(!space_pressed){
				al_play_sample(pause, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				GamePause(currTime);
				space_pressed = 1;
			}
		}
		return ;
	}

	if(!Mario::isWalkingJump() &&  gameState == Play) {
				if(al_key_down(&keyboardState, ALLEGRO_KEY_Z) && al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)){
					if(!z_pressed){
						al_play_sample(jump_small, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						z_pressed = 1;
					}
						if(Mario::isWalking() && !Mario::isWalkingJump()){
							return Mario::MarioWalkingJump();
						}
				}
				if(al_key_down(&keyboardState, ALLEGRO_KEY_Z) && al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)){
						if(Mario::isBackWalk()){
							return Mario::BackWalkAndJump();
						}
				}
				if(al_key_down(&keyboardState, ALLEGRO_KEY_DOWN)){ // down
						return Mario::EnterPipe(); // @todo something
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)){ // right
						Mario::GetOutFromPipe();
						return Mario::MarioMovesRight();
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)){ // lest
						return Mario::MarioMovesLeft();
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_SPACE)){ // space
					if(!space_pressed){
						al_play_sample(pause, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						GamePause(currTime);
						space_pressed = 1;
					}
					return ;
				}else if(al_key_down(&keyboardState, ALLEGRO_KEY_Z)){ // z
					if(!z_pressed){
						al_play_sample(jump_small, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						z_pressed = 1;
					}
					if(!Mario::isStandingJumping())
						return Mario::MarioStandingJump();
				}else{
						return ; // other keys...
				}
				al_flush_event_queue(queue);
		}
}

void MarioBrosMain::StartScreen(timestamp_t now) {
	TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
	if((al_key_down(&keyboardState, ALLEGRO_KEY_ENTER)) && gameState == Start){ // enter
		gameState = Play;
		//al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
	}
}

void MarioBrosMain::GamePause(timestamp_t now) {
	if(gameState == Play){
		gameState = Pause;
		TerrainStartScreen::CreatePause();
	}else if(gameState == Pause){
		gameState = Play;
		AnimatorHolder::SetTime(now);
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
		
		return ;
}


void MarioBrosMain::CollisionChecking(){
		Collision::CheckCollision();
		return ;
}

void MarioBrosMain::CommitDestructions(){
		Goumbas::SuspendGoumbas();
		Items::SuspendBricks();
		return ;
}

void MarioBrosMain::FPSCalculation(){
		assert(0 && "Unimpemented");
		return ;
}

void MarioBrosMain::InitializeGame() {
		al_start_timer(timer);
		currTime =  CurrTime();
		Terrain::Create();
		TerrainStartScreen::Create();
		AnimationFilmHolder::Create(MARIO_SPRITES_BMP);
		
		SpritesHolder* sh = new SpritesHolder();
		Enemies::Create();
		gameState = Start;

		
		Items::Init();
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
