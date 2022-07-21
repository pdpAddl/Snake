#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new 	sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);

}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
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
	/*
		- clear old frame
		- render objects
		- display frame in window

		Render ingame objects
	*/
	this->window->clear(sf::Color::Red);

	this->window->display();
}
