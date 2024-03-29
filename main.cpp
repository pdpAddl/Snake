#include "Game.h"
#include <stdlib.h>
#include <iostream>

#define N 5
#define SIZE_X 20
#define SIZE_Y 20
#define GAMESPEED 1
#define GAMEMODE 1

enum turn_directions
{
	STAY,
	LEFT_TURN,
	RIGHT_TURN
};


int main()
{

#if GAMEMODE == 0:

	//Init GUI Game 
	Game_GUI game(SIZE_X, SIZE_Y, GAMESPEED);

	//Game loop
	while (game.isRunning())
	{
		if (game.clockReady())
		{
			//Update
			game.update();

			//Render
			game.render();
		}
	}

	game.getScore();




#elif GAMEMODE == 1:

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
		}
	}

#elif GAMEMODE == 2:

	//Init SIM Games
	int turn_direction, high_score, score;
	std::vector<directions> moved_directions;
	std::vector<sf::Vector2i> head_pos, food_pos;

	const char* direction_names[4] = { "UP", "RIGHT", "DOWN", "LEFT" };

	Game_GUI* games = new Game_GUI[N];
	//Game_GUI game(SIZE_X, SIZE_Y, GAMESPEED);

	high_score = 0;

	for (int i = 0; i < N; i++) {
		games[i] = Game_GUI(SIZE_X, SIZE_Y, GAMESPEED);
	}
	//Game loop
	for (int i = 0; i < N; i++) {

		//games[i].render();

		while (games[i].isRunning())
		{
			if (games[i].clockReady())
			{
				//Update
				games[i].update();

				turn_direction = std::rand() % 3;
				games[i].turn(turn_direction);

				games[i].render();
			}
		}

		score = games[i].getScore();

		/*
		if (score > high_score)
		{
			moved_directions.clear();
			food_pos.clear();

			high_score = score;
			moved_directions = games[i].getMovedDirections();
			food_pos = games[i].getFoodPositions();


			std::cout << "NEW HIGH SCORE BY GAME #" << i << ": " << score << std::endl;

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
		}
		*/
	}


#elif GAMEMODE == 3:

//Init SIM Games
int turn_direction, high_score, score;
std::vector<directions> moved_directions;
std::vector<sf::Vector2i> head_pos, food_pos;

const char* direction_names[4] = { "UP", "RIGHT", "DOWN", "LEFT" };

Game_GUI game(SIZE_X, SIZE_Y, GAMESPEED);
//Game_GUI game(SIZE_X, SIZE_Y, GAMESPEED);


//Game loop
while (game.isRunning())
{
	if (game.clockReady())
	{
		//Update
		game.update();

		turn_direction = std::rand() % 3;
		game.turn(turn_direction);

		game.render();
	}
}

score = game.getScore();


moved_directions = game.getMovedDirections();
food_pos = game.getFoodPositions();


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
	

#endif


	return 0;
}