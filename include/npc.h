#ifndef NPC_H
#define NPC_H

#include <SDL/SDL.h>
#include "gameobject.h"
#include <string>

using namespace std;

class Npc : public Gameobject
{
private:
	int width, height;
	void draw_self (SDL_Surface* surface);

	SDL_Surface* npc_surface;

public:
	const static int SPEED_SLOW = 1;
	const static int SPEED_NORMAL = 2;
	const static int SPEED_FAST = 3;
	const static int SPEED_JUMP = 4;
	const static int MAX_JUMP_HEIGHT = 240;

	int x_position, y_position;
	float jumping_speed;
	bool jumping, moving_right, moving_left, jumped;
	Npc(string filename, int x_position, int y_position);
	~Npc();

};

#endif