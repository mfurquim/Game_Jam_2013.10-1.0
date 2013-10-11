#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <SDL/SDL.h>
#include <string>

using namespace std;

SDL_Surface* load_image (string filename, bool alpha = false);
void apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool load_files ();
void fade_in (SDL_Surface* surface, SDL_Surface* screen,int times, bool alpha);
void fade_out (SDL_Surface* surface, SDL_Surface* screen,int times,bool alpha);
#endif