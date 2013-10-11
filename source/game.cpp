#include "game.h"
#include <iostream>
#include "sdlutil.h"
#include <cstdlib>

using namespace std;

static Audio music;

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
			SDL_WM_SetCaption ("Candle Light", NULL);
		}
		if(init_music() == false){
			fprintf(stderr, "Sound could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;

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

//	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	return success;
}

bool
Game::init_music(){
	music.init();
	return true;
}

void
Game::clean_up ()
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
			if (character->jumping == false)
			{
				character->jumping = true;
				character->jumping_speed = character->SPEED_JUMP;
			}
			break;

		case SDLK_a:
			character->moving_left = true;
			character->side = false;
			break;

		case SDLK_d:
			character->moving_right = true;
			character->side = true;
			break;

		case SDLK_f:
				if((character->moving_right == true) or (character->moving_left == true) or (character->jumping == true))
				{
					character->defending = false;
				}
				else
				{
					character->defending = true;
				}
			break;

		case SDLK_q:
//			this->quit = true;
			break;

		case SDLK_p:
			while (this->pause == true)
			{
				if (SDL_WaitEvent(&event))
				{
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
					{
						this->pause = false;
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
			character->moving_left = false;
			character->side = false;
			break;

		case SDLK_d:
			character->moving_right = false;
			character->side = true;
			break;

		case SDLK_w:
			break;	

		case SDLK_f:
			character->defending = false;
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

void
Game::run_ai ()
{

}

void
Game::run_physics ()
{
	if (character->defending == false)
	{
		if (character->moving_right == true)
		{
			character->defending = false;
			character->movement ++;
			level->x_scenario -= character->SPEED_NORMAL;
			if (level->x_scenario < SCREEN_RIGHT_OFFSET)
			{
				level->x_scenario = SCREEN_RIGHT_OFFSET;
				end_game = true;
				quit = true;
			}
		}
	
		if (character->moving_left == true)
		{
			character->defending = false;
			character->movement ++;
			level->x_scenario += character->SPEED_NORMAL;
			if (level->x_scenario > SCREEN_LEFT_OFFSET)
			{
				level->x_scenario = SCREEN_LEFT_OFFSET;
			}
		}

		if (character->jumping == true)
		{
			character->defending = false;
			candle_light->y_position -= character->jumping_speed;
			character->y_position -= character->jumping_speed;
			if (character->y_position <= 250)
			{
				character->jumping_speed *= (-1);
			}
			if (character->y_position >= 360)
			{
				character->y_position = 360;
				character->jumping = false;
			}
		}
	}
}

void
Game::update_game ()
{
	if (character->moving_right == false && character->moving_left == false && character->defending == false)
	{
		if (character->side == true)
		{
			character->character_surface = character->character_idle;
		}
		else
		{
			character->character_surface = character->character_eidle;
		}
	}

	if (character->moving_right == false && character->moving_left == false && character->defending == true)
	{
		if (character->side == true)
		{
			character->character_surface = character->character_protecting_1;
		}
		else
		{
			character->character_surface = character->character_eprotecting_1;
		}
	}	

	if (character->moving_right == true)
	{
		if (character->character_surface == character->character_idle && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_walking_1;
		}
		else if (character->character_surface == character->character_walking_1 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_walking_2;
		}
		else if (character->character_surface == character->character_walking_2 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_walking_3;
		}
		else if (character->character_surface == character->character_walking_3 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_walking_4;
		}
		else if (character->character_surface == character->character_walking_4 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_walking_1;
		}
	}

	if (character->moving_left == true)
	{
		if (character->character_surface == character->character_eidle && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_ewalking_1;
		}
		else if (character->character_surface == character->character_ewalking_1 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_ewalking_2;
		}
		else if (character->character_surface == character->character_ewalking_2 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_ewalking_3;
		}
		else if (character->character_surface == character->character_ewalking_3 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_ewalking_4;
		}
		else if (character->character_surface == character->character_ewalking_4 && character->movement >= SPRITE_RATE)
		{
			character->character_surface = character->character_ewalking_1;
		}
	}

	if (character->movement > SPRITE_RATE)
	{
		character->movement = 0;
	}

	if (perigo == false)
	{
		int num = rand() % 1000;
		if (num == 0)
		{
			perigo = true;
		}
	}

	if (perigo == true)
	{
		nuvem->x_position --;
	}

	if (nuvem->x_position <= -854)
	{
		nuvem->x_position = 855;
		perigo = false;
	}

	if (nuvem->x_position < character->x_position && nuvem->x_position + nuvem->width > character->x_position && character->side == true && character->defending == false)
	{
		end_game = false;
		quit = true;
	}
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

	string music_string = "assets/presents_theme.wav";
	music.setAudio(music_string.c_str());
	music.setVolume(5);

	character = new Character ();

	string scenario_string = "assets/background.png";
	level = new Level (scenario_string);
	level->add_child (character);

	string candle_light_string = "assets/bigcandle.png";
	candle_light = new Light (candle_light_string, 1, 180, 10);
	level->add_child (candle_light);

	nuvem = new Nuvem();
	level->add_child (nuvem);
}

void
Game::init_game ()
{
	float FRAME_MILISECOND = (float) 1/60;

	bool quit = false;
	bool pause = false;

	return ;
}

void
Game::init_screen()
{
	bool game_begin = false;
	initscreen = new Initscreen();
	for(int i=0;i<5;i++)
			music.aumentaVolume();

	initscreen->draw(screen);

	while (game_begin == false)
	{
		if (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
			{
				game_begin = true;
			}
		}
	}
}

void
Game::present_end_game ()
{
	bool bool_end_game = false;

	if (end_game == true)
	{
		end_game_surface = load_image ("assets/youwon.png");
	}
	else
	{
		end_game_surface = load_image ("assets/gameover.png");
	}
	apply_surface (0, 0, end_game_surface, screen);
	SDL_Flip (screen);
	apply_surface (0, 0, end_game_surface, screen);
	SDL_Flip (screen);
	apply_surface (0, 0, end_game_surface, screen);
	SDL_Flip (screen);

	while (bool_end_game == false)
	{
		if (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
			{
				bool_end_game = true;
			}
		}
	}
}

void
Game::loop ()
{
	load_resources ();
	init_screen ();
	init_game ();

	while (is_game_finished () == false)
	{
		update_time_step ();
		handle_events ();
		run_ai ();
		run_physics ();
		update_game ();
		render ();
	}

	present_end_game ();

	clean_up ();

	return ;
}

void
Game::shut_down ()
{
	music.closeAudio();
	SDL_Quit ();

	return ;
}
