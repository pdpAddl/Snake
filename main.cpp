#include "Game.h"

int main()
{
	//Init Game Engine
	Game game(20, 20, 1);
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