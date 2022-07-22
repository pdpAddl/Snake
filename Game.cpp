#include "Game.h"
#include <iostream>

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initMap();
}

Game::~Game()
{
	delete this->window;

	for (int i = 0; i < this->tile_amt_x; i++)
	{
		delete map[i];
	}
	delete map;
}


void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initMap()
{
	this->tile_amt_x = 10;
	this->tile_amt_y = 10;

	// Init Map itself
	map = new int*[this->tile_amt_x];

	for (int i = 0; i < this->tile_amt_x; i++)
	{
		map[i] = new int[this->tile_amt_y];

		for (int j = 0; j < tile_amt_y; j++)
		{
			map[i][j] = 0;
		}
	}

	debugMap();
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);

}

void Game::debugMap()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << std::endl;

		for (int j = 0; j < 10; j++)
		{
			std::cout << this->map[i][j];
		}
	}
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


	this->window->display();
}



