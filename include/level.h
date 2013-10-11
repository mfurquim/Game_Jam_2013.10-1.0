#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"
#include <string>

using namespace std;

class Level : public Gameobject
{
private:
	SDL_Surface* scenario_surface;
	string scenario_string;

	void draw_self (SDL_Surface* surface);

public:
	int x_scenario;
	Level(string scenario_string);
	~Level();

};

#endif