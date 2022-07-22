#pragma once

class Tile
{
private:
	// Variables
	int x, y, x_speed, y_speed;
	int size;
	

public:
	// Constructor / Destructor
	Tile();
	~Tile();

	// Functions
	void move();
};

