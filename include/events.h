#ifndef EVENTS_H
#define EVENTS_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>

using namespace std;

class Events : public Gameobject
{
private:

	SDL_Surface* events_surface;


	bool trigger;

	void happen (bool trigger, string filename);

	void draw_self (SDL_Surface* surface);

	void load_message (string filename);



public:
	string filename;

	int map_x;

	int x_position;

	int checkpointplace;

	bool message, checkpoint;

	int create_checkpoint(int x_position, int checkpointplace);

	Events(bool message, bool checkpoint, int x_position, int map_x, string filename);
	~Events();

};

#endif