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

		if (!al_reserve_samples(2)){
			fprintf(stderr, "failed to reserve samples!\n");
			return false;
		}

		music = al_load_sample(MUSIC_PATH);
		jump_small = al_load_sample(JUMP_SMALL_PATH);
		if (!music) {
			printf( "Audio clip sample not loaded!\n" ); 
			return false;
		}
		if (!jump_small) {
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
		if (gameState == Play){
			Terrain::DisplayTerrain(al_get_backbuffer(display), now);
			AnimatorHolder::Display(al_get_backbuffer(display)); 		// @todo working properly;
		}

		
		al_flip_display(); // is blocking depending on defines?
}

//game loop logic
void MarioBrosMain::MainLoopOneIteration() {
		InputManagement(); //just reads from local input queue
		AnimationProgress();
		//ArtificialIntelligence();
		CollisionChecking();
		//CommitDestructions();
		//FPSCalculation();
}

void MarioBrosMain::InputManagement(){
		if(1) {
				if(al_key_down(&keyboardState, ALLEGRO_KEY_UP)) // up
						return ; // @todo something
				else if(al_key_down(&keyboardState, ALLEGRO_KEY_DOWN)) // down
						return ; // @todo something
				else if(al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)) // right
						return Mario::MarioMovesRight();
				else if(al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)) // lest
						return Mario::MarioMovesLeft();
				else if(al_key_down(&keyboardState, ALLEGRO_KEY_Z)){ // z
					if(!z_pressed){
						al_play_sample(jump_small, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						z_pressed = 1;
					}
					
					return Mario::MarioStandingJump();
				}
				else if(!al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)){
					z_pressed = 0;
				}
				else
						return ; // other keys...
		}
}

void MarioBrosMain::StartScreen(timestamp_t now) {
	TerrainStartScreen::DisplayTerrain(al_get_backbuffer(display), now);
	if((al_key_down(&keyboardState, ALLEGRO_KEY_ENTER)) && gameState == Start){ // enter
		gameState = Play;
		al_play_sample(music, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
		
	}

}

void MarioBrosMain::AnimationProgress(){
		AnimatorHolder::Progress(GetCurrTime());
		return ;
}

void MarioBrosMain::ArtificialIntelligence(){
		assert(0 && "Unimpemented");
		return ;
}


void MarioBrosMain::CollisionChecking(){
		Collision::CheckGroundCollision();
		return ;
}

void MarioBrosMain::CommitDestructions(){
		assert(0 && "Unimpemented");
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
		SpritesHolder* lala = new SpritesHolder();
		gameState = Start;
		redraw = true;
}

void ManageGameLoop() {
		using namespace MarioBrosMain;
		
		while(true) {
				currTime =  CurrTime();
				al_wait_for_event(queue, &events);
				al_get_keyboard_state(&keyboardState);
				Rendering(currTime);
				(((Terrain::GetTerrain())->GetTileLayer())->GetViewWindow()).IncreaseY(1);
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



















// from here and below are skata only for looking when we dont
// know what to do.

/* Our tiles atlas. */
ALLEGRO_BITMAP *tiles;
/* Our tilemap. */
int tile_map[100 * 100];
/* Keep track of pressed mouse button. */
int mouse;
/* Camera parameters. */
float zoom = 1.0, rotate;
float scroll_x, scroll_y;
/* Our icon and font. */
ALLEGRO_BITMAP *icon;
ALLEGRO_FONT *font;
/* Simple FPS counter. */
int fps, fps_accum;
double fps_time;

/* Places a single tile into the tile atlas.
 * Normally you would load the tiles from a file.
 */
void tile_draw(int i, float x, float y, float w, float h) {
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    switch (i) {
        case 0:
            al_draw_filled_rectangle(x, y, x + w, y + h, black);
            break;
        case 1:
            al_draw_filled_rectangle(x, y, x + w, y + h, red);
            al_draw_filled_circle(x + w * 0.5, y + h * 0.5, w * 0.475,
                yellow);
            break;
        case 2:
            al_draw_filled_rectangle(x, y, x + w, y + h, yellow);
            al_draw_filled_triangle(x + w * 0.5, y + h * 0.125,
                x + w * 0.125, y + h * 0.875,
                x + w * 0.875, y + h * 0.875, red);
            break;
        case 3:
            al_draw_filled_rectangle(x, y, x + w, y + h, black);
            if (icon)
                al_draw_scaled_bitmap(icon, 0, 0, 48, 48,
                    x, y, w, h, 0);
            break;
    }
}

/* Creates the tiles and a random 100x100 map. */
void tile_map_create(void) {
    int i;
    int x, y;
    /* Create the tile atlas. */
    tiles = al_create_bitmap(1024, 1024);
    al_set_target_bitmap(tiles);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    for (i = 0; i < 4; i++) {
        /* We draw the tiles a bit bigger (66x66 instead of 64x64)
         * to account for the linear filtering. Normally just leaving
         * the border transparent for sprites or repeating the border
         * for tiling tiles should work well.
         */
        tile_draw(i, i * 66, 0, 66, 66);
    }
    al_set_target_backbuffer(display);

    /* Create the random map. */
    for (y = 0; y < 100; y++) {
        for (x = 0; x < 100; x++) {
            tile_map[x + y * 100] = rand() % 4;
        }
    }

    /* Center of map. */
    scroll_x = 100 * 32 / 2;
    scroll_y = 100 * 32 / 2;
}

/* Draws the complete map. */
void tile_map_draw(void) {
    int x, y;
    ALLEGRO_TRANSFORM transform;
    float w, h;

    w = al_get_display_width(display);
    h = al_get_display_height(display);

    /* Initialize transformation. */
    al_identity_transform(&transform);
    /* Move to scroll position. */
    al_translate_transform(&transform, -scroll_x, -scroll_y);
    /* Rotate and scale around the center first. */
    al_rotate_transform(&transform, rotate);
    al_scale_transform(&transform, zoom, zoom);
    /* Move scroll position to screen center. */
    al_translate_transform(&transform, w * 0.5, h * 0.5);
    /* All subsequent drawing is transformed. */
    al_use_transform(&transform);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_hold_bitmap_drawing(1);
    for (y = 0; y < 100; y++) {
        for (x = 0; x < 100; x++) {
            int i = tile_map[x + y * 100];
            float u = 1 + i * 66;
            float v = 1;
            al_draw_scaled_bitmap(tiles, u, v, 64, 64,
                x * 32, y * 32, 32, 32, 0);
        }
    }
    al_hold_bitmap_drawing(0);

    al_identity_transform(&transform);
    al_use_transform(&transform);
}

/*int main(void) {
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    bool redraw = true;

    srand(time(NULL));

    // Init Allegro 5 + addons. 
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_install_mouse();
    al_install_keyboard();
    // Create our window. 
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(640, 480);
    al_set_window_title(display, "Allegro 5 Tilemap Example");
    // The example will work without those, but there will be no
    // FPS display and no icon.
    //
    font = al_load_font("fixed_font.tga", 0, 0);
    icon = al_load_bitmap("icon.tga");
    if (icon)
        al_set_display_icon(display, icon);

    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    tile_map_create();

    timer = al_create_timer(1.0 / 60);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse = event.mouse.button;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse = 0;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            // Left button scrolls
            if (mouse == 1) {
                float x = event.mouse.dx / zoom;
                float y = event.mouse.dy / zoom;
                scroll_x -= x * cos(rotate) + y * sin(rotate);
                scroll_y -= y * cos(rotate) - x * sin(rotate);
            }
            // Right button zooms/rotates.
            if (mouse == 2) {
                rotate += event.mouse.dx * 0.01;
                zoom += event.mouse.dy * 0.01 * zoom;
            }
            zoom += event.mouse.dz * 0.1 * zoom;
            if (zoom < 0.1) zoom = 0.1;
            if (zoom > 10) zoom = 10;
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            al_acknowledge_resize(display);
            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            double t = al_get_time();
            tile_map_draw();
            if (font) {
                al_draw_filled_rounded_rectangle(4, 4, 100, 30,
                    8, 8, al_map_rgba(0, 0, 0, 200));
                al_draw_textf(font, al_map_rgb(255, 255, 255),
                    54, 8, ALLEGRO_ALIGN_CENTRE, "FPS: %d", fps);
            }
            al_flip_display();
            fps_accum++;
            if (t - fps_time >= 1) {
                fps = fps_accum;
                fps_accum = 0;
                fps_time = t;
            }
        }
    }
    return 0;
} */


/*
// 1st example by the additional lesson materials.

int main()
{
	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init()){
		fprintf(stderr, "failed to initialize allegro\n");
		return -1;
	}

	display = al_create_display(600, 480);
	if(!display){
		fprintf(stderr, "failed to create display\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0,100,0));
	al_flip_display();
	int i = 0;
	do
	{
			putpixel(screan, 50, 50, makecol(255,255,255));
			al_rest(1.0);
	}while(i++ < 10);
	al_rest(10.0);
	al_destroy_display(display);
	return 0;
}

*/
