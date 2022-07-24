#include "Game.h"
#include <iostream>

Game::Game()
{
}

Game::Game(int p_tiles_x, int p_tiles_y)
{
	this->map_size = sf::Vector2i(p_tiles_x, p_tiles_y);
	this->initVariables();
}

Game::~Game()
{
}

void Game::initVariables()
{
	this->game_state = RUNNING;

	this->snake_length_start = 5;
	this->snake_length = this->snake_length_start;
	this->snake_body.resize(this->snake_length);
	this->new_direction = RIGHT;



	// Init Snake Head
	this->snake_body[0] = sf::Vector2i(this->map_size.x / 2, this->map_size.y / 2);

	// Init Snake Body
	for (int i = 1; i < this->snake_length; i++)
	{
		this->snake_body[i] = sf::Vector2i(this->snake_body[i - 1].x - 1, this->snake_body[i - 1].y);
		//std::cout << this->snake_body[i].x << " " << this->snake_body[i].y << std::endl;
	}

	// Init Food
	this->spawnFood();
}

void Game::move()
{
	sf::Vector2i head_pos = sf::Vector2i(this->snake_body[0].x, this->snake_body[0].y);

	this->direction = this->new_direction;

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



	// Collision detection

	// Collision with itself
	if (std::find(this->snake_body.begin(), this->snake_body.end(), head_pos) != this->snake_body.end())
	{
		this->game_state = ENDED;
		//std::cout << "COLLISION!" << std::endl;
	}

	// Collsision with border window
	if ((head_pos.x >= this->map_size.x) || (head_pos.x < 0) || (head_pos.y >= this->map_size.y) || (head_pos.y < 0))
	{
		this->game_state = ENDED;
		//std::cout << "COLLISION with wall!" << std::endl;
	}

	// Collsision with food
	if (head_pos == this->food_pos)
	{
		//std::cout << "EAT!" << std::endl;
		this->snake_length++;
		this->spawnFood();
	}
	else
	{
		this->snake_body.pop_back();
	}


	this->snake_body.push_front(head_pos);
	
}

void Game::spawnFood()
{
	int rand_x, rand_y;
	sf::Vector2i food_pos_tmp;
	do
	{
		rand_x = std::rand() % this->map_size.x;
		rand_y = std::rand() % this->map_size.y;
		food_pos_tmp = sf::Vector2i(rand_x, rand_y);

	} while (std::find(this->snake_body.begin(), this->snake_body.end(), food_pos_tmp) != this->snake_body.end());
	
	this->food_pos = food_pos_tmp;
}

sf::Vector2f Game::convertToWindowPos(sf::Vector2i tile_pos)
{
	return sf::Vector2f(tile_pos.x * this->tile_size.x, tile_pos.y * this->tile_size.y);
}


const bool Game::isRunning() 
{

	switch (this->game_state)
	{
	case RUNNING:
		return true;
		break;
	case ENDED:
		return false;
		break;
	default: 
		return true;
		break;
	}

	return this->game_state;
}

const int Game::getScore()
{
	int score = this->snake_length - this->snake_length_start;
	std::cout << score;
	return score;
}


//Functions
void Game::update()
{
	// Update snake
	this->move();

}

void Game::turn(int turn_direction)
{
	// 0 - Stay
	// 1 - Left (Relative)
	// 2 - Right (Relative)

	int current_direction = (int)this->direction;

	switch (turn_direction)
	{
	case 0:
		break;
	case 1:
		current_direction--;
		break;
	case 2:
		current_direction++;
		break;
	}

	current_direction = (current_direction % 4 + 4) % 4;


	this->new_direction = (directions)current_direction;
}
//***********************************************************************************************************************

Game_GUI::Game_GUI(int p_tiles_x, int p_tiles_y, float p_speed)
	:Game(p_tiles_x, p_tiles_y)
{
	this->speed = p_speed;
	this->initWindow();
}

Game_GUI::~Game_GUI()
{
	delete this->window;
}

bool Game_GUI::clockReady()
{
	if (this->clock.getElapsedTime() < this->elapsed_time_limit)
	{
		return false;
	}
	else
	{
		this->clock.restart();
		return true;
	}
}

void Game_GUI::initWindow()
{
	this->videomode.height = 800;
	this->videomode.width = 800;

	this->window = new sf::RenderWindow(this->videomode, "Snake", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);

	this->tile_size = sf::Vector2f(this->videomode.width / this->map_size.x, this->videomode.height / this->map_size.y);
	
	// Init Clock
	this->update_freq = this->speed * (this->map_size.x + this->map_size.y) / 4;
	this->elapsed_time_limit = sf::seconds(1 / this->update_freq);

}


void Game_GUI::update()
{

	this->pollEvents();

	// Update snake
	this->move();

	

}

void Game_GUI::pollEvents()
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
				if (this->direction != DOWN) this->new_direction = UP;
				break;
			case sf::Keyboard::Left:
				if (this->direction != RIGHT) this->new_direction = LEFT;
				break;
			case sf::Keyboard::Down:
				if (this->direction != UP) this->new_direction = DOWN;
				break;
			case sf::Keyboard::Right:
				if (this->direction != LEFT) this->new_direction = RIGHT;
				break;
			}

			break;
		}
	}
}


void Game_GUI::render()
{
	this->window->clear(sf::Color::Blue);


	// Draw snake
	this->snake_rectangles.resize(this->snake_length);
	sf::Vector2f current_pos_window;

	for (int i = 0; i < this->snake_length; i++)
	{
		current_pos_window = this->convertToWindowPos(this->snake_body[i]);

		//std::cout << current_pos_window.x << " " << current_pos_window.y << std::endl;

		this->snake_rectangles[i].setSize(this->tile_size);
		this->snake_rectangles[i].setPosition(current_pos_window);
		this->snake_rectangles[i].setOutlineThickness(1);
		this->snake_rectangles[i].setOutlineColor(sf::Color::Cyan);

		this->window->draw(this->snake_rectangles[i]);
	}

	// Draw food
	this->food_rectangle.setSize(this->tile_size);
	this->food_rectangle.setPosition(this->convertToWindowPos(this->food_pos));
	this->food_rectangle.setFillColor(sf::Color::Red);

	this->window->draw(this->food_rectangle);

	this->window->display();
}


/*********************************************************************************************************************************/

Game_SIM::Game_SIM()
{
}

Game_SIM::Game_SIM(int tiles_x, int tiles_y)
	:Game(tiles_x, tiles_y)
{
	this->moves = 0;
}

void Game_SIM::update()
{
	this->move();
	this->moves++;
	
	//std::cout << this->snake_body[0].x << " " << this->snake_body[0].y << std::endl;
}

const int Game_SIM::getScore()
{
	int score = this->snake_length - this->snake_length_start;
	if(score) std::cout << score << " with " << this->moves << " moves." <<std::endl;
	return score;
}