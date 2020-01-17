#pragma once
#include <SFML/Graphics.hpp>


class Przeciwnik
{
private:
	int rodzaj;
	sf::Texture tekstura;
public:
	sf::Clock zegar;
	sf::Sprite wrog;
	sf::IntRect ksztaltwroga;
	int predkosc;
	Przeciwnik();
	~Przeciwnik() {};
	void animuj();
	void draw(sf::RenderWindow& window);
};

