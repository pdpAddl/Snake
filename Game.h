#pragma once

#include "SFML//System.hpp"
#include "SFML/Graphics.hpp"


/*

	Class that describes game logic

*/


class Game
{
private:
	// Private Variables
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Private Functions
	void initVariables();
	void initWindow();



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
