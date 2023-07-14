#include <deque>
#include <stdlib.h>

#include "SFML/System.hpp"

enum absolute_directions {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum relative_directions
{
	STAY,
	LEFT_TURN,
	RIGHT_TURN
};

class Snake {

private:
	std::deque<sf::Vector2i> body;
	int length, length_start;
	absolute_directions direction, new_direction;

public:
	Snake();
	Snake(sf::Vector2i head_pos);
	virtual ~Snake();
	
	// getters
	std::deque<sf::Vector2i> getBodyPositions();
	sf::Vector2i getCurrentHeadPosition();
	absolute_directions getCurrentDirection();
	absolute_directions getNewDirection();
	int getLength();
	int getStartLength();

	// setters
	void set_direction(absolute_directions new_direction);

	// logic
	void turn(relative_directions turn_direction);
	void move_forward(sf::Vector2i new_head_pos, bool eating);
	
};
