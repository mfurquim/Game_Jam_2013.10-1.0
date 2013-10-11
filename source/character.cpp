#include "character.h"
#include "sdlutil.h"

Character::Character ()
{
	this->x_position = 397;
	this->y_position = 360;
	this->width = 61;
	this->height = 96;
	this->jumping = false;
	this->moving_right = false;
	this->moving_left = false;
	this->jumping_speed = 0;
	this->side = true;
	this->movement = 0;
	this->defending = false;

	character_surface = load_image ("assets/idle1.png", true);
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
