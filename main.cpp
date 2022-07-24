#include "Game.h"

int main()
{
	int p = 20;

	//Init Game Engine
	Game_GUI game(p, p, 1);
	sf::Clock clock;

	//Game loop
	while (game.isRunning())
	{

		//Update
		game.update();

		//Render
		game.render();
	}

	game.getScore();

	return 0;
}