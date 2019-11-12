#include <SFML/Graphics.hpp>
#include <iostream>
#include "test.h"

#define MAX_LICZBA_POZIOMOW 3
//#define TEST

class Menu
{

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
	int selectedItem = 0;


public:
	Menu(float width, float height);
	~Menu() {};
	void moveIt(int i);//przesun
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};


Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
		menu[i].setFont(font);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * (i+1)));
		menu[i].setFillColor(sf::Color::White);
		if (i == 0) {
			menu[i].setFillColor(sf::Color::Red);
			menu[i].setString("Nowa gra");
		}
		else if (i == 1) {
			menu[i].setString("Ostatnie wyniki");
		}else if (i == 2) {
			menu[i].setString("Wyjscie");
		}
		
	}
}

//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::moveIt(int i)
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem += i;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Red);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}


//funkcja opozniajaca
void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}

	}
}


int main()
{
#ifdef TEST
	test();
	return 0;
#endif
	int wybrane_menu = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "My Bombeer");// utworz okno

	Menu menu(window.getSize().x, window.getSize().y);
	// petla wieczna - dopoki okno jest otwarte
	sf::Event event;
	while (window.isOpen())
	{
		

		// w kazdej iteracji petli sprawdzaj zdarzenia
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				window.close();			

			//jezeli nacisnieto jakikolwiek przycisk
			if (event.type == sf::Event::KeyPressed)
			{//obsluga menu z poziomu klawiszy (strzalki)
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(150);
					menu.moveIt(-1);
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(150);
					menu.moveIt(1);
				}
				if (wybrane_menu == 0)
				{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Uruchamiam gre..." << std::endl;
						wybrane_menu = 1;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						std::cout << "Najlepsze wyniki..." << std::endl;
						wybrane_menu = 1;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Koniec gry..." << std::endl;
						window.close();
					}
				}
			}
		}
		// wyczysc obszar rysowania
		window.clear();
		// tutaj umiesc procedury rysujace...
		// window.draw(...);
		if (wybrane_menu == 0) {
			menu.draw(window);
			
		}

		// ostatnia czynnosc - wyswietl okno wraz zawartoscia
		window.display();
	}

	return 0;
}