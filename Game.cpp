#include "Game.h"
#include <iostream>

Game::Game(int p_tiles_x, int p_tiles_y, float p_update_rate = 0.5f)
{
	this->map_size = sf::Vector2u(p_tiles_x, p_tiles_y);
	this->update_freq = p_update_rate;

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

	this->direction = RIGHT;

	// Init Snake Head
	this->snake_body[0] = sf::Vector2u(this->map_size.x/2, this->map_size.y/2);

	// Init Snake Body
	for (int i = 1; i < this->snake_length; i++)
	{
		this->snake_body[i] = sf::Vector2u(this->snake_body[i-1].x-1, this->snake_body[i - 1].y);
		//std::cout << this->snake_body[i].x << " " << this->snake_body[i].y << std::endl;
	}

	// Init Clock
	this->elapsed_time_limit = sf::seconds(1 / this->update_freq);
}


void Game::initWindow()
{
	this->videomode.height = 800;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);

	this->tile_size = sf::Vector2f(this->videomode.width / this->map_size.x, this->videomode.height / this->map_size.y);

}

void Game::move()
{
	sf::Vector2u head_pos = sf::Vector2u(this->snake_body[0].x, this->snake_body[0].y);

	switch (this->direction)
	{
	case LEFT:
		head_pos.x--;
		break;
	case UP:
		head_pos.y--;
		break;
	case DOWN:
		head_pos.y++;
		break;
	case RIGHT:
		head_pos.x++;
		break;
	default:
		break;
	}

	this->snake_body.push_front(head_pos);
	this->snake_body.pop_back();
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
			switch (this->ev.key.code)
			{
			case sf::Keyboard::Escape:
				this->window->close();
				break;
			case sf::Keyboard::Up:
				if (this->direction != DOWN) this->direction = UP;
				break;
			case sf::Keyboard::Left:
				if (this->direction != RIGHT) this->direction = LEFT;
				break;
			case sf::Keyboard::Down:
				if (this->direction != UP) this->direction = DOWN;
				break;
			case sf::Keyboard::Right:
				if (this->direction != LEFT) this->direction = RIGHT;
				break;
			}

			break;
		}
	}
}

//Functions
void Game::update()
{

	this->pollEvents();

	if (this->clock.getElapsedTime() > this->elapsed_time_limit)
	{
		// Update snake
		this->move();

		std::cout << std::endl << this->clock.getElapsedTime().asMilliseconds() << std::endl << std::endl;

		// Restart clock
		this->clock.restart();
	}

	//std::cout << this->clock.getElapsedTime().asMilliseconds() << std::endl;


}


void Game::render()
{
	this->window->clear(sf::Color::Blue);


	// Update and draw rectangles
	this->snake_rectangles.resize(this->snake_length);
	sf::Vector2f current_pos_window;

	for (int i = 0; i < this->snake_length; i++)
	{
		current_pos_window = sf::Vector2f(this->snake_body[i].x * this->tile_size.x, this->snake_body[i].y * this->tile_size.y);

		//std::cout << current_pos_window.x << " " << current_pos_window.y << std::endl;

		this->snake_rectangles[i].setSize(this->tile_size);
		this->snake_rectangles[i].setPosition(current_pos_window);
		this->snake_rectangles[i].setOutlineThickness(1);
		this->snake_rectangles[i].setOutlineColor(sf::Color::Cyan);

		this->window->draw(this->snake_rectangles[i]);
	}


	//Draw game objects
	

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