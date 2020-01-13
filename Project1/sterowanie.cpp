#include "sterowanie.h"

Sterowanie::Sterowanie(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	for (int i = 0; i < MAX_STER; i++) {
		sterowanie[i].setFont(font);
		sterowanie[i].setPosition(sf::Vector2f(width / 3, height / (MAX_STER + 1) * (i + 1)));
		sterowanie[i].setFillColor(sf::Color::White);																	
		if (i == 0) {																									
			sterowanie[i].setFillColor(sf::Color::Red);																	
			sterowanie[i].setString("W górê");																			
		}																												
		else if (i == 1) {																								
			sterowanie[i].setString("W dó³");																					
		}																												
		else if (i == 2) {																								
			sterowanie[i].setString("W lewo");																				
		}																												
		else if (i == 3) {																								
			sterowanie[i].setString("W prawo");
		}
		else if (i == 4) {
			sterowanie[i].setString("Wstecz");
		}

	}
}

//rysowanie menu w biezacym oknie
void Sterowanie::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_STER; i++)
	{
		window.draw(sterowanie[i]);
	}
}


void Sterowanie::moveIt(int i)
{
	if (selectedItem >= 0 && selectedItem < MAX_STER)
	{
		sterowanie[selectedItem].setFillColor(sf::Color::White);
		sterowanie[selectedItem].setStyle(sf::Text::Regular);
		selectedItem += i;
		if (selectedItem < 0)
			selectedItem = MAX_STER - 1;
		if (selectedItem >= MAX_STER )
			selectedItem = 0;
		sterowanie[selectedItem].setFillColor(sf::Color::Red);
		sterowanie[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Sterowanie::pobierz_sterowanie(std::string a, std::string b, std::string c, std::string d) {
	std::fstream plik;
	int nr_linii = 1;
	plik.open("sterowanie.txt", std::ios::in);
	if (plik.good() == false) {
		std::cout << "plik nie istnieje.";
		exit(0);
	}
	std::string linia;
	while (getline(plik, linia)) {
		switch (nr_linii) {
		case 1: a = linia; break;
		case 2: b = linia; break;
		case 3: c = linia; break;
		case 4: d = linia; break;
		}
		nr_linii++;
	}
	plik.close();
}
void Sterowanie::zmien_sterowanie(std::string a, std::string b, std::string c, std::string d) {
	std::fstream plik;
	plik.open("sterowanie.txt", std::ios::out);
	plik << a << std::endl;
	plik << b << std::endl;
	plik << c << std::endl;
	plik << d << std::endl;
	plik.close();

}
