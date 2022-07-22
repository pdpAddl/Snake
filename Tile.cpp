#include "Tile.h"

Tile::Tile()
{
	this->size = 1;
	this->x = 0;
	this->y = 0;
	this->x_speed = 1;
	this->y_speed = 1;
}

Tile::~Tile()
{
}

void Tile::move()
{
	this->x += this->x_speed;
	this->y += this->y_speed;
}
