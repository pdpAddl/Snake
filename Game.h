#pragma once

#include <deque>
#include <stdlib.h>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"



enum directions {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum game_states {
	RUNNING,
	ENDED
};

enum modes {
	SIMULATION,
	MANUAL
};

/*

	Class that describes game logic

*/

class Game
{
protected:

	// Game
	game_states game_state;
	modes mode;

	// Map
	sf::Vector2i map_size;
	sf::Vector2f tile_size;
	//std::vector<std::vector<int>> map;

	// Snake
	std::deque<sf::Vector2i> snake_body;
	std::vector<sf::RectangleShape> snake_rectangles;
	int snake_length, snake_length_start;
	directions direction, new_direction;

	// Food
	sf::Vector2i food_pos;
	sf::RectangleShape food_rectangle;

	// Private Functions
	void initVariables();
	void move();
	virtual void spawnFood();
	sf::Vector2f convertToWindowPos(sf::Vector2i tile_pos);

	// Trace
	int moves;
	std::vector<directions> moved_directions;
	std::vector<sf::Vector2i> food_positions;

public:
	//Constructors / Destructors
	Game();
	Game(int tiles_x, int tiles_y);
	virtual ~Game();

	//Accessors
	const bool isRunning();
	const int virtual getScore();

	//Functions
	virtual void update();
	void turn(int turn_direction);

	std::vector<directions> getMovedDirections();
	std::vector<sf::Vector2i> getFoodPositions();
};



class Game_SIM : public Game
{
private:

public:
	Game_SIM();
	Game_SIM(int tiles_x, int tiles_y);
	//void update() override;
	const int getScore() override;
};



class Game_GUI : public Game
{
protected:

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Clock
	sf::Clock clock;
	sf::Time elapsed_time_limit;
	float speed, update_freq;

	// Functions
	void initWindow();

public:
	Game_GUI();
	Game_GUI(int tiles_x, int tiles_y, float speed);
	~Game_GUI();

	bool clockReady();

	void pollEvents();
	void render();
	void update() override;
};


// Class for replaying simulated games
class Game_REP : public Game_GUI
{
private:
	std::vector<directions> tomove_directions;
	std::vector<sf::Vector2i> toplacefood_positions;
	int moved;

public:
	Game_REP(int tiles_x, int tiles_y, float speed, std::vector<directions> moved_directions, std::vector<sf::Vector2i> food_positions);
	void update() override;
	void spawnFood() override;
};
