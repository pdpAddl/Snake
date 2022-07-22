#include "Game.h"

int main()
{
	//Init Game Engine
	Game game(20, 20, 0.5);

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