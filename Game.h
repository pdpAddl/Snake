#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

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
	int** map;

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
