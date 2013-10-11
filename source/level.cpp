#include "level.h"
#include "sdlutil.h"

Level::Level (string scenario_string)
{
	this->scenario_surface = load_image (scenario_string);
	this->scenario_string = scenario_string;
	this->x_scenario = 0;
}

Level::~Level()
{
	SDL_FreeSurface (this->scenario_surface);
}

void
Level::draw_self (SDL_Surface* surface)
{
	apply_surface (x_scenario, 0, scenario_surface, surface);
}
