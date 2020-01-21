#include "Wychodzenie.h"
Wychodzenie::Wychodzenie(float width, float height) {
	if (!wychodzenie.loadFromFile("wychodzenie.png"))
	{
		return;
	}
	czy_wyjsc.setTexture(wychodzenie);
}
void Wychodzenie::draw(sf::RenderWindow& window)
{
	window.draw(czy_wyjsc);
}
