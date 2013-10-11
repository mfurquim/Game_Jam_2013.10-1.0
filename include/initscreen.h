#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "gameobject.h"

class Initscreen : public Gameobject
{
private:
//	SDL_Surface *initScreen;
	SDL_Surface *titlebackground;
	SDL_Surface *companylogo;
	SDL_Surface *gamelogo;
//	SDL_Surface *gamewind;
	void draw_self(SDL_Surface *surface);

public:
	Initscreen();
	~Initscreen();
};


#endif