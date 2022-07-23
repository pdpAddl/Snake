#pragma once

#include <deque>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"


enum directions {
	UP,
	RIGHT,
	DOWN,
	LEFT
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

	// Map
	sf::Vector2i map_size;
	sf::Vector2f tile_size;
	//std::vector<std::vector<int>> map;

	// Snake
	std::deque<sf::Vector2i> snake_body;
	std::vector<sf::RectangleShape> snake_rectangles;
	int snake_length;
	directions direction;

	// Clock
	sf::Clock clock;
	sf::Time elapsed_time, elapsed_time_limit;
	float update_freq;

	
	

	// Private Functions
	void initVariables();
	void initWindow();
	void move();


public:
	//Constructors / Destructors
	Game(int tiles_x, int tiles_y, float update_freq);
	virtual ~Game();

	//Accessors
	const bool isRunning() const;

	//Functions
	void pollEvents();
	void update();
	void render();

};
