#include "Game.h"
#include <stdlib.h>
#include <iostream>

#define N 10000
#define SIZE_X 20
#define SIZE_Y 20
#define GAMESPEED 1

enum turn_directions
{
	STAY,
	LEFT_TURN,
	RIGHT_TURN
};


int main()
{
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
	int turn_direction, high_score, score;
	std::vector<directions> moved_directions;
	std::vector<sf::Vector2i> head_pos, food_pos;

	const char* direction_names [4] = {"UP", "RIGHT", "DOWN", "LEFT"};

	Game_SIM* games = new Game_SIM[N];

	high_score = 0;

	for (int i = 0; i < N; i++) {
		games[i] = Game_SIM(SIZE_X, SIZE_Y);
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

		score = games[i].getScore();

		if (score > high_score)
		{
			moved_directions.clear();
			food_pos.clear();

			high_score = score;
			moved_directions = games[i].getMovedDirections();
			food_pos = games[i].getFoodPositions();

			std::cout << "NEW HIGH SCORE BY GAME #"<< i<< ": " << score << std::endl;
			for (int i = 0; i < moved_directions.size(); i++) std::cout << direction_names[moved_directions[i]] << "; ";
			std::cout << std::endl;
			for (int i = 0; i < food_pos.size(); i++) std::cout << food_pos[i].x << "," << food_pos[i].y << "; ";

			Game_REP highscore_game(SIZE_X, SIZE_Y, GAMESPEED, moved_directions, food_pos);
			while (highscore_game.isRunning())
			{
				if (highscore_game.clockReady())
				{
					highscore_game.update();
					highscore_game.render();
				}
				
			}

			moved_directions = highscore_game.getMovedDirections();
			food_pos = highscore_game.getFoodPositions();

			std::cout << std::endl << "REPLAY" << std::endl;
			for (int i = 0; i < moved_directions.size(); i++) std::cout << direction_names[moved_directions[i]] << "; ";
			std::cout << std::endl;
			for (int i = 0; i < food_pos.size(); i++) std::cout << food_pos[i].x << "," << food_pos[i].y << "; ";
			std::cout << std::endl;
		}
	}

	

	return 0;
}