#include "okno.h"
#include <iostream>



okno::okno()
{
	WH = 1080;
	WW = (16.0f / 9) * WH;
	std::cout << "Podaj r: ";
	std::cin >> r;
	window.create(sf::VideoMode(WW, WH), "Entropia",sf::Style::Fullscreen);
	R = 2 * r + 1;
	P = r + (1 - r % 2);
	boxSize = WH / R;
}


okno::~okno()
{
}
