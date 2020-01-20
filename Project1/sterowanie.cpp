#include "sterowanie.h"

Sterowanie::Sterowanie(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		return;
	}

	gora = sf::Keyboard::Key::W;
	dol = sf::Keyboard::Key::S;
	lewo = sf::Keyboard::Key::A;
	prawo = sf::Keyboard::Key::D;
	bomba = sf::Keyboard::Key::Space;

	//rysowanie elementow menu
	for (int i = 0; i < MAX_STER; i++) {
		sterowanie[i].setFont(font);
		sterowanie[i].setPosition(sf::Vector2f(width / 5, height / (MAX_STER + 1) * (i + 1)));
		sterowanie[i].setFillColor(sf::Color::White);																	
		if (i == 0) {																									
			sterowanie[i].setFillColor(sf::Color::Red);																	
			sterowanie[i].setString("Ustaw ruch w gore");																			
		}																												
		else if (i == 1) {																								
			sterowanie[i].setString("Ustaw ruch w dol");																					
		}																												
		else if (i == 2) {																								
			sterowanie[i].setString("Ustaw ruch w lewo");																				
		}																												
		else if (i == 3) {																								
			sterowanie[i].setString("Ustaw ruch w prawo");
		}
		else if (i == 4) {
			sterowanie[i].setString("Ustaw stawianie bomb");
		}
		else if (i == 5) {
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
void Sterowanie::pobierz_sterowanie() {
	std::fstream plik;
	plik.open("sterowanie.txt", std::ios::in);
	if (plik.good() == false) {
		std::cout << "pliku nie mozna otworzyc";
		plik.close();
		return;
	}
	int klawisz;
	plik >> klawisz; gora = static_cast<sf::Keyboard::Key>(klawisz);
	plik >> klawisz; dol = static_cast<sf::Keyboard::Key>(klawisz);
	plik >> klawisz; lewo = static_cast<sf::Keyboard::Key>(klawisz);
	plik >> klawisz; prawo = static_cast<sf::Keyboard::Key>(klawisz);
	plik >> klawisz; bomba = static_cast<sf::Keyboard::Key>(klawisz);

	plik.close();
}
void Sterowanie::zapisz_sterowanie() {
	std::fstream plik;
	plik.open("sterowanie.txt", std::ios::out);
	if (plik.good() == false) {
		plik.close();
		return;
	}
	
	plik << gora << ' ';
	plik << dol << ' ';
	plik << lewo << ' ';
	plik << prawo << ' ';
	plik << bomba << ' ';

	plik.close();

}
