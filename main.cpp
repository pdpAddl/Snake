#include "Game.h"
#include <stdlib.h>


enum turn_directions
{
	STAY,
	LEFT_TURN,
	RIGHT_TURN
};


int main()
{
	int p = 20;
	/*

	//Init GUI Game 
	Game_GUI game(p, p, 0.1);

	//Game loop
	while (game.isRunning())
	{
		if (game.clockReady())
		{
			//Update
			game.update();

			//Render
			game.render();

			game.turn(LEFT_TURN);
		}

		
	}

	game.getScore();
	return 0;
}
*/
	
	//Init SIM Game 
	Game_SIM game(p, p);

	//Game loop
	while (game.isRunning())
	{

		//Update
		game.update();
		game.turn(LEFT_TURN);
	}

	game.getScore();

	return 0;
}