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
	std::srand(std::time(NULL));

	this->game_state = RUNNING; 
	this->snake = Snake(sf::Vector2i(this->map_size.x / 2, this->map_size.y / 2));

	// Init Food
	this->spawnFood();
	this->food_positions.push_back(this->food_pos);

	this->moves = 0;
}

void Game::move()
{
	sf::Vector2i head_pos = this->snake.getCurrentHeadPosition();
	absolute_directions direction = this->snake.getNewDirection();

	switch (direction)
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
	std::deque <sf::Vector2i> body = this->snake.getBodyPositions();
	if (std::find(body.begin(), body.end(), head_pos) != body.end())
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

	bool eating = false;

	// Collsision with food
	if (head_pos == this->food_pos)
	{
		eating = true;
		this->spawnFood();
	}	
	this->snake.move_forward(head_pos, eating);
}

void Game::spawnFood()
{
	int rand_x, rand_y;
	sf::Vector2i food_pos_tmp;
	/*do
	{
		rand_x = std::rand() % this->map_size.x;
		rand_y = std::rand() % this->map_size.y;
		food_pos_tmp = sf::Vector2i(rand_x, rand_y);

	} while (std::find(this->snake_body.begin(), this->snake_body.end(), food_pos_tmp) != this->snake_body.end());
	*/

	rand_x = std::rand() % this->map_size.x;
	rand_y = std::rand() % this->map_size.y;
	food_pos_tmp = sf::Vector2i(rand_x, rand_y);

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
	int score = this->snake.getLength() - this->snake.getStartLength();
	//std::cout << score;
	return score;
}


//Functions
void Game::update()
{
	// Update snake
	this->move();
	this->moves++;

	this->moved_directions.push_back(this->snake.getCurrentDirection());
	if (this->food_pos != this->food_positions.back()) this->food_positions.push_back(this->food_pos);

}

void Game::turn(int turn_direction)
{
	this->snake.turn((relative_directions)turn_direction);
}


std::vector<absolute_directions> Game::getMovedDirections()
{
	return this->moved_directions;
}

std::vector<sf::Vector2i> Game::getFoodPositions()
{
	return this->food_positions;;
}
sf::Vector2i Game::getCurrentFoodPosition()
{
	return this->food_pos;
}

//***********************************************************************************************************************

Game_SIM::Game_SIM()
{
}

Game_SIM::Game_SIM(int tiles_x, int tiles_y)
	:Game(tiles_x, tiles_y)
{
	//this->moves = 0;
	//this->head_positions.resize(0);
	//this->food_positions.resize(0);

	//this->food_positions.push_back(this->food_pos);
}

/*
void Game_SIM::update()
{
	this->move();
	this->moves++;

	this->moved_directions.push_back(this->direction);
	if (this->food_pos != this->food_positions.back()) this->food_positions.push_back(this->food_pos);
	
	//std::cout << this->snake_body[0].x << " " << this->snake_body[0].y << std::endl;
}
*/

const int Game_SIM::getScore()
{
	int score = this->snake.getLength() - this->snake.getStartLength();
	//if(score) std::cout << score << " with " << this->moves << " moves." <<std::endl;
	return score;
}

/******************************************************************************************************************************************/

Game_GUI::Game_GUI()
{
}

Game_GUI::Game_GUI(int p_tiles_x, int p_tiles_y, float p_speed)
	:Game(p_tiles_x, p_tiles_y)
{
	this->speed = p_speed;
	this->initWindow();
}

Game_GUI::~Game_GUI()
{
	//delete this->window;
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

	this->moved_directions.push_back(this->snake.getCurrentDirection());
	if (this->food_pos != this->food_positions.back()) this->food_positions.push_back(this->food_pos);
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
			absolute_directions current_direction = this->snake.getCurrentDirection();
			switch (this->ev.key.code)
			{
			case sf::Keyboard::Escape:
				this->window->close();
				break;
			case sf::Keyboard::Up:
				if (current_direction != DOWN) this->snake.set_direction(UP);
				break;
			case sf::Keyboard::Left:
				if (current_direction != RIGHT) this->snake.set_direction(LEFT);
				break;
			case sf::Keyboard::Down:
				if (current_direction != UP) this->snake.set_direction(DOWN);
				break;
			case sf::Keyboard::Right:
				if (current_direction != LEFT) this->snake.set_direction(RIGHT);
				break;
			default:
				this->snake.set_direction(current_direction);
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
	this->snake_rectangles.resize(this->snake.getLength());
	sf::Vector2f current_pos_window;

	for (int i = 0; i < this->snake.getLength(); i++)
	{
		current_pos_window = this->convertToWindowPos(this->snake.getBodyPositions()[i]);

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

Game_REP::Game_REP(int tiles_x, int tiles_y, float speed, std::vector<absolute_directions> p_directions, std::vector<sf::Vector2i> p_food_positions)
	:Game_GUI(tiles_x, tiles_y, speed)
{
	this->tomove_directions = p_directions;
	this->toplacefood_positions = p_food_positions;

	if(this->tomove_directions.size()) this->tomove_directions.erase(tomove_directions.begin());

	this->spawnFood();
}

void Game_REP::update()
{
	// Update snake
	this->move();

	if (moved < tomove_directions.size())
	{
		this->snake.set_direction(tomove_directions[moved]);
	}

	this->moved++;

	this->moved_directions.push_back(this->snake.getCurrentDirection());
	if (this->food_pos != this->food_positions.back())
	{
		this->food_positions.push_back(this->food_pos);
	}

	this->spawnFood();

}

void Game_REP::spawnFood()
{
	this->food_pos = this->toplacefood_positions[this->getScore()];
	return;
}