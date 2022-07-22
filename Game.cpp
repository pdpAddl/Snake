#include "Game.h"

Game::Game(int pTileAmountX, int pTileAmountY)
{
	this->tileAmountOnMapX = pTileAmountX;
	this->tileAmountOnMapY = pTileAmountY;

	this->initVariables();
	this->initWindow();
	this->initMap();
	this->initSnake();
}

Game::~Game()
{
	delete this->window;
}


void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);

}

void Game::initMap()
{
	sf::Vector2u windowSize = this->window->getSize();

	tileSizeX = windowSize.x / this->tileAmountOnMapX;
	tileSizeY = windowSize.y / this->tileAmountOnMapY;

	/*
	this->enemy.setPosition(100, 100);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(10.f);
	*/
}

void Game::initSnake()
{
	int startLength = 5;
	this->maxSnakeLength = this->tileAmountOnMapX * this->tileAmountOnMapY;

	sf::Vector2u snakebody[5][5];

	//this->body = 


	
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(ev))
	{
		switch (this->ev.type)
		{

		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;

		}
	}
}

//Functions
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	this->window->clear(sf::Color::Red);


	//Draw game objects
	//this->window->draw(this->enemy);


	this->window->display();
}

void Game::setTilePosition(int tileX, int tileY)
{
}


