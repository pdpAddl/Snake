#include <iostream>

#include "SFML//System.hpp"
#include "SFML/Graphics.hpp"


using namespace std;

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(640, 480), "Snake", sf::Style::Titlebar | sf::Style::Close);
	sf::Event ev;

	//Game loop
	while (window.isOpen())
	{
		//Event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;

			}
		}

		//Update


		//Render
		window.clear(sf::Color::Cyan); //Clear old frame



		window.display(); // Window is done drawing


	}


	return 0;
}