#include "Game.h"



int main()
{
	//Init Game Engine

	Game game;

	//Game loop
	while (game.isRunning())
	{

		//Update
		game.update();

		//Render
		game.render();

	}


	return 0;
}