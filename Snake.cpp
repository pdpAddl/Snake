#include "Snake.h"

Snake::Snake() : Snake(sf::Vector2i(5, 5)) {}

Snake::Snake(sf::Vector2i head_pos)
{
	this->length_start = 5;
	this->length = this->length_start;

	this->body.resize(this->length_start);
	this->direction = RIGHT;
	this->new_direction = RIGHT;

	// Init Head
	this->body[0] = sf::Vector2i(head_pos.x, head_pos.y);

	// Init Body
	for (int i = 1; i < this->length; i++)
	{
		this->body[i] = sf::Vector2i(this->body[i - 1].x - 1, this->body[i - 1].y);
	}
}

Snake::~Snake()
{
}

std::deque<sf::Vector2i> Snake::getBodyPositions()
{
	return this->body;
}

sf::Vector2i Snake::getCurrentHeadPosition()
{
	return this->body.front();
}

absolute_directions Snake::getCurrentDirection()
{
	return this->direction;
}

absolute_directions Snake::getNewDirection()
{
	return this->new_direction;
}

int Snake::getLength()
{
	return this->length;
}

int Snake::getStartLength()
{
	return this->length_start;
}

void Snake::turn(relative_directions turn_direction)
{
	// 0 - Stay
	// 1 - Left (Relative)
	// 2 - Right (Relative)

	int new_direction = (int)this->getCurrentDirection();

	switch (turn_direction)
	{
	case 0:
		break;
	case 1:
		new_direction--;
		break;
	case 2:
		new_direction++;
		break;
	}

	//current_direction = (current_direction % 4 + 4) % 4;
	new_direction = new_direction % 4;

	this->new_direction = (absolute_directions)new_direction;
}

void Snake::move_forward(sf::Vector2i new_head_pos, bool eating)
{
	if (eating)
	{
		this->length++;
	}
	else
	{
		this->body.pop_back();
	}

	this->body.push_front(new_head_pos);
	this->direction = this->new_direction;
}

void Snake::set_direction(absolute_directions new_direction)
{
	this->new_direction = new_direction;
}
