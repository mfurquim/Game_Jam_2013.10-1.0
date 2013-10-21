#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "timer.h"
#include "character.h"
//#include "initscreen.h"
#include "level.h"
//#include "audio.h"

using namespace std;

class Game
{
	const int FRAME_RATE = 30;
	const int SCREEN_BPP = 32;
	float FRAME_MILISECOND;

	bool quit = false;
	bool pause = false;

	SDL_Event event;
	SDL_Surface *screen;

	Character* character;
	Level* level;

	Timer frameTime;

//	Initscreen* initscreen;

	void init_screen ();
	void load_resources ();
	int check_if_skip ();

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
	bool initGUI ();
	void loop ();
	void shut_down ();
};

#endif