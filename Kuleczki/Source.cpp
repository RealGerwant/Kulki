#include "SFML\Graphics.hpp"
#include <Windows.h>
#include <math.h>
#include <iostream>
#include "drawer.h"
#include "okno.h"
#include <fstream>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
unsigned long long int silnia(unsigned long long int i)
{
	if (i == 1 || i==0)
		return 1;
	else
		return silnia(i - 1)*i;
}

void prawdopodobienstwo(int nrkwant, int ilezer ,long double prawdopodobienstwo, long double entropia)
{
	std::fstream plik;
	plik.open("prawdopodobienstwo.txt", std::ios::out | std::ios::app);
	plik << nrkwant << "\t" <<ilezer<<"\t"<< prawdopodobienstwo << "\t"<<entropia << std::endl;
	plik.close();
}
int main(int argc, char **argv)
{

	unsigned int nrkwant = 0;
	okno entropia;
	sf::Event events;
	sf::Keyboard::setVirtualKeyboardVisible;
	entropia.randAllVelocity();
	entropia.setInitialPosition();
//	std::cout << "wylosowano";
	//entropia.wypisz();
	entropia.rysujwykrespedow();
	entropia.zerowanieliczeniakulek();
	std::ofstream plik;
	std::ofstream plik2;
	plik2.open("prawdopodobienstwo.txt");
	plik2.close();
	plik.open("papaj.txt");
	long double prawdopodobienstwoTermodynamiczne;
	long double entropiawar;
	long double mianownik=1;
	plik.close();
	while (entropia.window.isOpen())
	{
		mianownik = 1;
		entropia.zerujwykrespedow();
		entropia.uzupelniajwykrespedow();
		entropia.wpisziloscpedow();
		entropia.AllcollisionCheck();
		entropia.liczeniekulek();
		entropia.ruchKulek();
		while(entropia.window.pollEvent(events))
			if ((events.type == sf::Event::KeyPressed) && (events.key.code == sf::Keyboard::Escape))
			{
				entropia.window.close();
				system("close");
				return 0;
			}
		int ilezer = 0;
		for (int i = 0; i < 2 * entropia.R + 1; i++)
		{
			for (int j = 0; j < 2 * entropia.R + 1; j++)
			{
				for (int k = 1; k < entropia.rozmieszczenie[i][j]; k++)
				{
					mianownik = mianownik*k;
					if (mianownik > (double)pow(10, 100))
					{
						ilezer -= 100;
						mianownik /= pow(10, 100);
					}
				}
			}
		}
		prawdopodobienstwoTermodynamiczne = 1 / mianownik;
		for (int i = 1; i < entropia.r; i++)
		{
			prawdopodobienstwoTermodynamiczne = prawdopodobienstwoTermodynamiczne*i;
			if (prawdopodobienstwoTermodynamiczne >(double) pow(10, 100))
			{
				ilezer += 100;
				prawdopodobienstwoTermodynamiczne /= pow(10, 100);
			}
		}
		long long int ilezerentropia = ilezer*std::log(10);
		entropiawar = std::log(prawdopodobienstwoTermodynamiczne)+ilezerentropia;
		prawdopodobienstwo(nrkwant,ilezer ,prawdopodobienstwoTermodynamiczne, entropiawar);
		plt::plot({ 1, 2, 3, 4 });
		plt::show();
		entropia.zerowanieliczeniakulek();
		entropia.window.clear();
		draw(entropia);
		entropia.window.display();
		entropia.WypiszDoPliku(nrkwant);
		++nrkwant;
	}
}