#include <iostream>
#include "Game.h"


using namespace std;

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