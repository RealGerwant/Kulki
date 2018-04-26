#pragma once
#ifndef drawer_h
#define drawer_h

#include "SFML\Graphics.hpp"
#include "okno.h"

void  draw(okno &window)
{
	int RL = window.R;
	int BS = window.boxSize;
	sf::RectangleShape kratka;
	kratka.setSize(sf::Vector2f(BS, BS));
	kratka.setFillColor(sf::Color(255, 255, 255));
	kratka.setOutlineThickness(BS * 0.1f);
	kratka.setOutlineColor(sf::Color(255, 0, 0));
	for (int i = 0; i < RL; i++)
	{
		for (int j = 0;j < RL; ++j)
		{
			kratka.setPosition(sf::Vector2f(j*BS, i*BS));
			window.window.draw(kratka);
		}
	}
}

#endif // !drawer_h
