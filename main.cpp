#include "Game.h"

int main()
{
	int p = 20;

	//Init Game Engine
	Game game(p, p, 1);
	sf::Clock clock;

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