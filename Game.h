#pragma once

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
	std::vector<std::vector<int>> map;
	int tile_amt_x, tile_amt_y;

	// Snake
	sf::Vector2u snake_head;
	int snake_length;
	std::vector<directions> snake_next_part_direction;

	// Private Functions
	void initVariables();
	void initMap();
	void initWindow();
	void debugMap();
	void generateBodyFromDirections();


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool isRunning() const;

	//Functions
	void pollEvents();
	void update();
	void render();

};
