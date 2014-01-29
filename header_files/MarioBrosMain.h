#ifndef _MARIO_BROS_MAIN_H_
#define _MARIO_BROS_MAIN_H_

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>

/* our libraries */
#include "animator\Animator.h"
#include "animator\AnimatorHolder.h"
#include "animation\AnimationFilmHolder.h"
#include "terrain\terrain.h"
#include "mario\logic.h"
#include "mario\SpritesHolder.h"
#include "mario\Mario.h"
#include "mario/NumbersHolder.h"
#include "items\Coins.h"
#include "mario\Score.h"
#include "enemies\Enemies.h"
#include "enemies\Goumba.h"
#include "enemies\Piranhas.h"
#include "enemies\GreenKoopaTroopa.h"
#include "items\Items.h"
#include "Objects.h"
#include "collision\Collision.h"
#include "collision\CollisionChecker.h"
#include "sounds\Sounds.h"
#include "conf\parser.h"


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


/* Our Defines */

enum GameState {
	Start = 0,
	Play,
	Pause,
	IsPaused,
	Over
};

extern GameState gameState;

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

		extern void GamePause(timestamp_t now);
		extern void GameStarting();
		extern void ManageTime();
		static bool GameIsStart(){return gameState == Start;}
		static bool GameIsPlay(){return gameState == Play;}
		static bool GameIsPause(){return gameState == Pause;}
		static bool GameIsOver(){return gameState == Over;}
		static void SetGamePlay(){gameState = Play;}
		static void SetGamePause(){gameState = Pause;}
		static void SetGameOver(){gameState = Over;}
		extern void DeathRender();
}

#endif