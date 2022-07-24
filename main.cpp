#include "Game.h"
#include <stdlib.h>

#define N 10000

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
	//Init SIM Games
	int turn_direction;
	Game_SIM* games = new Game_SIM[N];


	for (int i = 0; i < N; i++) {
		games[i] = Game_SIM(p, p);
	}
		//Game loop
	for (int i = 0; i < N; i++) {
		while (games[i].isRunning())
		{

			//Update
			games[i].update();

			turn_direction = std::rand() % 3;
			games[i].turn(turn_direction);
		}

		games[i].getScore();
	}

	

	return 0;
}