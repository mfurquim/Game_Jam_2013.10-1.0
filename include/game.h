#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "timer.h"
#include "character.h"
#include "initscreen.h"
#include "level.h"
#include "light.h"
#include "audio.h"
#include "nuvem.h"

using namespace std;

class Game
{
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;
	const static int SCREEN_BPP = 32;
	float FRAME_MILISECOND = (float) 1/60;
	const int SCREEN_RIGHT_OFFSET = 854 - 8540;
	const int SCREEN_LEFT_OFFSET = 0;

	bool quit = false;
	bool pause = false;
	bool perigo = false;
	bool end_game = false;

	const int SPRITE_RATE = 20;

	SDL_Event event;
	SDL_Surface *screen;
	SDL_Surface *end_game_surface;

	Character* character;
	Level* level;
	Light* candle_light;
	Nuvem* nuvem;

	Timer frameTime;

	Initscreen* initscreen;

	void init_screen ();
	void load_resources ();
	int check_if_skip ();
	void present_end_game ();

	void handle_event_keyup (SDL_Event& event);
	void handle_event_keydown (SDL_Event& event);
	void handle_event_type (SDL_Event& event);

	bool is_game_finished ();

	void clean_up ();
	bool init_SDL ();
	void init_game ();

	void update_time_step ();
	void handle_events ();
	void run_ai ();
	void run_physics ();
	void update_game ();
	int render ();

public:
	bool init_music();
	bool initGUI ();
	void loop ();
	void shut_down ();
};

#endif