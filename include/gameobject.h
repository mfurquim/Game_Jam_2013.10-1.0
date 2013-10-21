#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <SDL/SDL.h>

using namespace std;

class Gameobject
{
private:
	vector<Gameobject*> children;
	virtual void draw_self (SDL_Surface* surface) = 0;

public:
	virtual ~Gameobject();

	void draw (SDL_Surface* surface);
	void add_child (Gameobject* child);
};

#endif