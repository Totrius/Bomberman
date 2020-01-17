#include "Wskazowki.h"
Wskazowki::Wskazowki(float width, float height) {
	if (!wskazowki.loadFromFile("wskazowki.png"))
	{
		return;
	}
	jak_grac.setTexture(wskazowki);
}
void Wskazowki::draw(sf::RenderWindow& window)
{
	window.draw(jak_grac);
}
