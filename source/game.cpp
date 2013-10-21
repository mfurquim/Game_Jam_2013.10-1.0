#include "game.h"
#include <iostream>
#include "sdlutil.h"
#include <cstdlib>

using namespace std;

bool
Game::init_SDL ()
{
	bool success = true;

	if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

		if (screen == NULL)
		{
			fprintf(stderr, "Screen could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_WM_SetCaption ("Game Jam 2013/10 1.0", NULL);
		}
	}

	srand(time(NULL));

	return success;	
}

bool
Game::initGUI ()
{
	bool success = true;

	if (init_SDL () == false)
	{
		fprintf(stderr, "Game could not be initialized!\n");
		success = false;
	}

	return success;
}

void
Game::release_resources ()
{

	return ;
}

void
Game::update_time_step ()
{
	frameTime.start ();

	return ;
}

void
Game::handle_event_keydown (SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			this->quit = true;
			break;

		case SDLK_w:
			character->jump (true);
			break;

		case SDLK_a:
			character->move_left (true);
			break;

		case SDLK_d:
			character->move_right (true);
			break;

		case SDLK_q:
			this->quit = true;
			break;

		case SDLK_p:
			this->pause = true;
			while (this->pause == true)
			{
				if (SDL_WaitEvent(&event))
				{
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
					{
						this->pause = false;
					}

					if (even.type == SDL_KEYDOWN && even.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
					{
						this->pause = false;
						this->quit = true;
					}
				}
			}
			break;

		default:
			break;
	}
}

void
Game::handle_event_keyup (SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_a:
			character->move_left (false);
			break;

		case SDLK_d:
			character->move_right (false);
			break;

		case SDLK_w:
			character->jump (false);
			break;

		default:
			break;
	}
}

void
Game::handle_event_type (SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			this->quit = true;
			break;

		case SDL_KEYDOWN:
			handle_event_keydown (event);
			break;

		case SDL_KEYUP:
			handle_event_keyup (event);
			break;

		default:
			break;
	}
}

bool
Game::is_game_finished ()
{
	return this->quit;
}

void
Game::handle_events ()
{
	while (SDL_PollEvent (&event))
	{
		handle_event_type (event);
	}

	return ;
}
/*
void
Game::run_ai ()
{

}
*/
void
Game::run_physics ()
{
	character->update (level);
}

void
Game::update_game ()
{

}

int
Game::check_if_skip ()
{
	if (frameTime.get_ticks () < FRAME_MILISECOND)
	{
		frameTime.wait_diff (FRAME_MILISECOND);
		return 0;
	}
	return -1;
}

int
Game::render ()
{
	int error = 0;

	if (check_if_skip () < 0)
	{
		return -1;
	}
	
	level->draw(screen);

	error = SDL_Flip (screen);
	if (error < 0)
	{
		fprintf(stderr, "Screen could not be fliped!\n");
		return error;
	}
}

void
Game::load_resources ()
{
/*
	music.setAudio(music_string.c_str());
	music.setVolume(5);
*/
	string character_string = "assets/foo.png";

	Point character_upper_left;
	character_upper_left.x = 100;
	character_upper_left.y = 200;

	Box character_box;
	character_box.upper_left = character_upper_left;
	character_box.width = 30;
	character_box.height = 60;

	character = new Character (character_string, character_box);

	string scenario_string = "assets/background.png";
	level = new Level (scenario_string);
	level->add_child (character);
}

void
Game::init_game ()
{
	float FRAME_MILISECOND = (float) 1/FRAME_RATE;

	bool quit = false;
	bool pause = false;

	return ;
}

void
Game::loop ()
{
	load_resources ();
	init_game ();

	while (is_game_finished () == false)
	{
		update_time_step ();
		handle_events ();
		run_physics ();
		update_game ();
		render ();
	}

	release_resources ();

	return ;
}

void
Game::release_resources ()
{
	delete (level);
}


void
Game::shut_down ()
{
	SDL_Quit ();

	return ;
}
