#include "character.h"
#include "sdlutil.h"
#include <iostream>

Character::Character (string character_string, int initial_position_x, int initial_position_y, int width, int height)
{

	itself.upper_left.x = initial_position_x;
	itself.upper_left.y = initial_position_y;
	itself.width = width;
	itself.height = height;

	movement.x = 0;
	movement.y = 0;

	character_surface = load_image (character_string);
}

void
Character::draw_self (SDL_Surface* surface)
{
	SDL_SetAlpha (this->character_surface, SDL_RLEACCEL | SDL_SRCALPHA, 255);
	apply_surface (x_position, y_position, this->character_surface, surface);
}

Character::~Character()
{
	SDL_FreeSurface (this->character_surface);
}
