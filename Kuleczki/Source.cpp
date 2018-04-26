#include "SFML\Graphics.hpp"
#include <Windows.h>
#include <iostream>
#include "drawer.h"
#include "okno.h"


int main(int argc, char **argv)
{
	okno entropia;
	sf::Event events;
	sf::Keyboard::setVirtualKeyboardVisible;
	while (entropia.window.isOpen())
	{

		while(entropia.window.pollEvent(events))
			if ((events.type == sf::Event::KeyPressed) && (events.key.code == sf::Keyboard::Escape))
			{
				entropia.window.close();
				system("close");
				return 0;
			}
		entropia.window.clear();
		draw(entropia);
		entropia.window.display();
	}

	Sleep(3000);
}