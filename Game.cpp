#include "Game.h"
#include <iostream>

Game::Game(int p_tiles_x, int p_tiles_y)
{
	this->map_size = sf::Vector2u(p_tiles_x, p_tiles_y);

	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}


void Game::initVariables()
{
	this->window = nullptr;

	this->snake_length = 5;
	this->snake_body.resize(this->snake_length);

	// Init Snake Head
	this->snake_body[0] = sf::Vector2u(this->map_size.x/2, this->map_size.y/2);

	// Init Snake Body
	for (int i = 1; i < this->snake_length; i++)
	{
		this->snake_body[i] = sf::Vector2u(this->snake_body[i-1].x-1, this->snake_body[i - 1].y);
		std::cout << this->snake_body[i].x << " " << this->snake_body[i].y << std::endl;
	}
}


void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);

	this->tile_size = sf::Vector2f(this->videomode.width / this->map_size.x, this->videomode.height / this->map_size.y);

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
	this->snake_rectangles.resize(this->snake_length);

	sf::Vector2f current_pos_window;

	for (int i = 0; i < this->snake_length - 1; i++)
	{
		current_pos_window = sf::Vector2f(this->snake_body[i].x * this->tile_size.x, this->snake_body[i].y * this->tile_size.y);

		//std::cout << current_pos_window.x << " " << current_pos_window.y << std::endl;

		this->snake_rectangles[i] = sf::RectangleShape(this->tile_size);
		this->snake_rectangles[i].setPosition(current_pos_window);

	}
}

void Game::render()
{
	this->window->clear(sf::Color::Blue);


	//Draw game objects

	//Draw Snake
	for (int i = 0; i < this->snake_length - 1; i++)
	{
		this->window->draw(this->snake_rectangles[i]);
	}
	

	this->window->display();
}












/*
void Game::generateSnakeFromDirections()
{
	sf::Vector2u current_pos = this->snake_head;

	for (int i = 0; i < this->snake_length-1; i++)
	{
		switch (this->snake_next_part_direction[i])
		{
		case LEFT:
			current_pos.x -= 1;
			break;
		case UP:
			current_pos.y -= 1;
			break;
		case DOWN:
			current_pos.y += 1;
			break;
		case RIGHT:
			current_pos.x += 1;
			break;
		default:
			break;
		}

		this->map[current_pos.x][current_pos.y] = 2;
	}
}
*/