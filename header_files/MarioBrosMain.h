#ifndef _MARIO_BROS_MAIN_H_
#define _MARIO_BROS_MAIN_H_

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* our libraries */
#include "animator\Animator.h"
#include "animator\AnimatorHolder.h"
#include "animation\AnimationFilmHolder.h"
#include "terrain\terrain.h"
#include "mario\logic.h"
#include "mario\SpritesHolder.h"
#include "mario\Mario.h"
#include "enemies\Enemies.h"
#include "Objects.h"


/* Alllegro Libraries */
#include <allegro5\allegro5.h> 
#include <allegro5\allegro.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_font.h>

/* Our window. */
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_EVENT events;

ALLEGRO_KEYBOARD_STATE keyboardState;
bool redraw = true;

ALLEGRO_SAMPLE *music=NULL;
ALLEGRO_SAMPLE *jump_small=NULL;
ALLEGRO_SAMPLE *pause=NULL;

const float FPS = 90;
/* Our Defines */
#define MUSIC_PATH "Data\\Sounds\\smb_music.ogg"
#define JUMP_SMALL_PATH "Data\\Sounds\\smb_jump-small.wav"
#define PAUSE_PATH "Data\\Sounds\\smb_pause.wav"

enum GameState {
	Start = 0,
	Play,
	Pause,
	IsPaused,
	Over
};

namespace MarioBrosMain {
		extern bool InitAllegro();

		extern void Rendering(timestamp_t );

		extern void MainLoopOneIteration();

		extern void InputManagement();
		extern void AnimationProgress();
		extern void ArtificialIntelligence();
		extern void CollisionChecking();
		extern void CommitDestructions();
		extern void FPSCalculation();
		extern void StartScreen(timestamp_t now); 
		extern void InitializeGame();

		extern void GamePause();

		int z_pressed = 0;
		int space_pressed = 0;
}

#endif