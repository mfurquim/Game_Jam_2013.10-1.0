#include "initscreen.h"
#include "sdlutil.h"
#include <iostream>

using namespace std;

Initscreen::Initscreen()
{
	this->titlebackground = load_image("assets/background.png");
}

Initscreen::~Initscreen()
{
	if(this->titlebackground != NULL)
	{
		SDL_FreeSurface(this->titlebackground);
	}
}

void
Initscreen::draw_self(SDL_Surface *surface)
{
	SDL_SetAlpha (this->titlebackground, SDL_RLEACCEL | SDL_SRCALPHA, 255);
	apply_surface (0, 0, this->titlebackground, surface);

	return ;
}
