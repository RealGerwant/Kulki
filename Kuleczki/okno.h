#pragma once
#include "SFML\Graphics.hpp"

class okno
{
private:
	int r;
	float WH;
	float WW;
public:
	int R;
	int P;
	float boxSize;
	sf::RenderWindow window;


public:
	okno();
	~okno();
};

