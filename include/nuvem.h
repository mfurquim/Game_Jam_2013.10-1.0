#ifndef NUVEM_H
#define NUVEM_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>

using namespace std;

class Nuvem : public Gameobject
{
private:
	void draw_self (SDL_Surface* surface);

public:
	int width, height;

	SDL_Surface* wind_surface;

	int x_position, y_position;

	Nuvem();
	~Nuvem();

};

#endif