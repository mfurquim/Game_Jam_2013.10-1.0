#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "gameobject.h"

class Initscreen : public Gameobject
{
private:
	SDL_Surface *titlebackground;
	void draw_self(SDL_Surface *surface);

public:
	Initscreen();
	~Initscreen();
};


#endif