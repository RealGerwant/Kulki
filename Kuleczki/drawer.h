#pragma once
#ifndef drawer_h
#define drawer_h

#include "SFML\Graphics.hpp"
#include "okno.h"

void  draw(okno &window)
{

	float RL = window.R;
	float BS = window.boxSize;
	float grubosc = BS *0.05f;
	sf::RectangleShape kratka;
	kratka.setSize(sf::Vector2f(BS, BS));
	kratka.setFillColor(sf::Color(255, 255, 255));
	kratka.setOutlineThickness(grubosc);
	kratka.setOutlineColor(sf::Color(255, 0, 0));
	for (int i = 0; i < 2*RL+1; i++)
	{
		for (int j = 0;j < 2*RL+1; j++)
		{
			kratka.setPosition(sf::Vector2f(j*BS, i*BS));
			window.window.draw(kratka);
		}
	}
	for (int i = 0; i < window.r; i++)
	{
		window.window.draw(window.kulki[i].kula);
	}
	for (int i = 0; i < window.P * 2 + 1; i++)
	{
		for (int j = 0; j < window.P * 2 + 1; j++)
		{
			window.window.draw(window.polapedow[i][j].pole);
			window.window.draw(window.polapedow[i][j].ilosc);
		}
	}
}

#endif // !drawer_h
