#include "Sounds.h"

ALLEGRO_SAMPLE_ID Sounds::id_music;
ALLEGRO_SAMPLE_ID Sounds::id_jump_small;
ALLEGRO_SAMPLE_ID Sounds::id_pause;
ALLEGRO_SAMPLE_ID Sounds::id_hit_brick;
ALLEGRO_SAMPLE_ID Sounds::id_powerup_appears;
ALLEGRO_SAMPLE_ID Sounds::id_powerup;
ALLEGRO_SAMPLE_ID Sounds::id_mario_death;
ALLEGRO_SAMPLE_ID Sounds::id_Invincible;
ALLEGRO_SAMPLE_ID Sounds::id_one_up;
ALLEGRO_SAMPLE_ID Sounds::id_coin;
ALLEGRO_SAMPLE_ID Sounds::id_fireworks;
ALLEGRO_SAMPLE_ID Sounds::id_flag;
ALLEGRO_SAMPLE_ID Sounds::id_game_over;
ALLEGRO_SAMPLE_ID Sounds::id_enter_pipe;
ALLEGRO_SAMPLE_ID Sounds::id_finish;
ALLEGRO_SAMPLE_ID Sounds::id_stomp;
ALLEGRO_SAMPLE_ID Sounds::id_vine;
ALLEGRO_SAMPLE_ID Sounds::id_warning;
ALLEGRO_SAMPLE_ID Sounds::id_hurry_up;
ALLEGRO_SAMPLE_ID Sounds::id_underground;
ALLEGRO_SAMPLE_ID Sounds::id_underground_hurry_up;
ALLEGRO_SAMPLE_ID Sounds::id_jump_super;

ALLEGRO_SAMPLE *Sounds::music=NULL;
ALLEGRO_SAMPLE *Sounds::jump_small=NULL;
ALLEGRO_SAMPLE *Sounds::pause=NULL;
ALLEGRO_SAMPLE *Sounds::hit_brick=NULL;
ALLEGRO_SAMPLE *Sounds::powerup_appears=NULL;
ALLEGRO_SAMPLE *Sounds::powerup=NULL;
ALLEGRO_SAMPLE *Sounds::mario_death=NULL;
ALLEGRO_SAMPLE *Sounds::Invincible=NULL;
ALLEGRO_SAMPLE *Sounds::one_up;
ALLEGRO_SAMPLE *Sounds::coin;
ALLEGRO_SAMPLE *Sounds::fireworks;
ALLEGRO_SAMPLE *Sounds::flag;
ALLEGRO_SAMPLE *Sounds::game_over;
ALLEGRO_SAMPLE *Sounds::enter_pipe;
ALLEGRO_SAMPLE *Sounds::finish;
ALLEGRO_SAMPLE *Sounds::stomp;
ALLEGRO_SAMPLE *Sounds::vine;
ALLEGRO_SAMPLE *Sounds::warning;
ALLEGRO_SAMPLE *Sounds::hurry_up;
ALLEGRO_SAMPLE *Sounds::underground;
ALLEGRO_SAMPLE *Sounds::underground_hurry_up;
ALLEGRO_SAMPLE *Sounds::jump_super;
ALLEGRO_SAMPLE *Sounds::fire;

bool Sounds::InitSounds() {
	if (!al_reserve_samples(23)){
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	music = al_load_sample(MUSIC_PATH);
	jump_small = al_load_sample(JUMP_SMALL_PATH);
	pause = al_load_sample(PAUSE_PATH);
	hit_brick = al_load_sample(HIT_BRICK);
	powerup_appears = al_load_sample(POWERUP_APPEARS);
	powerup = al_load_sample(POWERUP);
	mario_death = al_load_sample(MARIO_DEATH);
	Invincible = al_load_sample(INVINCIBLE_MARIO);
	one_up = al_load_sample(ONE_UP);
	coin = al_load_sample(COIN);
	fireworks = al_load_sample(FIREWORKS);
	flag = al_load_sample(FLAG);
	game_over = al_load_sample(GAME_OVER);
	enter_pipe = al_load_sample(ENTER_PIPE);
	finish = al_load_sample(FINISH);
	stomp = al_load_sample(STOMP);
	vine = al_load_sample(VINE);
	warning = al_load_sample(WARNING);
	hurry_up = al_load_sample(HURRY_UP);
	underground = al_load_sample(UNDERGROUND);
	underground_hurry_up = al_load_sample(UNDERGROUND_HURRY_UP);
	jump_super = al_load_sample(JUMP_SUPER);
	fire = al_load_sample(FIRE);

	if (!music || !fire || !jump_small || !pause || !hit_brick || !powerup_appears || !powerup || !mario_death || !Invincible || !one_up || !coin || !fireworks || !flag || !game_over || !enter_pipe || !finish || !stomp || !vine || !warning || !hurry_up || !underground || !underground_hurry_up || !jump_super) {
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}
	return true;
}

void Sounds::Play(const char* id) {
	if(id == "music"){
		al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_music);
	}else if(id == "jump_small") {
		al_play_sample(jump_small, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_jump_small);
	}else if(id == "pause") {
		al_play_sample(pause, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_pause);
	}else if(id == "hit_brick") {
		al_play_sample(hit_brick, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_hit_brick);
	}else if(id == "powerup_appears") {
		al_play_sample(powerup_appears, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_powerup_appears);
	}else if(id == "powerup") {
		al_play_sample(powerup, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_powerup);
	}else if(id == "mario_death") {
		al_play_sample(mario_death, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_mario_death);
	}else if(id == "Invincible") {
		al_play_sample(Invincible, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_Invincible);
	}else if(id == "one_up") {
		al_play_sample(one_up, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_one_up);
	}else if(id == "coin") {
		al_play_sample(coin, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_coin);
	}else if(id == "fireworks") {
		al_play_sample(fireworks, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_fireworks);
	}else if(id == "flag") {
		al_play_sample(flag, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_flag);
	}else if(id == "game_over") {
		al_play_sample(game_over, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_game_over);
	}else if(id == "enter_pipe") {
		al_play_sample(enter_pipe, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_enter_pipe);
	}else if(id == "finish") {
		al_play_sample(finish, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_finish);
	}else if(id == "stomp") {
		al_play_sample(stomp, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_stomp);
	}else if(id == "vine") {
		al_play_sample(vine, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_vine);
	}else if(id == "warning") {
		al_play_sample(warning, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_warning);
	}else if(id == "hurry_up") {
		al_play_sample(hurry_up, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_hurry_up);
	}else if(id == "underground") {
		al_play_sample(underground, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_underground);
	}else if(id == "underground_hurry_up") {
		al_play_sample(underground_hurry_up, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_underground_hurry_up);
	}else if(id == "jump_super") {
		al_play_sample(jump_super, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&id_jump_super);
	}else if(id == "fire") {
		al_play_sample(fire, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	
}

void Sounds::Pause(const char* id) {
	if(id == "music"){
		al_stop_sample(&id_music);
	}else if(id == "jump_small") {
		al_stop_sample(&id_jump_small);
	}else if(id == "pause") {
		al_stop_sample(&id_pause);
	}else if(id == "hit_brick") {
		al_stop_sample(&id_hit_brick);
	}else if(id == "powerup_appears") {
		al_stop_sample(&id_powerup_appears);
	}else if(id == "powerup") {
		al_stop_sample(&id_powerup);
	}else if(id == "mario_death") {
		al_stop_sample(&id_mario_death);
	}else if(id == "Invincible") {
		al_stop_sample(&id_Invincible);
	}else if(id == "one_up") {
		al_stop_sample(&id_one_up);
	}else if(id == "coin") {
		al_stop_sample(&id_coin);
	}else if(id == "fireworks") {
		al_stop_sample(&id_fireworks);
	}else if(id == "flag") {
		al_stop_sample(&id_flag);
	}else if(id == "game_over") {
		al_stop_sample(&id_game_over);
	}else if(id == "enter_pipe") {
		al_stop_sample(&id_enter_pipe);
	}else if(id == "finish") {
		al_stop_sample(&id_finish);
	}else if(id == "stomp") {
		al_stop_sample(&id_stomp);
	}else if(id == "vine") {
		al_stop_sample(&id_vine);
	}else if(id == "warning") {
		al_stop_sample(&id_warning);
	}else if(id == "hurry_up") {
		al_stop_sample(&id_hurry_up);
	}else if(id == "underground") {
		al_stop_sample(&id_underground);
	}else if(id == "underground_hurry_up") {
		al_stop_sample(&id_underground_hurry_up);
	}else if(id == "jump_super") {
		al_stop_sample(&id_jump_super);
	}
	
}