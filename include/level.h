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

	static const int WIDTH = 854;
	static const int HEIGHT = 480;

	void draw_self (SDL_Surface* surface);

public:
	int x_scenario;
	Level(string scenario_string);
	~Level();

};

#endif