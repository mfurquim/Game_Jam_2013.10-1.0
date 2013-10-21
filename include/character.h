#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>
#include "level.h"
#include "primitives.h"

using namespace std;

class Character : public Gameobject
{
private:
	Box itself;
	void draw_self (SDL_Surface* surface);
	Vector2d movement;

public:
	Character (string character_string, int initial_position_x, int initial_position_y, int width = 30, int height = 60);
	Character (string character_string, Box itself);
	~Character();

	void move_left (bool enable);
	void move_right (bool enable);
	void jump (bool enable);

};

#endif