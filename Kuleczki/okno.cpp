#include "okno.h"




okno::okno()
{
	WH = 1080;
	WW = (16.0f / 9) * WH;
	std::cout << "Podaj r: ";
	std::cin >> r;
	window.create(sf::VideoMode(WW, WH), "Entropia", sf::Style::Fullscreen);
	window.setFramerateLimit(60U);
	R = 2 * r + 1;
	P = r + (1 - r % 2);
	r = pow(2, r);
	deltaT = 1.0f / (2 * P);
	boxSize = (WH*1.0f) / (2 * R + 1);
	kulki = new kulka[r];
	polapedow = new wykrespedow*[2 * P + 1];
	czcionka.loadFromFile("czcionka.otf");
	for (int i = 0; i < 2*P+1; i++)
	{
		polapedow[i] = new wykrespedow[2 * P + 1];
	}
	rozmieszczenie = new int *[2 * R + 1];
	for (int i = 0; i < 2 * R + 1; i++)
	{
		rozmieszczenie[i] = new int[2 * R + 1];
	}
//	std::cout << R;

}

okno::~okno()
{
}

void okno::liczeniekulek() {
	for (int i = 0; i < r; i++)
	{
		rozmieszczenie[(int)(kulki[i].kula.getPosition().x / boxSize) ][(int)(kulki[i].kula.getPosition().y / boxSize) ] += 1;
	}
}
void okno::zerowanieliczeniakulek()
{
	for (int i = 0; i < 2 * R + 1; i++)
	{
		for (int j = 0; j < 2 * R + 1; j++)
		{
			rozmieszczenie[i][j] = 0;
		}
	}
}
void okno::WypiszDoPliku(unsigned int papaj) {
	plik.open("papaj.txt", std::ios::out | std::ios::app);
	for (int i = 0; i < r; i++)
	{
		plik << papaj<<"\t"<<kulki[i].dx<<"\t"<< kulki[i].dy<<"\t" <<std::ceil( kulki[i].kula.getPosition().x / boxSize) <<"\t"<<std::ceil( kulki[i].kula.getPosition().y / boxSize )<< std::endl;
	}
	plik.close();
}

void okno::wpisziloscpedow()
{
	for (int i = 0; i < P * 2 + 1; i++)
	{
		for (int j = 0; j < P * 2 + 1; j++) {
			polapedow[2*P-i][j].ilosc.setString(std::to_string(polapedow[i][j].ile));
		}
	}
	
}
void okno::rysujwykrespedow()
{
	float rozmiar = (WW - WH) / (P * 2 + 1);
	for (int i = P*2; i >=0;i--)
	{
		for (int j = 2*P; j>=0; j--) {
			if (i==P || j == P)
				polapedow[i][j].pole.setFillColor(sf::Color::Yellow);
			else
				polapedow[i][j].pole.setFillColor(sf::Color::White);
			polapedow[i][j].ilosc.setCharacterSize(rozmiar*0.5);
			polapedow[i][j].ilosc.setPosition(WW - rozmiar*(i+1)+rozmiar*0.3, j*rozmiar);
			polapedow[i][j].ilosc.setFillColor(sf::Color::Red);
			polapedow[i][j].ilosc.setFont(czcionka);
			polapedow[i][j].pole.setSize(sf::Vector2f(rozmiar, rozmiar));
			polapedow[i][j].pole.setOutlineThickness(rozmiar*0.05f);
			polapedow[i][j].pole.setOutlineColor(sf::Color::Red);
			polapedow[i][j].pole.setPosition(sf::Vector2f(WW - rozmiar*(i+1)+rozmiar*0.05, j*rozmiar));
		}
	}
}
void okno::uzupelniajwykrespedow()
{
	for (int i = 0; i < r; i++)
	{
		polapedow[kulki[i].dx + P][kulki[i].dy + P].ile += 1;
	}
}

void okno::zerujwykrespedow()
{
	{
		for (int i = 0; i < 2 * P + 1; i++)
		{
			for (int j = 0; j < 2 * P + 1; j++)
			{
				polapedow[i][j].ile = 0;
			}
		}
	}
}
void okno::randAllVelocity()
{
	srand(time(NULL));
	for (int i = 0; i < r; i++)
	{
			kulki[i].dx = (rand() % (P *2)) -P  ;
			kulki[i].dy = (rand() % (P*2)) -P;
			//std::cout << kulki[i].dx << " " << kulki[i].dy << "\n";
			kulki[i].kula.setRadius((float)0.2*boxSize);
			kulki[i].kula.setFillColor(sf::Color::Green);
			kulki[i].kula.setOrigin((float)0.2*boxSize, (float)0.2*boxSize);
	}

}

void okno::wypisz()
{
	for (int i = 0; i < r; ++i)
	{
		std::cout << "#" << i << std::endl;
		std::cout << kulki[i].dx << std::endl;
		std::cout << kulki[i].dy << std::endl;
	}
}

void okno::setInitialPosition()
{
	float y =(WH*1.0f)/r;
	for (int i = 0; i < r; i++)
	{
		kulki[i].kula.setPosition(sf::Vector2f(0.5*boxSize, y*i +boxSize));
	}
}

void okno::ruchKulek()
{
	for (int i = 0; i < r; i++)
	{
		kulki[i].kula.setPosition(sf::Vector2f((kulki[i].kula.getPosition().x)+kulki[i].dx*deltaT, (kulki[i].kula.getPosition().y)+kulki[i].dy*deltaT));
	}
}

void okno::AllcollisionCheck()
{
	for (int i = 0; i < r; i++)
	{
		collisionCheck(kulki[i]);
	}
}
void okno::collisionCheck(kulka &kula)
{
	if (kula.kula.getPosition().x-kula.kula.getRadius() <= fabs(kula.dx*deltaT) && kula.dx<0)
		kula.dx = -kula.dx;
	if (kula.kula.getPosition().x + kula.kula.getRadius() >= WH- fabs(kula.dx*deltaT) && kula.dx>0)
		kula.dx = -kula.dx;
	if (kula.kula.getPosition().y - kula.kula.getRadius() <= fabs(kula.dy*deltaT) && kula.dy<0)
		kula.dy = -kula.dy;
	if (kula.kula.getPosition().y + kula.kula.getRadius() >= WH- fabs(kula.dy*deltaT) && kula.dy>0)
		kula.dy = -kula.dy;
}