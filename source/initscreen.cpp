#include "initscreen.h"
#include "sdlutil.h"
#include <iostream>

using namespace std;

Initscreen::Initscreen()
{
	string titlebackground_filename = "assets/background.png";
	string companylogo_filename = "assets/pressenter.png";
	string gamelogo_filename = "assets/titleandbg.png";
//	string gamewind_filename = "";

	this->titlebackground = load_image(titlebackground_filename);
	this->companylogo = load_image(companylogo_filename, true);
	this->gamelogo = load_image(gamelogo_filename);
//	this->gamewind = load_image(gamewind_filename);
}

Initscreen::~Initscreen()
{
	if(this->titlebackground != NULL)
	{
		SDL_FreeSurface(this->titlebackground);
	}
	if(this->companylogo != NULL)
	{
		SDL_FreeSurface(this->companylogo);
	}
	if(this->gamelogo != NULL)
	{
		SDL_FreeSurface(this->gamelogo);
	}
//	if(this->gamewind != NULL)
//	{
//		SDL_FreeSurface(this->gamewind);
//	}
}


//draws the level on the specified surface
void
Initscreen::draw_self(SDL_Surface *surface)
{

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,0,0,0));

	/* BACKGROUND */

	fade_in(this->titlebackground, surface, 80, false);
	SDL_Delay(400);
	fade_in(this->gamelogo, surface, 140, false);
	SDL_Delay(100);
	fade_in(this->companylogo, surface, 80, false);

	return ;
}
