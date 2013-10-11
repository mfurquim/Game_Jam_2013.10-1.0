#include "sdlutil.h"
#include <SDL/SDL_image.h>
#include <iostream>

using namespace std;

const int FRAMES_PER_SECOND = 20;

SDL_Surface* load_image (string filename, bool alpha)
{
	SDL_Surface* loaded_image = NULL;
	SDL_Surface* optimized_image = NULL;
	loaded_image = IMG_Load (filename.c_str());

	if (loaded_image != NULL)
	{
		if (alpha == true)
		{
			optimized_image = SDL_DisplayFormatAlpha (loaded_image);
		}
		else
		{
			optimized_image = SDL_DisplayFormat (loaded_image);
		}

		SDL_FreeSurface (loaded_image);

		if (optimized_image != NULL && alpha == false)
		{
			Uint32 colorkey = SDL_MapRGB (optimized_image->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey (optimized_image, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimized_image;
}

void apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, NULL, destination, &offset);

	return ;
}

void fade_in(SDL_Surface* surface, SDL_Surface* screen, int times, bool alpha)
{
	int i;

	for (i=2;i<=256;i = i+10)
	{
		SDL_Delay(times);
		if (alpha == true)
		SDL_SetAlpha(surface,SDL_RLEACCEL |SDL_SRCCOLORKEY| SDL_SRCALPHA,(Uint8)i);
		else
		SDL_SetAlpha(surface,SDL_RLEACCEL | SDL_SRCALPHA,(Uint8)i);	
		apply_surface(0,0,surface, screen);
		SDL_Flip(screen);

	}

	return ;
}

void fade_out(SDL_Surface* surface, SDL_Surface* screen, int times, bool alpha)
{
	int i;

	for (i=255;i>=2;i = i>>=1)
	{
		SDL_Delay(times);	
		if (alpha == true)
		SDL_SetAlpha(surface,SDL_RLEACCEL | SDL_SRCALPHA,(Uint8)i);
		else
		SDL_SetAlpha(surface,SDL_RLEACCEL | SDL_SRCALPHA,(Uint8)i);	
		apply_surface(0,0,surface, screen);
		SDL_Flip(screen);
	}

	return ;
} 