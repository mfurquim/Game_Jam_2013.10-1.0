#ifndef Light_H
#define Light_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>

using namespace std;

class Light : public Gameobject
{
private:
	SDL_Surface* light;
	SDL_Surface* bglight;
	int already_on;

	void candle_fire(int type, int opacity, int life);
	void draw_self (SDL_Surface* surface);

public:
	int life;
	int opacity;
	int type;
	int y_position;
	
	Light(string filename,int type,int opacity, int life);
	~Light();

};

#endif