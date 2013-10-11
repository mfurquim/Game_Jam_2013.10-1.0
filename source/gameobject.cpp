#include "gameobject.h"

Gameobject::~Gameobject ()
{
	int size = children.size ();
	for (int i = 0; i < size; ++i)
	{
		if (children[i])
		{
			delete children[i];
		}
	}
}

void
Gameobject::add_child (Gameobject* child)
{
	children.push_back (child);
}

void
Gameobject::draw (SDL_Surface* surface)
{
	draw_self (surface);
	int size = children.size ();

	for (int i = size - 1; i >= 0; --i)
	{
		if (children[i])
		{
			children[i]->draw(surface);
		}
	}
}