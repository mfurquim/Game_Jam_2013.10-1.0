#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>

using namespace std;

class Character : public Gameobject
{
private:
	int width, height;
	void draw_self (SDL_Surface* surface);


public:

	SDL_Surface* character_surface;

	const bool RIGHT = true;
	const bool LEFT = false;
	bool side; // true = right; false = left

	int movement;
	int x_position, y_position;
	float jumping_speed;
	bool jumping, moving_right, moving_left, jumped, defending;
	Character();
	~Character();

};

#endif