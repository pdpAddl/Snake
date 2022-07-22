#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

/*

	Class that describes game logic

*/

enum mapTiles
{
	NOTHING,
	HEAD,
	BODY,
	WALL,
	FOOD
};

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Game Objects Attributes
	int tileSizeX, tileSizeY;
	int tileAmountOnMapX, tileAmountOnMapY;
	int snakeLength, maxSnakeLength;

	// Game Objects
	sf::RectangleShape head;
	sf::RectangleShape* body;

	// Private Functions
	void initVariables();
	void initWindow();
	void initMap();
	void initSnake();



public:
	//Constructors / Destructors
	Game(int tileAmountX, int tileAmountY);
	virtual ~Game();

	//Accessors
	const bool isRunning() const;

	//Functions
	void pollEvents();
	void update();
	void render();

	void setTilePosition(int tileX, int tileY);

};
