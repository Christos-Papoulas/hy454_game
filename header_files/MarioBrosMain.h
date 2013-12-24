#ifndef _MARIO_BROS_MAIN_H_
#define _MARIO_BROS_MAIN_H_

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* our libraries */
#include "header_files\Animator.h"
#include "header_files\terrain\terrain.h"
#include "header_files\mario\logic.h"

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

const float FPS = 90;
/* Our Defines */
#define SCREEN_WINDOW_WIDTH 800
#define SCREEN_WINDOW_HEIGHT 600

namespace MarioBrosMain {
		extern bool InitAllegro();

		extern void MainLoopOneIteration();

		extern void InputManagement();
		extern void AnimationProgress();
		extern void ArtificialIntelligence();
		extern void CollisionChecking();
		extern void CommitDestructions();
		extern void FPSCalculation();

		extern void InitializeGame();
}

#endif