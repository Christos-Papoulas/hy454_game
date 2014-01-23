#ifndef _SOUNDS_H_
#define _SOUNDS_H_

#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <stdio.h>

#define MUSIC_PATH "Data\\Sounds\\smb_music.ogg"
#define JUMP_SMALL_PATH "Data\\Sounds\\smb_jump-small.wav"
#define PAUSE_PATH "Data\\Sounds\\smb_pause.wav"
#define HIT_BRICK "Data\\Sounds\\smb_bump.wav"
#define POWERUP_APPEARS "Data\\Sounds\\smb_powerup_appears.wav"
#define POWERUP "Data\\Sounds\\smb_powerup.wav"
#define MARIO_DEATH "Data\\Sounds\\smb_mariodie.wav"
#define INVINCIBLE_MARIO "Data\\Sounds\\Invincible.ogg"
#define ONE_UP "Data\\Sounds\\smb_1-up.wav"
#define COIN "Data\\Sounds\\smb_coin.wav"
#define FIREWORKS "Data\\Sounds\\smb_fireworks.wav"
#define FLAG "Data\\Sounds\\smb_flagpole.wav"
#define GAME_OVER "Data\\Sounds\\smb_gameover.wav"
#define ENTER_PIPE "Data\\Sounds\\smb_pipe.wav"
#define FINISH "Data\\Sounds\\smb_stage_clear.wav"
#define STOMP "Data\\Sounds\\smb_stomp.wav"
#define VINE "Data\\Sounds\\smb_vine.wav"
#define WARNING "Data\\Sounds\\smb_warning.wav"
#define HURRY_UP "Data\\Sounds\\Hurry_Up.ogg"
#define UNDERGROUND "Data\\Sounds\\Underground.ogg"
#define UNDERGROUND_HURRY_UP "Data\\Sounds\\Underground_Hurry_Up.ogg"



class Sounds{
	public:
		static ALLEGRO_SAMPLE_ID id_music;
		static ALLEGRO_SAMPLE_ID id_jump_small;
		static ALLEGRO_SAMPLE_ID id_pause;
		static ALLEGRO_SAMPLE_ID id_hit_brick;
		static ALLEGRO_SAMPLE_ID id_powerup_appears;
		static ALLEGRO_SAMPLE_ID id_powerup;
		static ALLEGRO_SAMPLE_ID id_mario_death;
		static ALLEGRO_SAMPLE_ID id_Invincible;
		static ALLEGRO_SAMPLE_ID id_one_up;
		static ALLEGRO_SAMPLE_ID id_coin;
		static ALLEGRO_SAMPLE_ID id_fireworks;
		static ALLEGRO_SAMPLE_ID id_flag;
		static ALLEGRO_SAMPLE_ID id_game_over;
		static ALLEGRO_SAMPLE_ID id_enter_pipe;
		static ALLEGRO_SAMPLE_ID id_finish;
		static ALLEGRO_SAMPLE_ID id_stomp;
		static ALLEGRO_SAMPLE_ID id_vine;
		static ALLEGRO_SAMPLE_ID id_warning;
		static ALLEGRO_SAMPLE_ID id_hurry_up;
		static ALLEGRO_SAMPLE_ID id_underground;
		static ALLEGRO_SAMPLE_ID id_underground_hurry_up;

		static ALLEGRO_SAMPLE *music;
		static ALLEGRO_SAMPLE *jump_small;
		static ALLEGRO_SAMPLE *pause;
		static ALLEGRO_SAMPLE *hit_brick;
		static ALLEGRO_SAMPLE *powerup_appears;
		static ALLEGRO_SAMPLE *powerup;
		static ALLEGRO_SAMPLE *mario_death;
		static ALLEGRO_SAMPLE *Invincible;
		static ALLEGRO_SAMPLE *one_up;
		static ALLEGRO_SAMPLE *coin;
		static ALLEGRO_SAMPLE *fireworks;
		static ALLEGRO_SAMPLE *flag;
		static ALLEGRO_SAMPLE *game_over;
		static ALLEGRO_SAMPLE *enter_pipe;
		static ALLEGRO_SAMPLE *finish;
		static ALLEGRO_SAMPLE *stomp;
		static ALLEGRO_SAMPLE *vine;
		static ALLEGRO_SAMPLE *warning;
		static ALLEGRO_SAMPLE *hurry_up;
		static ALLEGRO_SAMPLE *underground;
		static ALLEGRO_SAMPLE *underground_hurry_up;
		static bool InitSounds();
		static void Play(const char* id);
		static void Pause(const char* id);
};

#endif