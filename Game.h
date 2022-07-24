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

enum modes {
	SIMULATION,
	MANUAL
};

/*

	Class that describes game logic

*/

class Game
{
protected:

	// Game
	game_states game_state;
	modes mode;

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

	
	

	// Private Functions
	void initVariables();
	void move();
	void spawnFood();
	sf::Vector2f convertToWindowPos(sf::Vector2i tile_pos);


public:
	//Constructors / Destructors
	Game(int tiles_x, int tiles_y);
	virtual ~Game();

	//Accessors
	const bool isRunning();
	const int getScore();

	//Functions
	virtual void update();
};

class Game_GUI : public Game
{
private:

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Clock
	sf::Clock clock;
	sf::Time elapsed_time, elapsed_time_limit;
	float speed, update_freq;

	// Functions
	void initWindow();

public:
	Game_GUI(int tiles_x, int tiles_y, float speed);
	~Game_GUI();

	void pollEvents();
	void render();
	void update() override;
};

class Game_GUI : public Game
{
private:

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Clock
	sf::Clock clock;
	sf::Time elapsed_time, elapsed_time_limit;
	float speed, update_freq;

	// Functions
	void initWindow();

public:
	Game_GUI(int tiles_x, int tiles_y, float speed);
	~Game_GUI();

	void pollEvents();
	void render();
	void update() override;
};
