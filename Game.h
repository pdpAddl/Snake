#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

/*

	Class that describes game logic

*/

enum mapTiles
{
	EMPTY,
	SNAKE_HEAD,
	SNAKE_BODY
};

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Map
	int** map;
	int tile_amt_x, tile_amt_y;

	// Private Functions
	void initVariables();
	void initMap();
	void initWindow();
	void debugMap();


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
