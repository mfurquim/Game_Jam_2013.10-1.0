#include "game.h"

int main ()
{
	Game game;

	if (game.initGUI () < 0)
	{
		fprintf(stderr, "Game could not be initialized!\n");
		return -1;
	}

	game.loop ();
	game.shut_down();

	return 0;
}