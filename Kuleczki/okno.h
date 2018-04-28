#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <math.h>
#include <iostream>
#include <fstream>

class wykrespedow
{
	public:
	int ile=0;
	sf::RectangleShape pole;
	sf::Text ilosc;
};

struct kulka
{
	int dx = 1;
	int dy = 1;
	sf::CircleShape kula;
};
class okno
{
private:

	float WH;
	float WW;
public:
	std::fstream plik;
	float deltaT;
	int r;
	int R;
	int P;
	sf::Font czcionka;
	float boxSize;
	sf::RenderWindow window;
	int * array;
	int ** rozmieszczenie;
	kulka * kulki;
	wykrespedow ** polapedow;


public:
	okno();
	~okno();
	void zerowanieliczeniakulek();
	void liczeniekulek();
	void wpisziloscpedow();
	void uzupelniajwykrespedow();
	void zerujwykrespedow();
	void rysujwykrespedow();
	void collisionCheck(kulka &kula);
	void AllcollisionCheck();
	void ruchKulek();
	void setInitialPosition();
	void randAllVelocity();
	void wypisz();
	void WypiszDoPliku( unsigned int papaj);
};

