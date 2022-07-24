#pragma once

#include <deque>
#include <stdlib.h>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"



enum directions {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum game_states {
	RUNNING,
	ENDED
};

/*

	Class that describes game logic

*/

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Game
	game_states game_state;

	// Map
	sf::Vector2i map_size;
	sf::Vector2f tile_size;
	//std::vector<std::vector<int>> map;

	// Snake
	std::deque<sf::Vector2i> snake_body;
	std::vector<sf::RectangleShape> snake_rectangles;
	int snake_length, snake_length_start;
	directions direction;

	// Food
	sf::Vector2i food_pos;
	sf::RectangleShape food_rectangle;

	// Clock
	sf::Clock clock;
	sf::Time elapsed_time, elapsed_time_limit;
	float speed, update_freq;

	
	

	// Private Functions
	void initVariables();
	void initWindow();
	void move();
	void spawnFood();
	sf::Vector2f convertToWindowPos(sf::Vector2i tile_pos);


public:
	//Constructors / Destructors
	Game(int tiles_x, int tiles_y, float speed);
	virtual ~Game();

	//Accessors
	const bool isRunning();
	const int getScore();

	//Functions
	void pollEvents();
	void update();
	void render();


};
