#include "menu.h"

Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
		menu[i].setFont(font);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * (i + 1)));
		menu[i].setFillColor(sf::Color::White);
		if (i == 0) {
			menu[i].setFillColor(sf::Color::Red);
			menu[i].setString("Nowa gra");
		}
		else if (i == 1) {
			menu[i].setString("Ostatnie wyniki");
		}
		else if (i == 2) {
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
